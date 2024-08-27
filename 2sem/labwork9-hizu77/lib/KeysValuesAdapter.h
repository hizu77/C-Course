#pragma once
#include "Adapters.h"

namespace adapters {

    struct Keys{};
    struct Values{};

    template <typename Iterator, typename Type, typename Container>
    class associative_iterator {
    public:
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        using iterator_category = std::conditional_t<CheckReverse<Iterator>(), std::bidirectional_iterator_tag, std::forward_iterator_tag>;
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using reference = typename std::iterator_traits<Iterator>::reference;
        using pointer = typename std::iterator_traits<Iterator>::pointer;


        associative_iterator(Iterator cur, Iterator begin, Iterator end)
                : cur_(cur)
        {}

        auto operator*() const {
            if constexpr (IsMap<Container>::value) {
                if constexpr (std::is_same_v<Type, Keys>) {
                    return cur_->first;
                } else {
                    return cur_->second;
                }
            } else {
                return *cur_;
            }
        }


        associative_iterator& operator++() {
            ++cur_;
            return *this;
        }

        associative_iterator operator++(int) {
            associative_iterator temp = *this;
            ++(*this);
            return temp;
        }

        template<typename T = Iterator, typename = std::enable_if_t<CheckReverse<T>()>>
        associative_iterator& operator--() {
            --cur_;
            return *this;
        }

        template<typename T = Iterator, typename = std::enable_if_t<CheckReverse<T>()>>
        associative_iterator operator--(int) {
            associative_iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const associative_iterator& other) const {
            return (cur_ == other.cur_);
        }

        bool operator!=(const associative_iterator& other) const {
            return !(*this == other);
        }


    private:
        Iterator cur_;
    };

    class keys {
    public:
        keys() = default;

        template <typename Container>
        auto GetAdapter(const Container& container) {
            static_assert(IsMap<Container>::value || IsSet<Container>::value, "Keys only in associative containers");
            static_assert(CheckForward<decltype(std::begin(container))>(), "Minimal iterator is forward");

            return ContainerBaseRange<Container, decltype(std::begin(container)), associative_iterator<decltype(std::begin(container)), Keys, Container>>
                    (container, std::begin(container), std::end(container));
        }
    };

    class values {
    public:
        values() = default;

        template <typename Container>
        auto GetAdapter(const Container& container) {
            static_assert(IsMap<Container>::value || IsSet<Container>::value, "Values only in associative containers");
            static_assert(CheckForward<decltype(std::begin(container))>(), "Minimal iterator is forward");

            return ContainerBaseRange<Container, decltype(std::begin(container)), associative_iterator<decltype(std::begin(container)), Values, Container>>
                    (container, std::begin(container), std::end(container));
        }
    };

} // end of namespace adapters