#include <initializer_list>
#include <iostream>
#include <stdexcept>

#include "s21_containers_common.h"

namespace s21 {

template <typename value_type>
class list {
 private:
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  node<value_type>* ptr_begin_;
  node<value_type>* ptr_end_;
  size_type size_;

 public:
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
    // std::cout << "List constructor" << std::endl;
    for (const_reference item : items) {
      this->push_back(item);
    }
  }
  // destructor
  ~list() {
    this->clear();
    delete ptr_end_;
  }

  bool empty() const { return ptr_begin_ == ptr_end_; };

  size_type size() const { return size_; };

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
  };

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
    std::cout << "{";
    node<value_type>* ptr = ptr_begin_;
    while (ptr != ptr_end_) {
      std::cout << ptr->get_data();
      // std::cout << "data " << ptr->get_data() << " prev "
      //           << ptr->get_previous()->get_data() << " next "
      //           << ptr->get_next()->get_data() << std::endl;
      ptr = ptr->get_next();
      if (ptr != ptr_end_) std::cout << ", ";
    };
    // std::cout << "END: " << ptr_end_->get_data() << " prev "
    //           << ptr_end_->get_previous()->get_data() << " next "
    //           << ptr_end_->get_next()->get_data() << std::endl;
    std::cout << "}" << std::endl;
  }
};

}  // namespace s21