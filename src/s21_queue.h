#ifndef S21_QUEUE
#define S21_QUEUE
#include <cstddef>
#include <initializer_list>

#include "s21_vector.h"

namespace s21 {
template <typename T>
class queue {
 private:
  vector<T> data_;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue<T> &q);
  queue(queue<T> &&q);
  ~queue();
  queue &operator=(queue<T> &&q);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(queue &other);
};

template <typename T>
inline queue<T>::queue() = default;
template <typename T>
inline queue<T>::queue(std::initializer_list<value_type> const &items)
    : data_(items){};
template <typename T>
inline queue<T>::queue(const queue<T> &q) : data_(q.data_) {}
template <typename T>
inline queue<T>::queue(queue<T> &&q) : data_(std::move(q.data_)) {}
template <typename T>
inline queue<T>::~queue() = default;
template <typename T>
inline queue<T> &queue<T>::operator=(queue<T> &&q) {
  if (this != &q) {
    data_ = std::move(q.data_);
  }
  return *this;
}
template <typename T>
inline typename queue<T>::const_reference queue<T>::front() {
  if (empty()) throw std::out_of_range("queue::front: empty queue");
  return data_.front();
}

template <typename T>
inline typename queue<T>::const_reference queue<T>::back() {
  if (empty()) throw std::out_of_range("queue::back: empty queue");
  return data_.back();
}
template <typename T>
inline bool queue<T>::empty() {
  return data_.empty();
}

template <typename T>
inline typename queue<T>::size_type queue<T>::size() {
  return data_.size();
}

template <typename T>
inline void queue<T>::push(const_reference value) {
  data_.push_back(value);
}

template <typename T>
inline void queue<T>::pop() {
  if (!empty()) {
    data_.erase(data_.begin());
  }
}

template <typename T>
inline void queue<T>::swap(queue &other) {
  data_.swap(other.data_);
}
}  // namespace s21

#endif
