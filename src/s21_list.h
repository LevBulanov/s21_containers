#ifndef S21_CONTAINERS_LIST_H
#define S21_CONTAINERS_LIST_H
#include <initializer_list>
#include <limits>
// #include <stdexcept>

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
    ListIterator(const ListIterator& it) : ptr_(it.ptr_) {};

    ListIterator& operator=(const ListIterator& it) noexcept {
      ptr_ = it.ptr_;
      return *this;
    }

    bool operator==(ListIterator const& other) const noexcept {
      return ptr_ == other.ptr_;
    };

    bool operator!=(ListIterator const& other) const noexcept {
      return ptr_ != other.ptr_;
    };

    ListIterator& operator++() noexcept {
      ptr_ = ptr_->get_next();
      return *this;
    };

    ListIterator& operator--() noexcept {
      ptr_ = ptr_->get_previous();
      return *this;
    };

    value_type& operator*() const noexcept { return ptr_->get_data(); };

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
      push_back(item);
    }
  }
  // copy constructor
  list(const list& l) : list() { *this = l; }
  // move constructor
  list(list&& l) noexcept : list() { *this = std::move(l); }
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
      push_back(*it);
    };
    return *this;
  }

  // move assignment operator
  list& operator=(list&& l) noexcept {
    clear();
    swap(l);
    return *this;
  }

  // List Element access
  const_reference front() const noexcept { return *(begin()); }
  const_reference back() const noexcept { return *(--end()); }

  // List Iterators
  iterator begin() const noexcept { return iterator(ptr_end_->get_next()); }
  iterator end() const noexcept { return iterator(ptr_end_); }

  // List Capacity
  bool empty() const noexcept {
    return ptr_end_->get_next() == ptr_end_ &&
           ptr_end_->get_previous() == ptr_end_;
  }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<std::size_t>::max() / 2 /
           sizeof(node<value_type>);
  }

  // List Modifiers
  void clear() {
    while (!empty()) {
      erase(begin());
    };
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
    --pos;
    return pos;
  }

  void erase(iterator pos) {
    const_iterator it_end = end();
    if (!empty() && pos != it_end) {
      --size_;
      node<value_type>* prev = pos.ptr_->get_previous();
      node<value_type>* next = pos.ptr_->get_next();
      prev->set_next(next);
      next->set_previous(prev);
      delete pos.ptr_;
    }
  }

  void push_back(const_reference value) {
    auto pos = end();
    insert(pos, value);
  }

  void pop_back() {
    auto pos = --end();
    erase(pos);
  }

  void push_front(const_reference value) {
    auto pos = begin();
    insert(pos, value);
  }

  void pop_front() {
    auto pos = begin();
    erase(pos);
  }

  void swap(list& other) noexcept {
    node<value_type>* end_tmp = other.ptr_end_;
    size_type size_tmp = other.size_;
    other.ptr_end_ = ptr_end_;
    other.size_ = size_;
    ptr_end_ = end_tmp;
    size_ = size_tmp;
  }

  void merge(list& other) noexcept {
    iterator this_it = begin();
    iterator other_it = other.begin();
    iterator move_it = other_it;
    const_iterator end_this_it = end();
    const_iterator end_other_it = other.end();
    while (this_it != end_this_it && other_it != end_other_it) {
      if (*this_it <= *other_it) {
        ++this_it;
      } else {
        ++size_;
        --other.size_;
        move_it = other_it;
        ++other_it;
        transfer(this_it, move_it);
      }
    }
    if (other_it != end_other_it) splice(this_it, other);
  }

  void splice(const_iterator pos, list& other) noexcept {
    iterator other_it = other.begin();
    iterator move_it = other_it;
    const_iterator end_it = other.end();
    while (other_it != end_it) {
      move_it = other_it;
      ++other_it;
      transfer(pos, move_it);
      ++size_;
      --other.size_;
    }
  }

  void reverse() noexcept {
    node<value_type>* ptr = ptr_end_->get_next();
    node<value_type>* ptr_tmp = nullptr;
    while (ptr != ptr_end_) {
      ptr_tmp = ptr->get_next();
      ptr->set_next(ptr->get_previous());
      ptr->set_previous(ptr_tmp);
      ptr = ptr_tmp;
    }
    ptr_tmp = ptr_end_->get_next();
    ptr_end_->set_next(ptr_end_->get_previous());
    ptr_end_->set_previous(ptr_tmp);
  }

  void unique() {
    if (!empty()) {
      iterator it = begin();
      iterator del_it = it;
      const_iterator it_end = end();
      value_type data = *it;
      ++it;
      while (it != it_end) {
        if (*it == data) {
          del_it = it;
          ++it;
          erase(del_it);
        } else {
          data = *it;
          ++it;
        }
      }
    }
  }

  void sort() { qsort(begin(), end()); };

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    size_type tmp = size_;
    (insert(pos, std::forward<Args>(args)), ...);
    iterator result = pos;
    for (; tmp < size_; ++tmp) --result;
    return result;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    iterator pos = end();
    (insert(pos, std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    iterator pos = begin();
    (insert(pos, std::forward<Args>(args)), ...);
  }

 private:
  void transfer(const_iterator pos, const_iterator src) noexcept {
    src.ptr_->get_previous()->set_next(src.ptr_->get_next());
    src.ptr_->get_next()->set_previous(src.ptr_->get_previous());

    src.ptr_->set_next(pos.ptr_);
    src.ptr_->set_previous(pos.ptr_->get_previous());

    pos.ptr_->get_previous()->set_next(src.ptr_);
    pos.ptr_->set_previous(src.ptr_);
  }

  void qsort(const_iterator begin, const_iterator end) noexcept {
    iterator op = end;
    --op;
    if (op != begin) {
      iterator it = begin;
      while (it != op) {
        iterator tmp = it;
        ++it;
        if (*tmp > *op) {
          transfer(end, tmp);
        }
      }
      if (op != this->begin()) qsort(this->begin(), op);
      qsort(op, end);
    }
  }

  node<value_type>* ptr_end_;
  size_type size_;
};

}  // namespace s21

#endif  // S21_CONTAINERS_LIST_H