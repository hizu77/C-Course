#pragma once
#include <iterator>

// NODE need key_type
// MAPPED need mapped_type
// OTHER no this types

namespace adapters {

// associative container with value_type : <const T, U>

template <typename T, typename = void>
struct IsMap : std::false_type {};

template <typename T>
struct IsMap<T, std::enable_if_t<
        std::is_same<typename T::value_type,
                std::pair<const typename T::key_type,
                        typename T::mapped_type>
        >::value>
> : std::true_type {};

// associative container with value_type == T and key_type == T

template <typename T, typename = void>
struct IsSet : std::false_type {};

template <typename T>
struct IsSet<T, std::enable_if_t<
        std::is_same<typename T::value_type,
                typename T::key_type>::value>
> : std::true_type {};


template<typename Iterator>
constexpr bool CheckReverse() {
    return std::is_base_of_v<std::bidirectional_iterator_tag, typename Iterator::iterator_category>;
}

template<typename Iterator>
constexpr bool CheckForward() {
    return std::is_base_of_v<std::forward_iterator_tag, typename Iterator::iterator_category>;
}

template <typename Container, typename BaseIterator, typename RangeIterator, typename Func = std::nullptr_t>
class ContainerBaseRange {
public:
    using iterator = RangeIterator;
    using base_iterator = BaseIterator;

    ContainerBaseRange(const Container& container, base_iterator begin, base_iterator end, Func functor)
    : container_(container), begin_(begin), end_(end), functor_(functor)
    {}

    ContainerBaseRange(const Container& container, base_iterator begin, base_iterator end)
    : container_(container), begin_(begin), end_(end)
    {}

    iterator begin() const {
        if constexpr (std::is_same_v<Func, std::nullptr_t>) {
            return iterator(begin_, begin_, end_);
        } else {
            return iterator(begin_, begin_, end_, functor_);
        }
    }

    iterator end() const {
        if constexpr (std::is_same_v<Func, std::nullptr_t>) {
            return iterator(end_, begin_, end_);
        } else {
            return iterator(end_, begin_, end_, functor_);
        }
    }

    size_t size() const {
        return container_.size();
    }


private:
    const Container& container_;
    Func functor_;
    base_iterator begin_;
    base_iterator end_;

};

template <typename Container, typename Func>
auto operator|(const Container& container, Func functor) {
    return functor.GetAdapter(container);
}

} // end of namespace adapters