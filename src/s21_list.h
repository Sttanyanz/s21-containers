#ifndef S21_CONTAINERS_SRC_S21_LIST_H_
#define S21_CONTAINERS_SRC_S21_LIST_H_
#include <cstdio>
#include <cstdlib>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <typeinfo>

namespace s21 {

template <class T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

 private:
  class node;
  node* sentinel;
  size_type size_;

 public:
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l) noexcept;
  ~list();
  list<T>& operator=(const list<T>& l);
  list<T>& operator=(list<T>&& l) noexcept;

  const_reference front() const;
  const_reference back() const;
  reference front();
  reference back();
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);

  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);

  void splice(const_iterator pos, list& other);

  void reverse();
  void unique();
  void sort();
  bool operator==(const list& other) const;

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
};

template <class T>
inline list<T>::list() : size_(0) {
  sentinel = new node();
  sentinel->next_ = sentinel;
  sentinel->prev_ = sentinel;
}

template <class T>
inline list<T>::list(size_type n) : list() {
  for (int i = 0; i < (int)n; i++) {
    push_back((value_type)0);
  }
}

template <class T>
inline list<T>::list(std::initializer_list<value_type> const& items) : list() {
  for (auto item : items) {
    push_back(item);
  }
}

template <class T>
inline list<T>::list(const list<T>& l) : list() {
  node* n = l.sentinel->next_;
  while (n != l.sentinel) {
    push_back(n->data_);
    n = n->next_;
  }
}

template <class T>
inline list<T>::list(list<T>&& l) noexcept : list() {
  sentinel->next_ = l.sentinel->next_;
  sentinel->prev_ = l.sentinel->prev_;
  l.sentinel->next_->prev_ = sentinel;
  l.sentinel->prev_->next_ = sentinel;
  size_ = l.size_;

  l.sentinel->next_ = l.sentinel;
  l.sentinel->prev_ = l.sentinel;
  l.size_ = 0;
}

template <class T>
inline list<T>::~list() {
  clear();
  delete sentinel;
}

template <class T>
inline list<T>& list<T>::operator=(const list<T>& l) {
  clear();

  node* n = l.sentinel->next_;
  while (n != l.sentinel) {
    push_back(n->data_);
    n = n->next_;
  }
  return *this;
}

template <class T>
inline list<T>& list<T>::operator=(list<T>&& l) noexcept {
  clear();

  sentinel->next_ = l.sentinel->next_;
  sentinel->prev_ = l.sentinel->prev_;
  l.sentinel->next_->prev_ = sentinel;
  l.sentinel->prev_->next_ = sentinel;
  size_ = l.size_;
  l.sentinel->next_ = l.sentinel->prev_ = l.sentinel;
  l.size_ = 0;
  return *this;
}

template <class T>
inline typename list<T>::const_reference list<T>::front() const {
  return sentinel->next_->data_;
}

template <class T>
inline typename list<T>::const_reference list<T>::back() const {
  return sentinel->prev_->data_;
}

template <class T>
inline typename list<T>::reference list<T>::front() {
  return sentinel->next_->data_;
}

template <class T>
inline typename list<T>::reference list<T>::back() {
  return sentinel->prev_->data_;
}

template <class T>
inline typename list<T>::iterator list<T>::begin() {
  return ListIterator(sentinel->next_);
}

template <class T>
inline typename list<T>::iterator list<T>::end() {
  return ListIterator(sentinel);
}

template <class T>
inline typename list<T>::const_iterator list<T>::begin() const {
  return ListConstIterator(sentinel->next_);
}

template <class T>
inline typename list<T>::const_iterator list<T>::end() const {
  return ListConstIterator(sentinel);
}

template <class T>
inline bool list<T>::empty() const {
  return size_ == 0;
}

template <class T>
inline typename list<T>::size_type list<T>::size() const {
  return size_;
}

template <class T>
inline typename list<T>::size_type list<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(node);
}

template <class T>
inline void list<T>::clear() {
  while (sentinel != sentinel->next_) {
    node* buf = sentinel->next_;
    sentinel->next_ = buf->next_;
    delete buf;
    --size_;
  }
}

template <class T>
inline typename list<T>::iterator list<T>::insert(iterator pos,
                                                  const_reference value) {
  node* n = new node(value);
  n->next_ = pos.node_;
  n->prev_ = pos.node_->prev_;
  pos.node_->prev_->next_ = n;
  pos.node_->prev_ = n;
  size_++;
  return --pos;
}

template <class T>
inline void list<T>::erase(iterator pos) {
  node* n = pos.node_;
  if (n != sentinel) {
    n->next_->prev_ = n->prev_;
    n->prev_->next_ = n->next_;
    delete n;
    --size_;
  }
}

template <class T>
inline void list<T>::push_back(const_reference value) {
  iterator i = end();
  insert(i, value);
}

template <class T>
inline void list<T>::pop_back() {
  iterator i = --end();
  erase(i);
}

template <class T>
inline void list<T>::push_front(const_reference value) {
  iterator i = begin();
  insert(i, value);
}

template <class T>
inline void list<T>::pop_front() {
  iterator i = begin();
  erase(i);
}

template <class T>
inline void list<T>::swap(list& other) {
  if (&other != this) {
    auto buf = sentinel;
    sentinel = other.sentinel;
    other.sentinel = buf;
    size_ += other.size_;
    other.size_ = size_ - other.size_;
    size_ -= other.size_;
  }
}

template <class T>
inline void list<T>::merge(list& other) {
  if (&other != this) {
    iterator i_this = begin(), i_other = other.begin();
    while (i_this != end() && i_other != other.end()) {
      if (i_this == end() || (i_other != other.end() && *i_other < *i_this)) {
        insert(i_this, *i_other++);
      } else {
        ++i_this;
      }
    }
    while (i_other != other.end()) {
      push_back(*i_other++);
    }
    other.clear();
  }
}

template <class T>
inline void list<T>::splice(const_iterator pos, list& other) {
  other.sentinel->prev_->next_ = pos.node_;
  other.sentinel->next_->prev_ = pos.node_->prev_;
  pos.node_->prev_->next_ = other.sentinel->next_;
  pos.node_->prev_ = other.sentinel->prev_;

  size_ += other.size_;
  other.size_ = 0;
  other.sentinel->next_ = other.sentinel;
  other.sentinel->prev_ = other.sentinel;
}

template <class T>
inline void list<T>::reverse() {
  if (sentinel != sentinel->next_) {
    node* buf = sentinel;
    buf->prev_ = buf->next_;
    buf->next_ = buf;
    while (buf->prev_ != sentinel) {
      buf->prev_->prev_ = buf->prev_->next_;
      buf->prev_->next_ = buf;
      buf = buf->prev_;
    }
    sentinel->next_ = buf;
  }
}

template <class T>
inline void list<T>::unique() {
  if (size_ <= 1) return;
  for (iterator it = begin(), next_it = begin(); it != end(); ++it) {
    ++next_it;
    while (next_it != end() && *it == *next_it) {
      auto temp = next_it++;
      erase(temp);
    }
  }
}

template <class T>
inline void list<T>::sort() {
  if (size_ <= 1) return;
  bool swapped;
  do {
    swapped = false;
    auto it = begin();
    auto next_it = begin();
    ++next_it;

    while (next_it != end()) {
      if (*it > *next_it) {
        auto buf = *it;
        *it = *next_it;
        *next_it = buf;
        swapped = true;
      }
      ++it;
      ++next_it;
    }
  } while (swapped);
}

template <class T>
inline bool list<T>::operator==(const list& other) const {
  bool res = (size_ == other.size_);
  auto i_this = begin();
  auto i_other = other.begin();
  while (i_this != end() && i_other != other.end() && res) {
    if (*i_this != *i_other) {
      res = false;
    }
    i_this++;
    i_other++;
  }
  return res;
}

template <typename T>
template <typename... Args>
inline typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                       Args&&... args) {
  iterator left(pos.node_->prev_), right(pos.node_);

  if constexpr (sizeof...(args) > 0) {
    for (const auto& value : {args...}) {
      insert(right, value);
    }
  }

  return ++left;
}

template <typename T>
template <typename... Args>
inline void list<T>::insert_many_front(Args&&... args) {
  insert_many(begin(), args...);
}

template <typename T>
template <typename... Args>
inline void list<T>::insert_many_back(Args&&... args) {
  insert_many(end(), args...);
}

//--------------------------------------------------------------------------------

template <class T>
class list<T>::node {
 public:
  T data_;
  node* next_;
  node* prev_;

 public:
  node();
  node(value_type data);

  node(const node& n);

  ~node();
};

template <class T>
list<T>::node::node() : data_((value_type)0) {}

template <class T>
list<T>::node::node(value_type data) : data_(data) {}

template <class T>
list<T>::node::node(const node& n)
    : data_(n.data_), next_(n.next_), prev_(n.prev_) {}

template <class T>
list<T>::node::~node() {
  data_ = 0;
  next_ = nullptr;
  prev_ = nullptr;
}

template <class T>
class list<T>::ListIterator {
 protected:
  friend class list;
  node* node_;

 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T*;
  using reference = T&;

  ListIterator() : node_(nullptr) {}
  ListIterator(node* n) : node_(n) {}
  constexpr ListIterator(const iterator& other);
  ~ListIterator() { node_ = nullptr; }
  iterator& operator=(iterator other);
  node* getNode() const { return node_; }

  reference operator*() { return node_->data_; }
  pointer operator->() { return &(node_->data_); }

  iterator& operator++();
  iterator operator++(int);
  iterator& operator--();
  iterator operator--(int);

  bool operator==(const iterator& other) const { return node_ == other.node_; }
  bool operator!=(const iterator& other) const { return node_ != other.node_; }
  bool operator==(const const_iterator& other) const {
    return node_ == other.node_;
  }
  bool operator!=(const const_iterator& other) const {
    return node_ != other.node_;
  }

  friend list<T>::ListConstIterator::ListConstIterator(
      s21::list<T>::iterator i);
};

template <class T>
inline constexpr list<T>::ListIterator::ListIterator(const iterator& other) {
  node_ = other.node_;
}

template <class T>
inline typename list<T>::iterator& list<T>::ListIterator::operator=(
    iterator other) {
  node_ = other.node_;
  return *this;
}

template <class T>
inline typename list<T>::iterator& list<T>::ListIterator::operator++() {
  if (!node_) return *this;
  node_ = node_->next_;
  return *this;
}

template <class T>
inline typename list<T>::iterator list<T>::ListIterator::operator++(int) {
  iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <class T>
inline typename list<T>::iterator& list<T>::ListIterator::operator--() {
  if (!node_) return *this;
  node_ = node_->prev_;
  return *this;
}

template <class T>
inline typename list<T>::iterator list<T>::ListIterator::operator--(int) {
  iterator tmp = *this;
  --(*this);
  return tmp;
}

template <class T>
class list<T>::ListConstIterator {
 private:
  friend class list<T>;
  node* node_;

 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = const T;
  using difference_type = std::ptrdiff_t;
  using pointer = const T*;
  using reference = const T&;

  ListConstIterator() : node_(nullptr) {}
  ListConstIterator(node* n) : node_(n) {}
  ListConstIterator(iterator i) : node_(i.node_) {}
  constexpr ListConstIterator(const const_iterator& other)
      : node_(other.node_) {}
  ~ListConstIterator() { node_ = nullptr; }
  const node* getNode() const { return node_; }

  reference operator*() const { return node_->data_; }
  pointer operator->() const { return &(node_->data_); }

  const_iterator& operator++();
  const_iterator operator++(int);
  const_iterator& operator--();
  const_iterator operator--(int);

  bool operator==(const const_iterator& other) const {
    return node_ == other.node_;
  }
  bool operator!=(const const_iterator& other) const {
    return node_ != other.node_;
  }
  bool operator==(const iterator& other) const { return node_ == other.node_; }
  bool operator!=(const iterator& other) const { return node_ != other.node_; }
  const_iterator& operator=(const const_iterator& other);
  const_iterator& operator=(const_iterator&& other) noexcept;
};

template <class T>
inline typename list<T>::const_iterator&
list<T>::ListConstIterator::operator++() {
  if (!node_) return *this;
  node_ = node_->next_;
  return *this;
}

template <class T>
inline typename list<T>::const_iterator list<T>::ListConstIterator::operator++(
    int) {
  const_iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <class T>
inline typename list<T>::const_iterator&
list<T>::ListConstIterator::operator--() {
  if (!node_) return *this;
  node_ = node_->prev_;
  return *this;
}

template <class T>
inline typename list<T>::const_iterator list<T>::ListConstIterator::operator--(
    int) {
  const_iterator tmp = *this;
  --(*this);
  return tmp;
}

template <class T>
inline typename list<T>::const_iterator& list<T>::ListConstIterator::operator=(
    const const_iterator& other) {
  node_ = other.node_;
  return *this;
}

template <class T>
inline typename list<T>::const_iterator& list<T>::ListConstIterator::operator=(
    const_iterator&& other) noexcept {
  node_ = other.node_;
  other.node_ = nullptr;
  return *this;
}

}  // namespace s21

#endif
