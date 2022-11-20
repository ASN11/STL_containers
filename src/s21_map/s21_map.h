#ifndef S21_MAP
#define S21_MAP

#include <initializer_list>
#include <iostream>
#include <vector>

#include "../node.h"

namespace s21 {
template <typename Key, typename T>
class tree_element_ {
 public:
  std::pair<Key, T> values;
  tree_element_ *back;
  tree_element_ *left;
  tree_element_ *right;

  tree_element_() : tree_element_(Key(), T()) {}
  tree_element_(Key k, T val);
};

template <typename Key, typename T>
class MapIterator : public MainIterator<Key, T> {
 public:
  MapIterator() { this->elem = nullptr; }
  MapIterator(tree_element_<Key, T> *ref) { this->elem = ref; }
  std::pair<Key, T> &operator*() { return this->elem->values; }
};

template <typename Key, typename T>
class s21_map : public Tree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MapIterator<Key, T>;
  using size_type = size_t;
  using tree_type = tree_element_<key_type, mapped_type>;

  s21_map();
  s21_map(std::initializer_list<value_type> const &items);
  s21_map(s21_map &m);
  s21_map(s21_map &&m);
  ~s21_map();

  s21_map &operator=(s21_map &m);
  s21_map &operator=(s21_map &&m);

  T &at(const Key &key);
  T &operator[](const Key &key);

  iterator begin();
  iterator end();

  size_type max_size();

  void print_tree(tree_type *current);
  void print();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
  void erase(iterator pos);
  void swap(s21_map &other);
  void merge(s21_map &other);

  bool contains(const Key &key);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args);
};
}  // namespace s21

#include "s21_map_impl.h"

#endif  // S21_MAP
