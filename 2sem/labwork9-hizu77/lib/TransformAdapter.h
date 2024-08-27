#pragma once
#include "Adapters.h"

namespace adapters {

template <typename UnaryFunction, typename Iterator>
class transform_iterator {
public:
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using iterator_category = std::conditional_t<CheckReverse<Iterator>(), std::bidirectional_iterator_tag, std::forward_iterator_tag>;
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using reference = typename std::iterator_traits<Iterator>::reference;
    using pointer = typename std::iterator_traits<Iterator>::pointer;


    transform_iterator(Iterator cur, Iterator begin, Iterator end, UnaryFunction function)
    : iterator_(cur), function_(function) {}

    UnaryFunction functor() const {
        return function_;
    }

    auto operator*() const {
        return function_(*iterator_);
    }


    transform_iterator& operator++() {
        ++iterator_;
        return *this;
    }

    transform_iterator operator++(int) {
        transform_iterator temp = *this;
        ++(*this);
        return temp;
    }

    template<typename T = Iterator, typename = std::enable_if_t<CheckReverse<T>()>>
    transform_iterator& operator--() {
        --iterator_;
        return *this;
    }

    template<typename T = Iterator, typename = std::enable_if_t<CheckReverse<T>()>>
    transform_iterator operator--(int) {
        transform_iterator temp = *this;
        --(*this);
        return temp;
    }

    bool operator==(const transform_iterator& other) const {
        return (iterator_ == other.iterator_);
    }

    bool operator!=(const transform_iterator& other) const {
        return !(*this == other);
    }

private:
    Iterator iterator_;
    UnaryFunction function_;
};


    template<typename UnaryOperation>
    class transform {
    public:
        transform(UnaryOperation operation) : operation_(operation) {}

        template<typename Container>
        auto GetAdapter(const Container& container) {
            static_assert(!IsMap<Container>::value && !IsSet<Container>::value, "Transform only in sequence containers");
            static_assert(CheckForward<decltype(std::begin(container))>(), "Minimal iterator is forward");

            return ContainerBaseRange<Container, decltype(std::begin(container)),
                    transform_iterator<UnaryOperation, decltype(std::begin(container))>,
                            UnaryOperation>(container, std::begin(container), std::end(container), operation_);
        }

    private:
        UnaryOperation operation_;
    };

} // end of namespace adapters
