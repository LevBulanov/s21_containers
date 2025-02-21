#include <initializer_list>
#include <stdexcept>
#include <cstddef>

template <typename T, std::size_t N>
class array {
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = T *;
        using const_iterator = const T *;
        using size_type = size_t;

        //constructors
        array() = default;
        array(std::initializer_list<value_type> init) {
            if (init.size() > N) {
                throw std::out_of_range("Too much of elements in the initializer list");
            }
            size_t i = 0;
            for (auto it = init.begin(); it != init.end(); ++it) {
                data_[i++] = *it;
            }
        }
        array(const array &a) {
            if (a.size() > N) {
                throw std::out_of_range("Too much of elements in source array");
            }
            size_t i = 0;
            for (auto it = a.begin(); it != a.end(); ++it) {
                data_[i++] = *it;
            }
        }
        array(array &&a) {
            if (a.size() > N) {
                throw std::out_of_range("Too much of elements in source array");
            }
            for (size_t i = 0; i < N; ++i) {
                data_[i] = std::move(a.data_[i]);
            }
        }

        //destructor
        ~array() = default;

        //overload =
        array& operator=(array &&a) {
            if (a.size() > N) {
                throw std::out_of_range("Too much of elements in source array"); 
            }
            if (this != &a) {
                for (size_t i = 0; i < N; ++i) {
                    data_[i] = std::move(a.data_[i]);
                }
            }
            return *this;
        }

        //Element access
        reference at(size_type pos) {
            if (pos >= N) {
                throw std::out_of_range("index out of range");
            } 
            return data_[pos];
        } 

        reference operator[](size_type pos) {
            return data_[pos];
        }

        const_reference front() const {
            return data_[0];
        }

        const_reference back() const {
            return data_[N - 1];
        }

        iterator data() {
            return data_;
        } 

        iterator begin() {
            return data_;
        }

        iterator end() {
            return data_ + N;
        }

        //Capacity
        bool empty() {
            return (N == 0);
        }

        size_type size() {
            return N;
        }

        size_type max_size() {
            return N;
        }


    //Modifiers
    void swap(array& other) {
        array temp(other);
        other = *this;
        *this = std::move(temp);
    }

    void fill(const_reference value) {
        for (size_t i = 0; i < N; ++i) {
            data_[i] = value;
        }
    }

    private:
        value_type data_[N];
};