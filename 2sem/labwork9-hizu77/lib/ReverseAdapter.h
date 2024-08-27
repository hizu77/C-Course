#pragma once
#include "Adapters.h"

namespace adapters {
template <typename Iterator>
class reverse_iterator {
public:
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using reference = typename std::iterator_traits<Iterator>::reference;
    using pointer = typename std::iterator_traits<Iterator>::pointer;

    reverse_iterator(Iterator cur, Iterator begin, Iterator end)
    : cur_(cur) {}

    auto operator*() const {
        return *(std::prev(cur_));
    }

    reverse_iterator& operator++() {
        --cur_;

        return *this;
    }

    reverse_iterator operator++(int) {
        reverse_iterator temp = *this;
        --(*this);

        return temp;
    }

    reverse_iterator& operator--() {
        ++cur_;

        return *this;
    }

    reverse_iterator operator--(int) {
        reverse_iterator temp = *this;
        ++(*this);

        return temp;
    }

    bool operator==(const reverse_iterator& other) {
        return cur_ == other.cur_;
    }

    bool operator!=(const reverse_iterator& other) {
        return !(*this == other);
    }

private:
    Iterator cur_;
};

class reverse {
public:
    reverse() = default;

    template<typename Container>
    auto GetAdapter(const Container& container) {
        static_assert(!IsMap<Container>::value && !IsSet<Container>::value, "Reverse only in sequence containers");
        static_assert(CheckReverse<decltype(std::begin(container))>(), "Reverse need minimal bidirectional iterator");

        return ContainerBaseRange<Container, decltype(std::begin(container)), reverse_iterator<decltype(std::begin(container))>>
                (container, std::end(container), std::begin(container));
    }
};



} // end of namespace adapters