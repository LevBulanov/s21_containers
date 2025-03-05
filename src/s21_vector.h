#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  class VectorIterator {
   public:
    VectorIterator(T* ptr = nullptr) : ptr_(ptr) {}

    reference operator*() const { return *ptr_; }

    VectorIterator& operator++() {
      ++ptr_;
      return *this;
    }

    VectorIterator& operator--() {
      --ptr_;
      return *this;
    }

    bool operator==(const VectorIterator& other) const {
      return ptr_ == other.ptr_;
    }

    bool operator!=(const VectorIterator& other) const {
      return ptr_ != other.ptr_;
    }

   private:
    T* ptr_ = nullptr;

    friend class vector;
  };
  using iterator = VectorIterator;
  using const_iterator = const VectorIterator;

  vector() : vector(3) {}

  vector(size_type n) : size_(0), capacity_(n) { data_ = new value_type[n]; }

  vector(std::initializer_list<value_type> const& items)
      : size_(items.size()), capacity_(size_) {
    data_ = new value_type[items.size()];
    size_type i = 0;
    for (value_type item : items) {
      data_[i] = item;
      ++i;
    }
  }

  vector(const vector& other) : size_(other.size_), capacity_(other.capacity_) {
    data_ = new value_type[other.size_];
    for (size_type i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }

  vector(vector&& other) : size_(other.size_), capacity_(other.capacity_) {
    if (data_) {
      delete[] data_;
    }

    data_ = other.data_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  vector operator=(vector&& other) {
    if (data_) {
      delete[] data_;
    }

    data_ = other.data_;
    size_ = other.size_;
    other.data_ = nullptr;
    other.size_ = 0;

    return *this;
  }

  ~vector() { delete[] data_; }

  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Out of range");
    }
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }

  const_reference front() { return data_[0]; }

  const_reference back() { return data_[size_ - 1]; }

  T* data() { return data_; }

  iterator begin() { return iterator(data_); }

  iterator end() { return iterator(data_ + size_); }

  bool empty() { return size_ == 0; }

  size_type size() { return size_; }

  size_type max_size() { return std::numeric_limits<size_type>::max(); }

  void reserve(size_type new_cap) {
    if (new_cap <= capacity_) {
      return;
    }

    value_type* new_data = new value_type[new_cap];
    for (size_type i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
  }

  size_type capacity() { return capacity_; }

  void shrink_to_fit() {
    if (size_ < capacity_) {
      value_type *new_data = new value_type[size_];
      for (size_type i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
      }
      delete[] data_;
      data_ = new_data;
      capacity_ = size_;
    }
  }

  void clear() { size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    size_type index = (pos.ptr_ - data_);

    if (size_ == capacity_) {
        reserve(capacity_ * 2);
    }

    for (size_type i = size_; i > index; --i) {
      data_[i] = data_[i - 1];
    }

    data_[index] = value;

    ++size_;

    return iterator(data_ + index);
  }

  void erase(iterator pos) {
    size_type index = (pos.ptr_ - data_);

    for (size_type i = index; i < size_ - 1; ++i) {
      data_[i] = data_[i + 1];
    }

    --size_;
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(capacity_ * 2);
    }

    data_[size_] = value;
    ++size_;
  }

  void pop_back() {
    if (size_ > 0) {
      --size_;
    }
  }

  void swap(vector& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    size_type index = (pos.ptr_ - data_);
    size_type i = 0;
    for (auto&& arg : {std::forward<Args>(args)...}) {
      insert(iterator(data_ + index + i), arg);
      ++i;
    }

    return iterator(data_ + index);
  }

  template <typename... Args>
  iterator insert_many_back(Args&&... args) {
    size_type i = 0;
    for (auto&& arg : {std::forward<Args>(args)...}) {
      push_back(arg);
      ++i;
    }

    return iterator(data_ + size_ - i);
  }

 private:
  size_type size_;
  size_type capacity_;
  value_type* data_ = nullptr;
};

}  // namespace s21

#endif  // S21_VECTOR_H