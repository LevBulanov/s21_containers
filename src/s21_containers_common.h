#ifndef S21_CONTAINERS_COMMON_H
#define S21_CONTAINERS_COMMON_H

namespace s21 {

template <typename value_type>
class node {
 public:
  node(){};
  explicit node(value_type data)
      : data_(data), next_(nullptr), previous_(nullptr){};
  value_type& get_data() const noexcept { return data_; };
  value_type& get_data() noexcept { return data_; };
  node<value_type>* get_next() const noexcept { return next_; };
  node<value_type>* get_previous() const noexcept { return previous_; };
  void set_data(const value_type data) noexcept { data_ = data; };
  void set_next(node<value_type>* ptr) noexcept { next_ = ptr; };
  void set_previous(node<value_type>* ptr) noexcept { previous_ = ptr; };

 private:
  value_type data_ = {0};
  node<value_type>* next_ = nullptr;
  node<value_type>* previous_ = nullptr;
};

}  // namespace s21

#endif  // S21_CONTAINERS_COMMON_H