#ifndef S21_RBT
#define S21_RBT

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <utility>

namespace s21 {

enum Color { RED, BLACK };

template <typename T, typename Compare = std::less<T>>
class rbt {
 private:
  struct Node_;

 public:
  using value_type = T;
  using size_type = std::size_t;
  using comparator_type = Compare;

  class Iterator;
  using iterator = Iterator;
  class ConstIterator;
  using const_iterator = ConstIterator;
  using reference = T &;

  rbt();
  ~rbt();
  rbt(const rbt<T, Compare> &other);
  rbt(rbt<T, Compare> &&other);
  rbt &operator=(const rbt<T, Compare> &other);
  rbt &operator=(rbt<T, Compare> &&other);
  rbt(std::initializer_list<value_type> const &items);

  size_type size() const;
  bool empty() const;
  size_type max_size() const;

  std::pair<iterator, bool> insert(const value_type &value);
  iterator multi_insert(const value_type &value);
  size_type erase(const value_type &value);
  void erase(iterator pos);
  void swap(rbt &other);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  iterator find(const value_type &value);
  const_iterator find(const value_type &value) const;
  void transplant(Node_ *u, Node_ *v);

  void clear();

  void clearHelper(Node_ *node);
  bool contains(const value_type &value) const;

  size_type count(const value_type &value) const;
  iterator lower_bound(const value_type &value);
  iterator upper_bound(const value_type &value);
  const_iterator upper_bound(const value_type &value) const;
  const_iterator lower_bound(const value_type &value) const;

  std::pair<iterator, iterator> equal_range(const value_type &value);

 private:
  struct Node_ {
    T data;
    Color color;
    Node_ *left;
    Node_ *right;
    Node_ *parent;

    Node_(const T &value)
        : data(value),
          color(RED),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
  };

  Node_ *root_;
  size_type size_;
  Compare comp_;

  void clear(Node_ *node);
  Node_ *copyTree(Node_ *node, Node_ *parent);

  Node_ *findNode(const value_type &value) const;

  void fixInsert(Node_ *insert);
  void fixErase(Node_ *x);
  void rightRotate(Node_ *y);
  void leftRotate(Node_ *x);
};

template <typename T, typename Compare>
inline typename rbt<T, Compare>::iterator rbt<T, Compare>::begin() {
  Node_ *node = root_;
  if (!node) return Iterator(nullptr, root_);
  while (node->left) node = node->left;
  return Iterator(node, root_);
}

template <typename T, typename Compare>
inline typename rbt<T, Compare>::const_iterator rbt<T, Compare>::begin() const {
  Node_ *node = root_;
  if (!node) return ConstIterator(nullptr, root_);
  while (node->left) node = node->left;
  return ConstIterator(node, root_);
}

template <typename T, typename Compare>
inline typename rbt<T, Compare>::const_iterator rbt<T, Compare>::end() const {
  return ConstIterator(nullptr, root_);
}

template <typename T, typename Compare>
inline typename rbt<T, Compare>::iterator rbt<T, Compare>::end() {
  return Iterator(nullptr, root_);
}

template <typename T, typename Compare>
class rbt<T, Compare>::Iterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;

  Iterator() : node_(nullptr), root_(nullptr) {}
  Iterator(Node_ *node, Node_ *root) : node_(node), root_(root) {}
  Node_ *getNode() const { return node_; }

  reference operator*() { return node_->data; }
  pointer operator->() { return &(node_->data); }

  Iterator &operator++() {
    if (!node_) return *this;
    if (node_->right) {
      node_ = node_->right;
      while (node_->left) node_ = node_->left;
    } else {
      Node_ *p = node_->parent;
      while (p && node_ == p->right) {
        node_ = p;
        p = p->parent;
      }
      node_ = p;
    }
    return *this;
  }

  Iterator operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  Iterator &operator--() {
    if (!node_) {
      node_ = root_;
      if (!node_) return *this;
      while (node_->right) node_ = node_->right;
      return *this;
    }
    if (node_->left) {
      node_ = node_->left;
      while (node_->right) node_ = node_->right;
    } else {
      Node_ *p = node_->parent;
      while (p && node_ == p->left) {
        node_ = p;
        p = p->parent;
      }
      node_ = p;
    }
    return *this;
  }

  Iterator operator--(int) {
    Iterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const Iterator &other) const { return node_ == other.node_; }
  bool operator!=(const Iterator &other) const { return node_ != other.node_; }

 private:
  Node_ *node_;
  Node_ *root_;
};

template <typename T, typename Compare>
class rbt<T, Compare>::ConstIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = const T;
  using difference_type = std::ptrdiff_t;
  using pointer = const T *;
  using reference = const T &;

  ConstIterator() : node_(nullptr), root_(nullptr) {}
  ConstIterator(Node_ *node, Node_ *root) : node_(node), root_(root) {}

  reference operator*() const { return node_->data; }
  pointer operator->() const { return &(node_->data); }

  ConstIterator &operator++() {
    if (!node_) return *this;
    if (node_->right) {
      node_ = node_->right;
      while (node_->left) node_ = node_->left;
    } else {
      Node_ *p = node_->parent;
      while (p && node_ == p->right) {
        node_ = p;
        p = p->parent;
      }
      node_ = p;
    }
    return *this;
  }

  ConstIterator operator++(int) {
    ConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  ConstIterator &operator--() {
    if (!node_) {
      node_ = root_;
      if (!node_) return *this;
      while (node_->right) node_ = node_->right;
      return *this;
    }
    if (node_->left) {
      node_ = node_->left;
      while (node_->right) node_ = node_->right;
    } else {
      Node_ *p = node_->parent;
      while (p && node_ == p->left) {
        node_ = p;
        p = p->parent;
      }
      node_ = p;
    }
    return *this;
  }

  ConstIterator operator--(int) {
    ConstIterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const ConstIterator &other) const {
    return node_ == other.node_;
  }
  bool operator!=(const ConstIterator &other) const {
    return node_ != other.node_;
  }

 private:
  Node_ *node_;
  Node_ *root_;
};

template <typename T, typename Compare>
inline typename rbt<T, Compare>::size_type rbt<T, Compare>::size() const {
  return this->size_;
}

template <typename T, typename Compare>
inline bool rbt<T, Compare>::empty() const {
  return this->size_ == 0;
}

template <typename T, typename Compare>
inline rbt<T, Compare>::rbt() : root_(nullptr), size_(0), comp_(Compare()) {}

template <typename T, typename Compare>
inline rbt<T, Compare>::~rbt() {
  clear(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename T, typename Compare>
inline rbt<T, Compare>::rbt(const rbt<T, Compare> &other)
    : root_(nullptr), size_(other.size_), comp_(other.comp_) {
  root_ = copyTree(other.root_, nullptr);
}

template <typename T, typename Compare>
inline rbt<T, Compare>::rbt(rbt<T, Compare> &&other)
    : root_(other.root_), size_(other.size_), comp_(std::move(other.comp_)) {
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename T, typename Compare>
inline rbt<T, Compare> &rbt<T, Compare>::operator=(
    const rbt<T, Compare> &other) {
  if (this != &other) {
    clear(root_);
    this->size_ = other.size_;
    comp_ = other.comp_;
    root_ = copyTree(other.root_, nullptr);
  }
  return *this;
}

template <typename T, typename Compare>
inline rbt<T, Compare> &rbt<T, Compare>::operator=(rbt<T, Compare> &&other) {
  if (this != &other) {
    clear(root_);
    root_ = other.root_;
    this->size_ = other.size_;
    comp_ = std::move(other.comp_);
    other.root_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T, typename Compare>
inline rbt<T, Compare>::rbt(std::initializer_list<value_type> const &items)
    : root_(nullptr), size_(0), comp_(Compare()) {
  for (auto &item : items) insert(item);
}

template <typename T, typename Compare>
inline void rbt<T, Compare>::clear(Node_ *node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename T, typename Compare>
inline typename rbt<T, Compare>::Node_ *rbt<T, Compare>::copyTree(
    Node_ *node, Node_ *parent) {
  if (!node) return nullptr;
  Node_ *newNode = new Node_(node->data);
  newNode->color = node->color;
  newNode->parent = parent;
  newNode->left = copyTree(node->left, newNode);
  newNode->right = copyTree(node->right, newNode);
  return newNode;
}

template <typename T, typename Compare>
inline std::pair<typename rbt<T, Compare>::iterator, bool>
rbt<T, Compare>::insert(const value_type &value) {
  Node_ *node = new Node_(value);
  Node_ *current = root_;
  Node_ *parent = nullptr;

  if (this->size_ == 0) {
    root_ = node;
    root_->color = BLACK;
    ++this->size_;
    return {iterator(root_, root_), true};
  }

  while (current != nullptr) {
    parent = current;
    if (comp_(value, current->data)) {
      current = current->left;
    } else if (comp_(current->data, value)) {
      current = current->right;
    } else {
      delete node;
      return {iterator(current, root_), false};
    }
  }

  node->parent = parent;
  if (comp_(node->data, parent->data))
    parent->left = node;
  else
    parent->right = node;

  node->color = RED;
  ++this->size_;
  fixInsert(node);

  return {iterator(node, root_), true};
}

template <typename T, typename Compare>
inline typename rbt<T, Compare>::iterator rbt<T, Compare>::multi_insert(
    const value_type &value) {
  Node_ *node = new Node_(value);
  Node_ *current = root_;
  Node_ *parent = nullptr;

  if (!root_) {
    root_ = node;
    root_->color = BLACK;
    ++size_;
    return iterator(root_, root_);
  }

  while (current != nullptr) {
    parent = current;
    if (comp_(value, current->data)) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  node->parent = parent;
  if (comp_(node->data, parent->data))
    parent->left = node;
  else
    parent->right = node;

  node->color = RED;
  ++size_;
  fixInsert(node);

  return iterator(node, root_);
}

template <typename T, typename Compare>
inline void rbt<T, Compare>::rightRotate(Node_ *y) {
  if (!y) return;
  Node_ *x = y->left;
  if (!x) return;
  y->left = x->right;
  if (x->right) x->right->parent = y;
  x->parent = y->parent;
  if (!y->parent)
    root_ = x;
  else if (y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;
  x->right = y;
  y->parent = x;
}

template <typename T, typename Compare>
inline void rbt<T, Compare>::leftRotate(Node_ *x) {
  if (!x) return;
  Node_ *y = x->right;
  if (!y) return;
  x->right = y->left;
  if (y->left) y->left->parent = x;
  y->parent = x->parent;
  if (!x->parent)
    root_ = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

template <typename T, typename Compare>
inline void rbt<T, Compare>::fixInsert(Node_ *z) {
  if (!z) return;
  while (z != root_ && z->parent->color == RED) {
    Node_ *parent = z->parent;
    Node_ *grandparent = parent->parent;
    if (!grandparent) break;

    if (parent == grandparent->left) {
      Node_ *uncle = grandparent->right;
      if (uncle && uncle->color == RED) {
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        z = grandparent;
      } else {
        if (z == parent->right) {
          z = parent;
          leftRotate(z);
        }
        parent->color = BLACK;
        grandparent->color = RED;
        rightRotate(grandparent);
      }
    } else {
      Node_ *uncle = grandparent->left;
      if (uncle && uncle->color == RED) {
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        z = grandparent;
      } else {
        if (z == parent->left) {
          z = parent;
          rightRotate(z);
        }
        parent->color = BLACK;
        grandparent->color = RED;
        leftRotate(grandparent);
      }
    }
  }
  if (root_) root_->color = BLACK;
}

template <typename T, typename Compare>
inline typename rbt<T, Compare>::iterator rbt<T, Compare>::find(
    const value_type &value) {
  Node_ *node = root_;
  while (node != nullptr) {
    if (!comp_(node->data, value) && !comp_(value, node->data)) {
      return Iterator(node, root_);
    } else if (comp_(value, node->data)) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return this->end();
}

template <typename T, typename Compare>
inline typename rbt<T, Compare>::const_iterator rbt<T, Compare>::find(
    const value_type &value) const {
  Node_ *node = root_;
  while (node != nullptr) {
    if (!comp_(node->data, value) && !comp_(value, node->data)) {
      return ConstIterator(node, root_);
    } else if (comp_(value, node->data)) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return this->end();
}

template <typename T, typename Compare>
inline typename rbt<T, Compare>::size_type rbt<T, Compare>::erase(
    const value_type &value) {
  Node_ *z = findNode(value);
  if (!z) return 0;

  Node_ *y = z;
  Node_ *x = nullptr;
  Color y_original_color = y->color;

  if (!z->left) {
    x = z->right;
    transplant(z, z->right);
  } else if (!z->right) {
    x = z->left;
    transplant(z, z->left);
  } else {
    y = z->right;
    while (y->left) y = y->left;
    y_original_color = y->color;
    x = y->right;

    if (y->parent == z) {
      if (x) x->parent = y;
    } else {
      transplant(y, y->right);
      y->right = z->right;
      if (y->right) y->right->parent = y;
    }

    transplant(z, y);
    y->left = z->left;
    if (y->left) y->left->parent = y;
    y->color = z->color;
  }

  delete z;
  --size_;

  if (y_original_color == BLACK) fixErase(x);
  return 1;
}

template <typename T, typename Compare>
inline typename rbt<T, Compare>::Node_ *rbt<T, Compare>::findNode(
    const value_type &value) const {
  Node_ *current = root_;
  while (current) {
    if (comp_(value, current->data)) {
      current = current->left;
    } else if (comp_(current->data, value)) {
      current = current->right;
    } else {
      return current;
    }
  }
  return nullptr;
}

template <typename T, typename Compare>
inline void rbt<T, Compare>::transplant(Node_ *u, Node_ *v) {
  if (!u->parent) {
    root_ = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  if (v) v->parent = u->parent;
}

template <typename T, typename Compare>
inline void rbt<T, Compare>::fixErase(Node_ *x) {
  while (x != root_ && (!x || x->color == BLACK)) {
    if (!x) break;

    if (x == x->parent->left) {
      Node_ *w = x->parent->right;

      if (w && w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        leftRotate(x->parent);
        w = x->parent->right;
      }

      if ((!w || !w->left || w->left->color == BLACK) &&
          (!w || !w->right || w->right->color == BLACK)) {
        if (w) w->color = RED;
        x = x->parent;
      } else {
        if (!w || !w->right || w->right->color == BLACK) {
          if (w && w->left) w->left->color = BLACK;
          if (w) w->color = RED;
          if (w) rightRotate(w);
          w = x->parent->right;
        }

        if (w) w->color = x->parent->color;
        x->parent->color = BLACK;
        if (w && w->right) w->right->color = BLACK;
        leftRotate(x->parent);
        x = root_;
      }
    } else {
      Node_ *w = x->parent->left;

      if (w && w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rightRotate(x->parent);
        w = x->parent->left;
      }

      if ((!w || !w->left || w->left->color == BLACK) &&
          (!w || !w->right || w->right->color == BLACK)) {
        if (w) w->color = RED;
        x = x->parent;
      } else {
        if (!w || !w->left || w->left->color == BLACK) {
          if (w && w->right) w->right->color = BLACK;
          if (w) w->color = RED;
          if (w) leftRotate(w);
          w = x->parent->left;
        }

        if (w) w->color = x->parent->color;
        x->parent->color = BLACK;
        if (w && w->left) w->left->color = BLACK;
        rightRotate(x->parent);
        x = root_;
      }
    }
  }
  if (x) x->color = BLACK;
}

template <typename T, typename Compare>
inline void rbt<T, Compare>::clear() {
  clearHelper(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename T, typename Compare>
inline void rbt<T, Compare>::clearHelper(Node_ *node) {
  if (!node) return;
  clearHelper(node->left);
  clearHelper(node->right);
  delete node;
}

template <typename T, typename Compare>
inline bool rbt<T, Compare>::contains(const value_type &value) const {
  return find(value) != end();
}

template <typename T, typename Compare>
typename rbt<T, Compare>::size_type rbt<T, Compare>::count(
    const value_type &value) const {
  auto first = lower_bound(value);
  auto last = upper_bound(value);
  size_type cnt = 0;
  while (first != last) {
    ++cnt;
    ++first;
  }
  return cnt;
}

template <typename T, typename Compare>
inline typename rbt<T, Compare>::iterator rbt<T, Compare>::lower_bound(
    const value_type &value) {
  Node_ *node = root_;
  Node_ *res = nullptr;
  while (node) {
    if (!comp_(node->data, value)) {
      res = node;
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return res ? Iterator(res, root_) : end();
}

template <typename T, typename Compare>
typename rbt<T, Compare>::const_iterator rbt<T, Compare>::lower_bound(
    const value_type &value) const {
  Node_ *current = root_;
  Node_ *result = nullptr;
  while (current) {
    if (!comp_(current->data, value)) {
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return const_iterator(result, root_);
}

template <typename T, typename Compare>
typename rbt<T, Compare>::const_iterator rbt<T, Compare>::upper_bound(
    const value_type &value) const {
  Node_ *current = root_;
  Node_ *result = nullptr;
  while (current) {
    if (comp_(value, current->data)) {
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return const_iterator(result, root_);
}

template <typename T, typename Compare>
inline typename rbt<T, Compare>::iterator rbt<T, Compare>::upper_bound(
    const value_type &value) {
  Node_ *node = root_;
  Node_ *res = nullptr;
  while (node) {
    if (comp_(value, node->data)) {
      res = node;
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return res ? Iterator(res, root_) : end();
}

template <typename T, typename Compare>
inline std::pair<typename rbt<T, Compare>::iterator,
                 typename rbt<T, Compare>::iterator>
rbt<T, Compare>::equal_range(const value_type &value) {
  return {lower_bound(value), upper_bound(value)};
}

template <typename T, typename Compare>
inline void rbt<T, Compare>::erase(iterator pos) {
  if (pos == end()) return;
  erase(*pos);
}

template <typename T, typename Compare>
inline typename rbt<T, Compare>::size_type rbt<T, Compare>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(Node_) / 2;
}

template <typename T, typename Compare>
inline void rbt<T, Compare>::swap(rbt &other) {
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
  std::swap(comp_, other.comp_);
}

}  // namespace s21

#endif
