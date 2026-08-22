#ifndef S21_STACK_H
#define S21_STACK_H

#include "s21_list.h"

namespace s21 {

template <typename T>
class stack {
 private:
  list<T> container_;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  stack() = default;

  stack(std::initializer_list<value_type> const& items) {
    for (auto it = items.begin(); it != items.end(); ++it) {
      container_.push_back(*it);
    }
  }

  stack(const stack& s) : container_(s.container_) {}

  stack(stack&& s) noexcept : container_(std::move(s.container_)) {}

  ~stack() = default;

  stack& operator=(stack&& s) noexcept {
    container_ = std::move(s.container_);
    return *this;
  }

  stack& operator=(const stack& s) {
    container_ = s.container_;
    return *this;
  }

  const_reference top() const { return container_.back(); }

  reference top() { return container_.back(); }

  bool empty() const { return container_.empty(); }

  size_type size() const { return container_.size(); }

  void push(const_reference value) { container_.push_back(value); }

  void pop() {
    if (empty()) {
      throw std::out_of_range("Stack is empty");
    }
    container_.pop_back();
  }

  void swap(stack& other) noexcept { container_.swap(other.container_); }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    container_.insert_many_back(args...);
  }
};

}  // namespace s21

#endif
