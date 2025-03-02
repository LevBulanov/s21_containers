#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename Key>
class set {
 public:
  typedef Key key_type;
  typedef Key value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;

  class SetNode {
   public:
    SetNode() {};
    explicit SetNode(value_type data)
        : data_(data), left_(nullptr), right_(nullptr) {};

    friend class set;

   private:
    value_type data_ = {0};
    SetNode* left_ = nullptr;
    SetNode* right_ = nullptr;
  };

  typedef class SetIterator {
   public:
    explicit SetIterator(SetNode* p, SetNode* h) : ptr_(p), head_(h) {};
    SetIterator(SetIterator& it) : ptr_(it.ptr_), head_(it.head_) {};
    SetIterator(const SetIterator& it) : ptr_(it.ptr_), head_(it.head_) {};

    SetIterator& operator=(const SetIterator& it) {
      ptr_ = it.ptr_;
      head_ = it.head_;
      return *this;
    }

    bool operator==(SetIterator const& other) const noexcept {
      return ptr_ == other.ptr_ && head_ == other.head_;
    };

    bool operator!=(SetIterator const& other) const noexcept {
      return ptr_ != other.ptr_ || head_ != other.head_;
    };

    SetIterator& operator++() {
      if (ptr_ == head_) {
        if (head_->left_ != nullptr) {
          ptr_ = head_->left_;
          while (ptr_->right_ != nullptr) {
            ptr_ = ptr_->right_;
          }
        }
      } else {
        value_type current_data = ptr_->data_;
        SetNode* ptr = search_greater(head_->left_, current_data);
        if (ptr != nullptr) {
          *this = SetIterator(ptr, head_);
        } else {
          *this = SetIterator(head_, head_);
        }
      }
      return *this;
    };

    SetIterator& operator--() {
      if (ptr_ == head_) {
        if (head_->left_ != nullptr) {
          ptr_ = head_->left_;
          while (ptr_->right_ != nullptr) {
            ptr_ = ptr_->right_;
          }
        }
      } else {
        value_type current_data = ptr_->data_;
        SetNode* ptr = search_lower(head_->left_, current_data);
        if (ptr != nullptr) *this = SetIterator(ptr, head_);
      };
      return *this;
    };

    value_type& operator*() const noexcept { return ptr_->data_; };

   private:
    SetNode* search_greater(SetNode* ptr, const value_type& value) const {
      SetNode* result = nullptr;
      if (value < ptr->data_) {
        if (ptr->left_ != nullptr) {
          result = search_greater(ptr->left_, value);
        }
        if (result == nullptr) result = ptr;
      } else if (ptr->right_ != nullptr) {
        result = search_greater(ptr->right_, value);
      }
      return result;
    }

    SetNode* search_lower(SetNode* ptr, const value_type& value) const {
      SetNode* result = nullptr;
      if (value <= ptr->data_) {
        if (ptr->left_ != nullptr) {
          result = search_lower(ptr->left_, value);
        }
      } else {
        if (ptr->right_ != nullptr) {
          result = search_lower(ptr->right_, value);
        }
        if (result == nullptr) result = ptr;
      }
      return result;
    }

    SetNode* ptr_;
    SetNode* head_;
  } iterator;
  typedef const iterator const_iterator;

  // constructors
  set() {
    SetNode* new_node = new SetNode();
    root_ = new_node;
    size_ = 0;
  }

  set(std::initializer_list<value_type> const& items) : set() {
    for (const_reference item : items) {
      insert(item);
    }
  }

  set(const set& s) : set() { *this = s; }

  set(set&& s) noexcept : set() { *this = std::move(s); }

  // destructor
  ~set() { clear_tree(root_); }

  // copy assignment operator
  set& operator=(const set& s) {
    // std::cout << "copy assignment" << std::endl;
    clear();
    root_->left_ = copy_tree(s.root_->left_);
    return *this;
  }

  // move assignment operator
  set& operator=(set&& s) noexcept {
    // std::cout << "move assignment" << std::endl;
    clear();
    swap(s);
    return *this;
  }

  // Set Iterators
  iterator begin() const {
    SetNode* ptr = root_;
    if (!empty()) {
      while (ptr->left_ != nullptr) {
        ptr = ptr->left_;
      }
    }
    return iterator(ptr, root_);
  }

  iterator end() const { return iterator(root_, root_); }

  // Set Capacity
  bool empty() const noexcept { return root_->left_ == nullptr; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<std::size_t>::max() / 2 / sizeof(SetNode);
  }

  // Set Modifiers

  void clear() {
    clear_tree(root_->left_);
    root_->left_ = nullptr;
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    std::pair<iterator, bool> result{end(), false};
    root_->left_ = add_node(root_->left_, value, result);
    return result;
  }

  void swap(set& other) noexcept {
    SetNode* tmp_root = root_;
    size_type tmp_size = size_;
    root_ = other.root_;
    size_ = other.size_;
    other.root_ = tmp_root;
    other.size_ = tmp_size;
  }

  void merge(set& other) {
    splice_tree(other.root_->left_);
    other.root_->left_ = nullptr;
    other.size_ = 0;
  }

  // Set Lookup
  iterator find(const Key& key) const noexcept {
    iterator it = begin();
    const_iterator end_it = end();
    while (*it != key && it != end_it) ++it;
    return it;
  }

  bool contains(const Key& key) const noexcept {
    iterator it = find(key);
    return it != end();
  }

  void print() {
    print_node(root_->left_);
    std::cout << std::endl;
  }

 private:
  SetNode* add_node(SetNode* ptr, const value_type& value,
                    std::pair<iterator, bool>& p) {
    SetNode* result = ptr;
    if (ptr == nullptr) {
      result = new SetNode(value);
      ++size_;
      // p = {iterator(result), true};
      p.first = iterator(result, root_);
      p.second = true;
    } else if (value < ptr->data_) {
      ptr->left_ = add_node(ptr->left_, value, p);
    } else if (value > ptr->data_) {
      ptr->right_ = add_node(ptr->right_, value, p);
    }
    return result;
  }

  void clear_tree(SetNode* ptr) {
    if (ptr != nullptr) {
      clear_tree(ptr->left_);
      clear_tree(ptr->right_);
      delete ptr;
      --size_;
    }
  }

  SetNode* copy_tree(SetNode* ptr) {
    SetNode* result = nullptr;
    if (ptr != nullptr) {
      result = new SetNode(ptr->data_);
      result->left_ = copy_tree(ptr->left_);
      result->right_ = copy_tree(ptr->right_);
      ++size_;
    }
    return result;
  }

  void splice_tree(SetNode* ptr) {
    if (ptr != nullptr) {
      insert(ptr->data_);
      if (ptr->left_) splice_tree(ptr->left_);
      if (ptr->right_) splice_tree(ptr->right_);
      delete ptr;
    }
  }

  void print_node(SetNode* ptr) {
    if (ptr != nullptr) {
      print_node(ptr->left_);
      std::cout << ptr->data_ << " ";
      print_node(ptr->right_);
    }
  }

  SetNode* root_;
  size_type size_;
};

}  // namespace s21