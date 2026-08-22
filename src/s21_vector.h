#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using size_type = size_t;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;

  vector();
  ~vector();
  explicit vector(size_type n);
  vector(const vector<T> &other);
  vector(vector<T> &&other);
  vector<T> &operator=(const vector<T> &other);
  vector<T> &operator=(vector<T> &&other);
  vector(std::initializer_list<value_type> const &items);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();

  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size();
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  value_type *arr_;
  size_type size_;
  size_type capacity_;
};

template <typename T>
inline vector<T>::vector() : arr_(nullptr), size_(0), capacity_(0) {}

template <typename T>
inline vector<T>::~vector() {
  delete[] arr_;
  size_ = 0;
  capacity_ = 0;
  arr_ = nullptr;
}

template <typename T>
inline vector<T>::vector(size_type n)
    : arr_(n > 0 ? new value_type[n] : nullptr), size_(n), capacity_(n) {
  for (size_t i = 0; i < n; ++i) {
    arr_[i] = T();
  }
}

template <typename T>
inline vector<T>::vector(const vector<T> &other)
    : arr_(other.size_ > 0 ? new value_type[other.capacity_] : nullptr),
      size_(other.size_),
      capacity_(other.capacity_) {
  if (arr_) {
    for (size_type i = 0; i < size_; ++i) {
      arr_[i] = other.arr_[i];
    }
  }
}

template <typename T>
inline vector<T>::vector(vector<T> &&other)
    : arr_(other.arr_), size_(other.size_), capacity_(other.capacity_) {
  other.arr_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <typename T>
inline void vector<T>::swap(vector &other) {
  value_type *temp_arr_ = arr_;
  this->arr_ = other.arr_;
  other.arr_ = temp_arr_;

  size_type temp_size_ = size_;
  this->size_ = other.size_;
  other.size_ = temp_size_;

  size_type temp_capacity_ = capacity_;
  this->capacity_ = other.capacity_;
  other.capacity_ = temp_capacity_;
}

template <typename T>
inline vector<T> &vector<T>::operator=(const vector<T> &other) {
  if (this != &other) {
    vector<T> temp(other);
    this->swap(temp);
  }
  return *this;
}

template <typename T>
inline vector<T> &vector<T>::operator=(vector<T> &&other) {
  if (this != &other) {
    delete[] arr_;
    arr_ = other.arr_;
    capacity_ = other.capacity_;
    size_ = other.size_;

    other.arr_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
inline vector<T>::vector(std::initializer_list<value_type> const &items)
    : vector(items.size()) {
  for (size_type i = 0; i < size_; ++i) {
    arr_[i] = *(items.begin() + i);
  }
}

template <typename T>
inline typename vector<T>::size_type vector<T>::size() const {
  return size_;
}
template <typename T>
inline typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
inline bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
inline typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("vector::at: index out of range");
  }
  return arr_[pos];
}

template <typename T>
inline typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return arr_[pos];
}

template <typename T>
inline typename vector<T>::const_reference vector<T>::front() {
  return *arr_;
}

template <typename T>
inline typename vector<T>::const_reference vector<T>::back() {
  return arr_[size_ - 1];
}

template <typename T>
inline typename vector<T>::value_type *vector<T>::data() {
  return arr_;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::begin() {
  return arr_;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::end() {
  return arr_ + size_;
}

template <typename T>
inline typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(T);
}

template <typename T>
inline void vector<T>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::length_error("Can't allocate");
  }
  if (size > capacity_) {
    vector tmp(size);
    for (size_type i = 0; i < size_; ++i) {
      tmp.arr_[i] = arr_[i];
    }
    tmp.size_ = size_;
    swap(tmp);
  }
}

template <typename T>
inline void vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    vector<T> tmp;
    tmp.reserve(size_);
    for (size_type i = 0; i < size_; ++i) {
      tmp.arr_[i] = arr_[i];
    }
    tmp.size_ = size_;
    swap(tmp);
  }
}

template <typename T>
inline void vector<T>::clear() {
  for (size_type i = 0; i < size_; ++i) {
    arr_[i].~T();
  }
  size_ = 0;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::insert(iterator pos,
                                                      const_reference value) {
  size_type index = pos - arr_;
  vector<value_type> tmp;

  tmp.reserve(size_ + 1);

  for (size_type i = 0; i < index; ++i) {
    tmp.arr_[i] = arr_[i];
  }

  tmp.arr_[index] = value;

  for (size_type i = index; i < size_; ++i) {
    tmp.arr_[i + 1] = arr_[i];
  }
  tmp.size_ = size_ + 1;

  *this = std::move(tmp);
  return arr_ + index;
}

template <typename T>
inline void vector<T>::erase(iterator pos) {
  size_type index = pos - arr_;

  for (size_type i = index; i < size_ - 1; ++i) {
    arr_[i] = arr_[i + 1];
  }
  --size_;
}

template <typename T>
inline void vector<T>::push_back(const_reference value) {
  if (size_ + 1 > capacity_) {
    reserve(size_ + 1);
  }
  arr_[size_] = value;
  ++size_;
}

template <typename T>
inline void vector<T>::pop_back() {
  if (size_ > 0) {
    arr_[size_ - 1].~T();
    --size_;
  }
}

template <typename T>
template <typename... Args>
inline typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                           Args &&...args) {
  size_type index = pos - arr_;
  size_type count = sizeof...(args);

  if (size_ + count > capacity_) {
    reserve(size_ + count);
  }

  for (size_type i = size_; i > index; --i) {
    arr_[i + count - 1] = std::move(arr_[i - 1]);
  }

  size_type offset = 0;
  for (const auto &value : {args...}) {
    arr_[index + offset] = value;
    ++offset;
  }

  size_ += count;
  return arr_ + index;
}

template <typename T>
template <typename... Args>
inline void vector<T>::insert_many_back(Args &&...args) {
  size_type count = sizeof...(args);
  if (size_ + count > capacity_) {
    reserve(size_ + count);
  }

  value_type tmp[] = {args...};
  for (size_type i = 0; i < count; ++i) {
    arr_[size_ + i] = tmp[i];
  }

  size_ += count;
}

}  // namespace s21

#endif
