#ifndef S21_CONTAINERS_COMMON_H
#define S21_CONTAINERS_COMMON_H

namespace s21 {

template <typename T>
class link_node {
 public:
  link_node() {};
  explicit link_node(T data)
      : data_(data), next_(nullptr), previous_(nullptr) {};
  T& get_data() const noexcept { return data_; };
  T& get_data() noexcept { return data_; };
  link_node<T>* get_next() const noexcept { return next_; };
  link_node<T>* get_previous() const noexcept { return previous_; };
  void set_data(const T data) noexcept { data_ = data; };
  void set_next(link_node<T>* ptr) noexcept { next_ = ptr; };
  void set_previous(link_node<T>* ptr) noexcept { previous_ = ptr; };

 private:
  T data_ = {0};
  link_node<T>* next_ = nullptr;
  link_node<T>* previous_ = nullptr;
};

}  // namespace s21

#endif  // S21_CONTAINERS_COMMON_H