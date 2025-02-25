#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>

#include "s21_containers_common.h"

namespace s21 {

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
    ListIterator(ListIterator& it) : ptr_(it.ptr_) {};
    explicit ListIterator(const ListIterator& it) : ptr_(it.ptr_) {};

    ListIterator& operator=(const ListIterator& it) {
      ptr_ = it.ptr_;
      return *this;
    }
    // ListIterator operator=(ListIterator& it) {
    //   ptr_ = it.ptr_;
    //   return *this;
    // }
    const_reference operator=(const_reference data) {
      ptr_->set_data(data);
      return data;
    }
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
    // как вариант, добавить для node признак, что это заглушка и проверять его
    // дефолт для заглушки выдает значение последнего элемента перед заглушкой
    value_type& operator*() const { return ptr_->get_data(); };

    // node<value_type>* get_ptr() const { return ptr_;}
    friend class list;

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
    const_iterator l_end = l.end();
    for (iterator it = l.begin(); it != l_end; ++it) {
      this->push_back(*it);
    };
    return *this;
  }

  // move assignment operator
  list& operator=(list&& l) {
    this->clear();
    this->swap(l);
    return *this;
  }

  const_reference front() { return *(this->begin()); }
  const_reference back() { return *(--this->end()); }

  iterator begin() const { return iterator(ptr_end_->get_next()); }
  iterator end() const { return iterator(ptr_end_); }

  bool empty() const {
    return ptr_end_->get_next() == ptr_end_ &&
           ptr_end_->get_previous() == ptr_end_;
  }

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

  iterator insert(iterator pos, const_reference value) {
    ++size_;
    node<value_type>* new_node = new node<value_type>;
    node<value_type>* prev = pos.ptr_->get_previous();
    new_node->set_data(value);
    new_node->set_next(pos.ptr_);
    pos.ptr_->set_previous(new_node);
    new_node->set_previous(prev);
    prev->set_next(new_node);
    ptr_begin_ = ptr_end_->get_next();
    --pos;
    return pos;
  }

  void push_back(const_reference value) {
    auto pos = end();
    insert(pos, value);
  }

  void pop_back() {
    if (!empty()) {
      --size_;
      node<value_type>* ptr_tmp = ptr_end_->get_previous();
      if (ptr_begin_ == ptr_tmp) ptr_begin_ = ptr_end_;
      ptr_tmp->get_previous()->set_next(ptr_tmp->get_next());
      ptr_end_->set_previous(ptr_tmp->get_previous());
      delete ptr_tmp;
    }
  }

  void push_front(const_reference value) {
    auto pos = begin();
    insert(pos, value);
  }

  void pop_front() {
    if (!empty()) {
      --size_;
      node<value_type>* ptr_tmp = ptr_end_->get_next();
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
    other.ptr_begin_ = ptr_begin_;
    other.ptr_end_ = ptr_end_;
    other.size_ = size_;
    ptr_begin_ = begin_tmp;
    ptr_end_ = end_tmp;
    size_ = size_tmp;
  }

  void reverse() {
    node<value_type>* ptr = ptr_end_->get_next();
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
    const_iterator p_end = end();
    for (iterator ptr = begin(); ptr != p_end; ++ptr) {
      std::cout << *ptr << ", ";
    }
    std::cout << "}" << std::endl;
  }

 private:
  node<value_type>* ptr_begin_;
  node<value_type>* ptr_end_;
  size_type size_;
};

}  // namespace s21