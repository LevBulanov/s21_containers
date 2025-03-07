#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace s21 {

template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // constructors
  array() = default;

  array(std::initializer_list<value_type> const &items) {
    if (items.size() > N) {
      throw std::out_of_range("Too many elements in the initializer list");
    }
    size_t i = 0;
    for (auto it = items.begin(); it != items.end(); ++it) {
      data_[i++] = *it;
    }
  }

  array(const array &a) {
    for (size_t i = 0; i < N; ++i) {
      data_[i] = a.data_[i];
    }
  }

  array(array &&a) {
    for (size_t i = 0; i < N; ++i) {
      data_[i] = std::move(a.data_[i]);
    }
  }

  // destructor
  ~array() = default;

  // overload =
  array &operator=(array &&a) {
    if (this != &a) {
      for (size_t i = 0; i < N; ++i) {
        data_[i] = std::move(a.data_[i]);
      }
    }
    return *this;
  }

  // Element access
  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }

  const_reference front() const { return data_[0]; }

  const_reference back() const { return data_[N - 1]; }

  iterator data() { return data_; }

  iterator begin() { return data_; }

  iterator end() { return data_ + N; }

  // Capacity
  bool empty() { return (N == 0); }

  size_type size() { return N; }

  size_type max_size() { return N; }

  // Modifiers
  void swap(array &other) {
    array temp(other);
    for (size_t i = 0; i < N; ++i) {
      other.data_[i] = data_[i];
      data_[i] = temp.data_[i];
    }
  }

  void fill(const_reference value) {
    for (size_t i = 0; i < N; ++i) {
      data_[i] = value;
    }
  }

 private:
  value_type data_[N];
};

}  // namespace s21