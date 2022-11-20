#ifndef S21_LIST
#define S21_LIST

#include <initializer_list>
#include <iostream>

#include "../node.h"

namespace s21 {
template <typename T>
class ListConstIterator;

template <typename T>
class s21_list;
template <typename T>
class ListIterator {
 public:
  using self = ListIterator;
  using value_type = T;
  using reference = T &;
  using node_type = Node<T>;

  ListIterator();
  ListIterator(node_type *node);
  ~ListIterator();
  value_type operator*() const;
  self &operator++();
  self &operator--();
  self operator++(int);
  self operator--(int);
  bool operator==(const self &rhs) const;
  bool operator!=(const self &rhs) const;

 private:
  node_type *node;

  friend class ListConstIterator<T>;
  friend class s21_list<T>;
};

template <typename T>
class ListConstIterator : public ListIterator<T> {
 public:
  using self = ListConstIterator;
  using iterator = ListIterator<T>;
  using value_type = T;
  using reference = T &;
  using node_type = Node<T>;

  ListConstIterator();
  ListConstIterator(const iterator &it);
  ListConstIterator(const node_type *node);
  ~ListConstIterator();
  iterator node_const_cast() const;

 private:
  const node_type *node;

  friend class s21_list<T>;
};

template <typename T>
class s21_list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;
  using node_type = Node<T>;

  s21_list();
  s21_list(size_type n);
  s21_list(std::initializer_list<value_type> const &items);
  s21_list(const s21_list &l);
  s21_list(s21_list &&l);
  ~s21_list();
  s21_list operator=(s21_list &&l);
  s21_list operator=(const s21_list &l);

  const_reference front() const;
  const_reference back() const;

  iterator begin() const;
  iterator end() const;

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
  void swap(s21_list &other);
  void merge(s21_list &other);
  void splice(const_iterator pos, s21_list &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);

  template <typename... Args>
  void emplace_back(Args &&...args);

  template <typename... Args>
  void emplace_front(Args &&...args);

 private:
  void move_node_(node_type **dest, node_type **source);
  node_type *end_ptr_;
  node_type *head_;
  size_type size_;
};
}  // namespace s21

#include "s21_list_impl.h"

#endif  // S21_LIST
