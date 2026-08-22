#ifndef S21_MAP_H
#define S21_MAP_H

#include "rbt.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename rbt<value_type>::Iterator;
  using const_iterator = typename rbt<value_type>::ConstIterator;
  using size_type = size_t;

  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map();
  map<Key, T> &operator=(map &&m);

  iterator find(const Key &key);

  mapped_type &at(const Key &key);
  mapped_type &operator[](const Key &key);

  iterator end();
  iterator begin();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);
  bool contains(const Key &key);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  rbt<value_type> tree_;
};

template <typename Key, typename T>
inline map<Key, T>::map() : tree_() {}
template <typename Key, typename T>
inline map<Key, T>::map(std::initializer_list<value_type> const &items)
    : tree_() {
  for (auto &item : items) {
    tree_.insert(item);
  }
}

template <typename Key, typename T>
inline map<Key, T>::map(const map &m) : tree_(m.tree_) {}

template <typename Key, typename T>
inline map<Key, T>::map(map &&m) : tree_(std::move(m.tree_)) {}

template <typename Key, typename T>
inline map<Key, T>::~map() {}

template <typename Key, typename T>
inline map<Key, T> &map<Key, T>::operator=(map &&m) {
  tree_ = std::move(m.tree_);
  return *this;
}

template <typename Key, typename T>
inline map<Key, T>::iterator map<Key, T>::find(const Key &key) {
  iterator it = tree_.begin();
  iterator it_end = tree_.end();

  while (it != it_end) {
    if (it->first == key) {
      return it;
    }
    ++it;
  }
  return it_end;
}

template <typename Key, typename T>
inline typename map<Key, T>::mapped_type &map<Key, T>::at(const Key &key) {
  iterator it = find(key);
  if (it == end()) {
    throw std::out_of_range("Key not found");
  }
  return it->second;
}

template <typename Key, typename T>
inline typename map<Key, T>::mapped_type &map<Key, T>::operator[](
    const Key &key) {
  iterator it = find(key);
  if (it != end()) {
    return it->second;
  } else {
    auto result = insert(std::make_pair(key, T()));
    return result.first->second;
  }
}

template <typename Key, typename T>
inline typename map<Key, T>::iterator map<Key, T>::end() {
  return tree_.end();
}

template <typename Key, typename T>
inline typename map<Key, T>::iterator map<Key, T>::begin() {
  return tree_.begin();
}

template <typename Key, typename T>
inline std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type &value) {
  iterator it = find(value.first);
  if (it != end()) {
    return {it, false};
  }
  return tree_.insert(value);
}

template <typename Key, typename T>
inline bool map<Key, T>::empty() {
  return tree_.empty();
}

template <typename Key, typename T>
inline typename map<Key, T>::size_type map<Key, T>::size() {
  return tree_.size();
}

template <typename Key, typename T>
inline typename map<Key, T>::size_type map<Key, T>::max_size() {
  return tree_.max_size();
}

template <typename Key, typename T>
inline void map<Key, T>::clear() {
  tree_.clear();
}

template <typename Key, typename T>
inline std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key &key, const T &obj) {
  iterator it = find(key);
  if (it != end()) {
    return {it, false};
  }
  return tree_.insert(std::make_pair(key, obj));
}

template <typename Key, typename T>
inline std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert_or_assign(const Key &key, const T &obj) {
  iterator it = find(key);
  if (it != end()) {
    it->second = obj;
    return std::make_pair(it, false);
  } else {
    auto result = insert(key, obj);
    return std::make_pair(result.first, true);
  }
}

template <typename Key, typename T>
inline void map<Key, T>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename Key, typename T>
inline void map<Key, T>::swap(map &other) {
  tree_.swap(other.tree_);
}

template <typename Key, typename T>
inline void map<Key, T>::merge(map &other) {
  auto it = other.begin();
  while (it != other.end()) {
    auto current = it++;
    if (!contains(current->first)) {
      insert(*current);
      other.erase(current);
    }
  }
}

template <typename Key, typename T>
inline bool map<Key, T>::contains(const Key &key) {
  return find(key) != end();
}

template <typename Key, typename T>
template <typename... Args>
inline s21::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> results;
  (results.push_back(this->insert(std::forward<Args>(args))), ...);
  return results;
}

}  // namespace s21

#endif
