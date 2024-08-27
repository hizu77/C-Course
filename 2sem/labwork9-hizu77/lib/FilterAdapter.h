#pragma once
#include "Adapters.h"

namespace adapters {

template <typename UnaryOperation, typename Iterator>
class filter_iterator {
public:
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using iterator_category = std::conditional_t<CheckReverse<Iterator>(), std::bidirectional_iterator_tag, std::forward_iterator_tag>;
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using reference = typename std::iterator_traits<Iterator>::reference;
    using pointer = typename std::iterator_traits<Iterator>::pointer;

    filter_iterator(Iterator cur, Iterator begin, Iterator end, UnaryOperation operation)
    : cur_(cur), begin_(begin), end_(end), operation_(operation)
    {

        while (cur_ != end_ && !operation_(*cur_)) {
            ++cur_;
        }
    }

    UnaryOperation predicate() const {
        return operation_;
    }

    Iterator end() const {
        return end_;
    }

    auto operator*() const {
        return *cur_;
    }

    filter_iterator& operator++() {
        do {
            ++cur_;
        } while (cur_ != end_ && !operation_(*cur_));

        return *this;
    }

    filter_iterator operator++(int) {
        filter_iterator temp = *this;
        ++(*this);
        return temp;
    }

    template<typename T = Iterator, typename = std::enable_if_t<CheckReverse<T>()>>
    filter_iterator& operator--() {
        do {
            --cur_;
        } while (cur_ != begin_ && !operation_(*cur_));

        return *this;
    }

    template<typename T = Iterator, typename = std::enable_if_t<CheckReverse<T>()>>
    filter_iterator operator--(int) {
        filter_iterator temp = *this;
        --(*this);
        return temp;
    }

    bool operator==(const filter_iterator& other) const {
        return (cur_ == other.cur_);
    }

    bool operator!=(const filter_iterator& other) const {
        return !(*this == other);
    }


private:
    Iterator cur_;
    Iterator begin_;
    Iterator end_;

    UnaryOperation operation_;
};

template <typename UnaryOperation>
class filter {
public:
    filter(UnaryOperation operation) : operation_(operation) {}

    template<typename Container>
    auto GetAdapter(const Container& container) {

        static_assert(!IsMap<Container>::value && !IsSet<Container>::value, "Filter only in sequence containers");
        static_assert(CheckForward<decltype(std::begin(container))>(), "Minimal iterator is forward");
        static_assert(std::is_convertible_v<UnaryOperation, bool>, "Incorrect predicate");

        return ContainerBaseRange<Container, decltype(std::begin(container)), filter_iterator<UnaryOperation,
                decltype(std::begin(container))>,
                    UnaryOperation>(container, std::begin(container), std::end(container), operation_);
    }


private:
    UnaryOperation operation_;
};

} // end of namespace adapters*/