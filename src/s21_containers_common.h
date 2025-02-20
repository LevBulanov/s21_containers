#ifndef S21_CONTAINERS_COMMON_H
#define S21_CONTAINERS_COMMON_H

namespace s21 {

template <typename value_type>
class node {
 private:
  value_type data_;
  node<value_type>* next_;
  node<value_type>* previous_;

 public:
  node() {};
  explicit node(value_type data)
      : data_(data), next_(nullptr), previous_(nullptr) {};
  value_type& get_data() const { return data_; };
  value_type& get_data() { return data_; };
  node<value_type>* get_next() const { return next_; };
  node<value_type>* get_previous() const { return previous_; };
  void set_data(const value_type data) { data_ = data; };
  void set_next(node<value_type>* ptr) { next_ = ptr; };
  void set_previous(node<value_type>* ptr) { previous_ = ptr; };
};

}  // namespace s21

#endif  // S21_CONTAINERS_COMMON_H