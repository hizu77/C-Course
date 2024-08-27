#pragma once
#include "Adapters.h"

namespace adapters {
template <typename Iterator>
class take_iterator {
public:
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using iterator_category = std::conditional_t<CheckReverse<Iterator>(), std::bidirectional_iterator_tag, std::forward_iterator_tag>;
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using reference = typename std::iterator_traits<Iterator>::reference;
    using pointer = typename std::iterator_traits<Iterator>::pointer;

    take_iterator(Iterator cur, Iterator begin, Iterator end)
    : cur_(cur){}

    auto operator*() const {
        return *(cur_);
    }

    take_iterator& operator++() {
        ++cur_;
        return *this;
    }

    take_iterator operator++(int) {
        take_iterator temp = *this;
        ++(*this);

        return temp;
    }

    template<typename T = Iterator, typename = std::enable_if_t<CheckReverse<T>()>>
    take_iterator& operator--() {
        --cur_;
        return *this;
    }

    template<typename T = Iterator, typename = std::enable_if_t<CheckReverse<T>()>>
    take_iterator operator--(int) {
        take_iterator temp = *this;
        --(*this);

        return temp;
    }

    bool operator==(const take_iterator& other) const {
        return (cur_ == other.cur_);
    }

    bool operator!=(const take_iterator& other) const {
        return !(*this == other);
    }

private:
    Iterator cur_;


};

class take {
public:
    take(size_t count) : count_(count) {}

    template<typename Container>
    auto GetAdapter(const Container& container) {
        static_assert(!IsMap<Container>::value && !IsSet<Container>::value, "Take only in sequence containers");
        static_assert(CheckForward<decltype(std::begin(container))>(), "Minimal iterator is forward");

        count_ = std::min(count_, container.size());
        return ContainerBaseRange<Container, decltype(std::begin(container)), take_iterator<decltype(std::begin(container))>>
                (container, std::begin(container), std::next(std::begin(container), count_));
    }


private:
    size_t count_;
};

class drop {
public:
    drop(size_t count) : count_(count) {}

    template<typename Container>
    auto GetAdapter(const Container& container) {
        static_assert(!IsMap<Container>::value && !IsSet<Container>::value, "Drop only in sequence containers");
        static_assert(CheckForward<decltype(std::begin(container))>(), "Minimal iterator is forward");

        count_ = std::min(count_, container.size());
        return ContainerBaseRange<Container, decltype(std::begin(container)), take_iterator<decltype(std::begin(container))>>
                (container, std::next(std::begin(container), count_), std::end(container));
    }


private:
    size_t count_;
};

} // end of namespace