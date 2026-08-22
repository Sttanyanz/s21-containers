#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "rbt.h"

namespace s21 {
template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename rbt<value_type>::Iterator;
  using const_iterator = typename rbt<value_type>::ConstIterator;
  using size_type = size_t;

  multiset();
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms);
  ~multiset();
  multiset<Key> &operator=(multiset &&ms);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(const value_type &value);
  void erase(iterator pos);
  void swap(multiset &other);
  void merge(multiset &other);
  size_type count(const Key &key);
  iterator find(const Key &key);
  bool contains(const Key &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

 private:
  rbt<value_type> tree_;
};

template <typename Key>
inline multiset<Key>::multiset() : tree_() {}

template <typename Key>
inline multiset<Key>::multiset(std::initializer_list<value_type> const &items)
    : tree_() {
  for (auto &item : items) {
    tree_.multi_insert(item);
  }
}

template <typename Key>
inline multiset<Key>::multiset(const multiset &ms) : tree_(ms.tree_) {}

template <typename Key>
inline multiset<Key>::multiset(multiset &&ms) : tree_(std::move(ms.tree_)) {}

template <typename Key>
inline multiset<Key>::~multiset() {}

template <typename Key>
inline multiset<Key> &multiset<Key>::operator=(multiset &&ms) {
  tree_ = std::move(ms.tree_);
  return *this;
}

template <typename Key>
inline typename multiset<Key>::iterator multiset<Key>::begin() {
  return tree_.begin();
}

template <typename Key>
inline typename multiset<Key>::iterator multiset<Key>::end() {
  return tree_.end();
}

template <typename Key>
inline bool multiset<Key>::empty() {
  return tree_.empty();
}

template <typename Key>
inline typename multiset<Key>::size_type multiset<Key>::size() {
  return tree_.size();
}

template <typename Key>
inline typename multiset<Key>::size_type multiset<Key>::max_size() {
  return tree_.max_size();
}

template <typename Key>
inline void multiset<Key>::clear() {
  tree_.clear();
}

template <typename Key>
inline typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type &value) {
  return tree_.multi_insert(value);
}

template <typename Key>
inline void multiset<Key>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename Key>
inline void multiset<Key>::swap(multiset &other) {
  tree_.swap(other.tree_);
}

template <typename Key>
inline void multiset<Key>::merge(multiset &other) {
  iterator it = other.begin();
  while (it != other.end()) {
    auto current = it++;
    insert(*current);
    other.erase(current);
  }
}

template <typename Key>
inline typename multiset<Key>::size_type multiset<Key>::count(const Key &key) {
  return tree_.count(key);
}

template <typename Key>
inline typename multiset<Key>::iterator multiset<Key>::find(const Key &key) {
  return tree_.find(key);
}

template <typename Key>
inline bool multiset<Key>::contains(const Key &key) {
  return tree_.contains(key);
}

template <typename Key>
inline std::pair<typename multiset<Key>::iterator,
                 typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key &key) {
  return tree_.equal_range(key);
}

template <typename Key>
inline typename multiset<Key>::iterator multiset<Key>::lower_bound(
    const Key &key) {
  return tree_.lower_bound(key);
}

template <typename Key>
inline typename multiset<Key>::iterator multiset<Key>::upper_bound(
    const Key &key) {
  return tree_.upper_bound(key);
}

}  // namespace s21

#endif
