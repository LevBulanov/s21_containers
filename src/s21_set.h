#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class set {
 public:
  typedef T key_type;
  typedef T value_type;
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
    explicit SetIterator(SetNode* p) : ptr_(p) {};
    SetIterator(SetIterator& it) : ptr_(it.ptr_) {};
    SetIterator(const SetIterator& it) : ptr_(it.ptr_) {};

    SetIterator& operator=(const SetIterator& it) noexcept {
      ptr_ = it.ptr_;
      return *this;
    }

    bool operator==(SetIterator const& other) const noexcept {
      return ptr_ == other.ptr_;
    };

    bool operator!=(SetIterator const& other) const noexcept {
      return ptr_ != other.ptr_;
    };

    SetIterator& operator++() noexcept {
      value_type current_data = *this;
      bool found = false;
      SetNode* ptr = search_greater(root_->left_, current_data);
      if (ptr != nullptr) *this = SetIterator(ptr);
      return *this;
    };

    // SetIterator& operator--() noexcept {
    //   ptr_ = ptr_->get_previous();
    //   return *this;
    // };

    value_type& operator*() const noexcept { return ptr_->data_; };

    friend class set;

   private:
    SetNode* search_greater(const SetNode* ptr,
                            const value_type& value) const noexcept {
      SetNode* result = nullptr;
      if (value < ptr->data_) {
        result = search_greater(ptr->left_, value);
        if (result == nullptr) result = ptr;
      } else if (ptr->right_ != nullptr) {
        result = search_greater(ptr->right_, value);
      }
      return result;
    }
    SetNode* ptr_;
  } iterator;

  // constructors
  set() noexcept {
    SetNode* new_node = new SetNode({0});
    root_ = new_node;
    size_ = 0;
  }

  // set(std::initializer_list<value_type> const &items) {

  // }

  // Set Iterators
  iterator begin() {
    SetNode* ptr = root_;
    if (!empty()) {
      while (ptr->left_ != nullptr) {
        ptr = ptr->left_;
      }
    }
    return iterator(ptr);
  }

  iterator end() {
    SetNode* ptr = root_;
    if (!empty()) {
      ptr = root_->left_;
      while (ptr->right_ != nullptr) {
        ptr = ptr->right_;
      }
    }
    return iterator(ptr);
  }

  // Set Capacity
  bool empty() const noexcept { return root_->left_ == nullptr; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<std::size_t>::max() / 2 / sizeof(SetNode);
  }

  // Set Modifiers
  // std::pair<iterator, bool>
  void insert(const value_type& value) {
    root_->left_ = add_node(root_->left_, value);

    // bool success = (ptr != nullptr);
    // if (success) ++size_;
    // return success;
  }

  void print() {
    print_node(root_->left_);
    std::cout << std::endl;
  }

 private:
  SetNode* add_node(SetNode* ptr, const value_type& value) {
    SetNode* result = ptr;
    if (ptr == nullptr) {
      result = new SetNode(value);
      ++size_;
    } else if (value < ptr->data_) {
      ptr->left_ = add_node(ptr->left_, value);
    } else if (value > ptr->data_) {
      ptr->right_ = add_node(ptr->right_, value);
    }
    return result;
  }

  void print_node(SetNode* ptr) {
    if (ptr != nullptr) {
      print_node(ptr->left_);
      std::cout << ptr->data_ << " ";
      print_node(ptr->right_);
    }
  }

  SetNode* root_ = nullptr;
  size_type size_ = 0;
};

}  // namespace s21