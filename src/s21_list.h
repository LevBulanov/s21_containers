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
  list() {
    node<value_type>* new_node = new node<value_type>;
    new_node->set_data({0});
    new_node->set_next(nullptr);
    new_node->set_previous(nullptr);
    ptr_begin_ = new_node;
    ptr_end_ = new_node;
    size_ = 0;
  }
  list(size_type n) : list() {
    // for (int i = 0; i < n; ++i) this->push({0});
  }
  list(std::initializer_list<value_type> const& items) : list() {
    // std::cout << "List constructor" << std::endl;
    // for (const_reference item : items) {
    //   this->push(item);
    // }
  }
  ~list() {
    this->clear();
    delete ptr_begin_;
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
    size_ = 0;
  };

  void print() const {
    std::cout << "{";
    node<value_type>* ptr = ptr_begin_;
    while (ptr != ptr_end_) {
      std::cout << ptr->get_data();
      ptr = ptr->get_next();
      if (ptr != ptr_end_) std::cout << ", ";
    }
    std::cout << "}" << std::endl;
  }
};

}  // namespace s21