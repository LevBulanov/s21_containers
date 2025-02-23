#include <initializer_list>
#include <stdexcept>
#include <cstddef> 
#include <list>

template <typename T>
class queue {
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using size_type = size_t;

    public:
        //constructors, think about exceptions 
        queue() = default;
        queue(std::initializer_list<value_type> const &items) : container_(items) {}
        queue(const queue &q) : container_(q) {}
        queue(queue &&q) noexcept : container_(std::move(q.container_)) {}

        //destructor
        ~queue() = default;


        queue& operator=(queue &&q) {
            if (this != &q) {
                container_ = std::move(q.container_);
            }
            return *this;
        }

        const_reference front() const {
            return container_.front();
        }

        const_reference back() const {
            return container_.back();
        }

    private:
        std::list<value_type> container_;
};