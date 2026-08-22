#ifndef S21_SET_H
#define S21_SET_H

#include "rbt.h"
#include "s21_vector.h"

namespace s21 {
template <typename K>
class set {
 public:
  using key_type = K;
  using value_type = K;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename rbt<K>::Iterator;
  using const_iterator = typename rbt<K>::ConstIterator;
  using size_type = size_t;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set<K> &s);
  set(set<K> &&s);
  ~set();
  set<K> &operator=(set<K> &&s);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const K &key);
  bool contains(const K &key);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  rbt<K> tree_;
};

template <typename K>
inline set<K>::set() : tree_() {}

template <typename K>
inline set<K>::set(std::initializer_list<value_type> const &items) : tree_() {
  for (auto &item : items) {
    tree_.insert(item);
  }
}

template <typename K>
inline set<K>::set(const set<K> &s) : tree_(s.tree_) {}

template <typename K>
inline set<K>::set(set<K> &&s) : tree_(std::move(s.tree_)) {}

template <typename K>
inline set<K>::~set() {}

template <typename K>
inline set<K> &set<K>::operator=(set<K> &&s) {
  tree_ = std::move(s.tree_);
  return *this;
}

template <typename K>
inline typename set<K>::iterator set<K>::begin() {
  return tree_.begin();
}

template <typename K>
inline typename set<K>::iterator set<K>::end() {
  return tree_.end();
}

template <typename K>
inline bool set<K>::empty() {
  return tree_.empty();
}

template <typename K>
inline typename set<K>::size_type set<K>::size() {
  return tree_.size();
}

template <typename K>
inline typename set<K>::size_type set<K>::max_size() {
  return tree_.max_size();
}

template <typename K>
inline void set<K>::clear() {
  tree_.clear();
}

template <typename K>
inline std::pair<typename set<K>::iterator, bool> set<K>::insert(
    const value_type &value) {
  return tree_.insert(value);
}

template <typename K>
inline void set<K>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename K>
inline void set<K>::swap(set &other) {
  tree_.swap(other.tree_);
}
template <typename K>
inline void set<K>::merge(set &other) {
  auto it = other.begin();
  while (it != other.end()) {
    auto next = it;
    ++next;

    auto [inserted_it, inserted] = insert(*it);
    if (inserted) {
      other.erase(it);
    }

    it = next;
  }
}

template <typename K>
inline typename set<K>::iterator set<K>::find(const K &key) {
  return tree_.find(key);
}

template <typename K>
inline bool set<K>::contains(const K &key) {
  return tree_.contains(key);
}

template <typename K>
template <typename... Args>
inline s21::vector<std::pair<typename set<K>::iterator, bool>>
set<K>::insert_many(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> results;
  results.reserve(sizeof...(Args));
  (results.push_back(insert(std::forward<Args>(args))), ...);
  return results;
}

}  // namespace s21

#endif
