#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <stdexcept>
#include <limits>
#include <initializer_list>

namespace s21 {

template <typename T>
class vector {
public:
    class VectorIterator {
    };
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = VectorIterator;
    using const_iterator = const VectorIterator;
    using size_type = size_t;

    vector():vector(3) {}

    vector(size_type n) {
        data_ = new value_type[n];
        size_ = 0;
        capacity_ = n;
    }

    vector(std::initializer_list<value_type> const &items) {
        data_ = new value_type[items.size()];
        size_ = items.size();
        capacity_ = size_;
        size_type i = 0;
        for (value_type item : items) {
            data_[i] = item;
            ++i;
        }
    }

    vector(const vector &other) {
        data_ = new value_type[other.size_];
        size_ = other.size_;
        capacity_ = other.capacity_;
        for (size_type i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    vector(vector &&other) {
        if(data_) {
            delete[] data_;
        }

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    vector operator=(const vector &&other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
    }

    ~vector() {
        delete[] data_;
    }

    reference at(size_type pos) {
        if (pos >= size_) {
            throw std::out_of_range("Out of range");
        }
        return data_[pos];
    }

    reference operator[](size_type pos) {
        return data_[pos];
    }

    const_reference front() {}

    const_reference back() {}

    T* data() {
        return data_;
    }
    
    iterator begin() {
        return iterator(data_);
    }

    iterator end() {
        return iterator(data_ + size_);
    }

    bool empty() {
        return size_ == 0;
    }

    size_type size() {
        return size_;
    }

    size_type max_size() {
        return std::numeric_limits<size_type>::max();
    }

    void reserve(size_type new_cap) {
        if (new_cap > capacity_) {
            value_type new_data[] = new value_type[new_cap];
            for (size_type i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_cap;
        }
    }

    size_type capacity() {
        return capacity_;
    }

    void shrink_to_fit() {
        if (size_ < capacity_) {
            value_type new_data[] = new value_type[size_];
            for (size_type i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = size_;
        }
    }

    void clear() {
        size_ = 0;
    }

    iterator insert(iterator pos, const_reference value) {

    }

    void erase(iterator pos) {}

    void push_back(const_reference value) {}

    void pop_back() {}

    void swap(vector &other) {}

private:
    size_type size_ = 0;
    size_type capacity_ = 0;
    value_type *data_ = nullptr;
};

}  // namespace s21

#endif // S21_VECTOR_H