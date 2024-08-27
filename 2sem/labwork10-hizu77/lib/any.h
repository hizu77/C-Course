#pragma once
#include <memory>


class any {
public:
    any() = default;

    template<typename T>
    any(const T& other) {
        value_ = std::unique_ptr<any_base>(new inner<T>(other));
    }

    template<typename T>
    any& operator=(const T& other) {
        value_ = std::make_unique<inner<T>>(other);

        return *this;
    }

    any(const any& rhs) {
        value_ = std::unique_ptr<any_base>(rhs.value_->Clone());
    }

    any& operator=(any rhs) {
        value_.swap(rhs.value_);

        return *this;
    }

    ~any() {
        value_ = nullptr;
    }

    template<typename T>
    T& Cast() {
        if (typeid(T) != value_->get_type()) {
            throw std::bad_cast();
        }

        return static_cast<inner<T>*>(value_.get())->value_;
    }

private:
    class any_base {
    public:
        virtual any_base* Clone() = 0;
        virtual const std::type_info& get_type() const = 0;
        virtual ~any_base() = default;
    };

    template<typename T>
    class inner : public any_base {
    public:
        inner(const T& val) : value_(val) {}

        const std::type_info& get_type() const override {
            return typeid(T);
        }

        any_base* Clone() override {
            return new inner(value_);
        }

        T value_;
    };

    std::unique_ptr<any_base> value_ = nullptr;
};
