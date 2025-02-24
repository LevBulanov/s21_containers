#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>

#include "s21_containers_common.h"

namespace s21 {

// template <typename value_type>
// class ListIterator
//     : public std::iterator<std:: , value_type> {
//  public:

//  private:
//   node<value_type>* ptr_;
// };

template <typename T>
class list {
 public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef class ListIterator {
   public:
    explicit ListIterator(node<value_type>* p) : ptr_(p) {};
    explicit ListIterator(const ListIterator& it) : ptr_(it.ptr_) {};

    ListIterator& operator=(const ListIterator& it) { ptr_ = it.ptr_; }
    bool operator==(ListIterator const& other) const {
      return ptr_ == other.ptr_;
    };
    bool operator!=(ListIterator const& other) const {
      return ptr_ != other.ptr_;
    };
    ListIterator& operator++() {
      ptr_ = ptr_->get_next();
      return *this;
    };
    ListIterator& operator--() {
      ptr_ = ptr_->get_previous();
      return *this;
    };
    value_type& operator*() const { return ptr_->get_data(); };

   private:
    node<value_type>* ptr_;
  } iterator;
  typedef const iterator const_iterator;

  // default constructor, creates empty stack
  list() {
    node<value_type>* new_node = new node<value_type>;
    new_node->set_data({0});
    new_node->set_next(new_node);
    new_node->set_previous(new_node);
    ptr_begin_ = new_node;
    ptr_end_ = new_node;
    size_ = 0;
  }
  // parameterized constructor, creates the list of size n
  explicit list(size_type n) : list() {
    for (int i = 0; i < n; ++i) this->push_front({0});
  }
  // initializer list constructor
  list(std::initializer_list<value_type> const& items) : list() {
    for (const_reference item : items) {
      this->push_back(item);
    }
  }
  // copy constructor
  list(const list& l) : list() { *this = l; }
  // move constructor
  list(list&& l) : list() { *this = std::move(l); }
  // destructor
  ~list() {
    this->clear();
    delete ptr_end_;
  }
  // copy assignment operator
  list& operator=(const list& l) {
    this->clear();
    node<value_type>* ptr_l = l.ptr_begin_;
    if (!l.empty()) {
      while (ptr_l != l.ptr_end_) {
        this->push_back(ptr_l->get_data());
        ptr_l = ptr_l->get_next();
      };
    };
    return *this;
  }

  // move assignment operator
  list& operator=(list&& l) {
    this->clear();
    this->swap(l);
    return *this;
  }

  iterator begin() const { return iterator(ptr_end_->get_next()); }
  iterator end() const { return iterator(ptr_end_); }

  bool empty() const { return ptr_begin_ == ptr_end_; }

  size_type size() const { return size_; }

  void clear() {
    node<value_type>* ptr_tmp = ptr_begin_;
    while (ptr_begin_ != ptr_end_) {
      ptr_begin_ = ptr_tmp->get_next();
      delete ptr_tmp;
      ptr_tmp = ptr_begin_;
    }
    ptr_end_->set_next(ptr_end_);
    ptr_end_->set_previous(ptr_end_);
    size_ = 0;
  }

  void push_back(const_reference value) {
    ++size_;
    node<value_type>* new_node = new node<value_type>;
    new_node->set_data(value);
    if (ptr_begin_ == ptr_end_) ptr_begin_ = new_node;
    ptr_end_->get_previous()->set_next(new_node);
    new_node->set_previous(ptr_end_->get_previous());
    ptr_end_->set_previous(new_node);
    new_node->set_next(ptr_end_);
  }

  void pop_back() {
    if (ptr_begin_ != ptr_end_) {
      --size_;
      node<value_type>* ptr_tmp = ptr_end_->get_previous();
      if (ptr_begin_ == ptr_tmp) ptr_begin_ = ptr_end_;
      ptr_tmp->get_previous()->set_next(ptr_tmp->get_next());
      ptr_end_->set_previous(ptr_tmp->get_previous());
      delete ptr_tmp;
    }
  }

  void push_front(const_reference value) {
    ++size_;
    node<value_type>* new_node = new node<value_type>;
    new_node->set_data(value);
    new_node->set_next(ptr_begin_);
    new_node->set_previous(ptr_end_);
    ptr_begin_->set_previous(new_node);
    ptr_end_->set_next(new_node);
    ptr_begin_ = new_node;
  }

  void pop_front() {
    if (ptr_begin_ != ptr_end_) {
      --size_;
      node<value_type>* ptr_tmp = ptr_begin_;
      ptr_begin_ = ptr_tmp->get_next();
      ptr_tmp->get_next()->set_previous(ptr_end_);
      ptr_end_->set_next(ptr_tmp->get_next());
      delete ptr_tmp;
    }
  }

  void swap(list& other) {
    node<value_type>* begin_tmp = other.ptr_begin_;
    node<value_type>* end_tmp = other.ptr_end_;
    size_type size_tmp = other.size_;
    other.ptr_begin_ = this->ptr_begin_;
    other.ptr_end_ = this->ptr_end_;
    other.size_ = this->size_;
    this->ptr_begin_ = begin_tmp;
    this->ptr_end_ = end_tmp;
    this->size_ = size_tmp;
  }

  void reverse() {
    node<value_type>* ptr = ptr_begin_;
    node<value_type>* ptr_tmp = nullptr;
    while (ptr != ptr_end_) {
      ptr_tmp = ptr->get_next();
      ptr->set_next(ptr->get_previous());
      ptr->set_previous(ptr_tmp);
      ptr = ptr_tmp;
    }
    ptr_begin_ = ptr_end_->get_previous();
    ptr_tmp = ptr_end_->get_next();
    ptr_end_->set_next(ptr_end_->get_previous());
    ptr_end_->set_previous(ptr_tmp);
  }

  void print() const {
    // std::cout << "{";
    // node<value_type>* ptr = ptr_begin_;
    // while (ptr != ptr_end_) {
    //   std::cout << ptr->get_data();
    //   ptr = ptr->get_next();
    //   if (ptr != ptr_end_) std::cout << ", ";
    // };
    // std::cout << "}" << std::endl;
    std::cout << "{";
    iterator ptr = this->begin();
    while (ptr != this->end()) {
      std::cout << *ptr;
      ++ptr;
      if (ptr != this->end()) std::cout << ", ";
    };
    std::cout << "}" << std::endl;
  }

 private:
  node<value_type>* ptr_begin_;
  node<value_type>* ptr_end_;
  size_type size_;
};

}  // namespace s21