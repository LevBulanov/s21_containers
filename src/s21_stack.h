#ifndef SRC_S21_STACK_H
#define SRC_S21_STACK_H

#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace s21 {

template <typename value_type>
class node {
 private:
  value_type data_;
  node<value_type>* next_;
  node<value_type>* previous_;

 public:
  node() {};
  node(value_type data) : data_(data), next_(nullptr), previous_(nullptr) {};
  value_type get_data() const { return data_; };
  value_type& get_data() { return data_; };
  node<value_type>* get_next() const { return next_; };
  node<value_type>* get_previous() const { return previous_; };
  void set_data(value_type data) { data_ = data; };
  void set_next(node<value_type>* ptr) { next_ = ptr; };
  void set_previous(node<value_type>* ptr) { previous_ = ptr; };
};

template <typename value_type>
class stack {
 private:
  node<value_type>* ptr_top;
  int size_;

 public:
  stack() : ptr_top(nullptr), size_(0) {};
  stack(std::initializer_list<value_type> const& items) : stack() {
    for (const value_type& item : items) {
      this->push(item);
    }
  };
  stack(const stack& s) : stack() {
    std::cout << "Copy constructor" << std::endl;
    node<value_type>* ptr_s = s.ptr_top;
    if (s.ptr_top != nullptr) {
      while (ptr_s->get_next() != nullptr) {
        ptr_s = ptr_s->get_next();
      };
      while (ptr_s != nullptr) {
        ++size_;
        this->push(ptr_s->get_data());
        ptr_s = ptr_s->get_previous();
      };
    };
  };
  ~stack() {
    node<value_type>* ptr = ptr_top;
    while (ptr_top != nullptr) {
      ptr_top = ptr->get_next();
      delete ptr;
      ptr = ptr_top;
    }
  };

  bool empty() const { return size_ == 0; };
  int size() const { return size_; };

  void push(const value_type& value) {
    ++size_;
    node<value_type>* new_node = new node<value_type>;
    new_node->set_data(value);
    new_node->set_next(ptr_top);
    new_node->set_previous(nullptr);
    if (ptr_top != nullptr) ptr_top->set_previous(new_node);
    ptr_top = new_node;
  }

  const value_type& top() {
    if (ptr_top == nullptr) {
      throw std::range_error("Stack is empty");
    }
    return ptr_top->get_data();
  };

  void pop() {
    if (size_ != 0) {
      --size_;
      node<value_type>* tmp = ptr_top;
      ptr_top = ptr_top->get_next();
      delete tmp;
      if (ptr_top != nullptr) ptr_top->set_previous(nullptr);
    }
  };

  void print() {
    std::cout << "{";
    node<value_type>* ptr = ptr_top;
    while (ptr != nullptr) {
      std::cout << ptr->get_data();
      ptr = ptr->get_next();
      if (ptr != nullptr) std::cout << ", ";
    }
    std::cout << "}" << std::endl;
  }
};

}  // namespace s21

#endif  // SRC_S21_STACK_H