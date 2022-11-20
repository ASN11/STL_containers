#ifndef S21_MULTISET_IMPL
#define S21_MULTISET_IMPL

#include "s21_multiset.h"

namespace s21 {

// конструктор списка инициализаторов
template <typename Key, typename T>
multiset<Key, T>::multiset(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); it++) this->insert(*it);
}

// конструктор перемещения
template <class Key, typename T>
multiset<Key, T>::multiset(multiset &&s) {
  this->head_ = s.head_;
  s.head_ = nullptr;
}

// Перегрузка оператора присваивания
template <typename Key, typename T>
multiset<Key, T> &multiset<Key, T>::operator=(const multiset &s) {
  this->copy_set(s.head_);
  return *this;
}

// вставляет узел и возвращает итератор туда, где элемент находится в контейнере
template <typename Key, typename T>
typename multiset<Key, T>::iterator multiset<Key, T>::insert(
    const value_type &value) {
  if (this->head_ == nullptr) {
    this->head_ = this->create_tree_element(value);
    this->find_ = this->create_tree_element(Key());
  } else {
    tree_element_<Key, T> *el = this->create_tree_element(value);
    this->insert_into_tree(this->head_, el);
  }
  return iterator(this->head_);
}

// возвращает количество элементов, соответствующих определенному ключу
template <typename Key, typename T>
typename multiset<Key, T>::size_type multiset<Key, T>::count(const Key &key) {
  auto s = multicount(this->head_, key);
  return this->end_ && s ? s - 1 : s;
}

template <typename Key, typename T>
typename multiset<Key, T>::size_type multiset<Key, T>::multicount(
    tree_element_<Key, T> *current, const Key &key) {
  size_type res = 0;
  if (current == nullptr) return 0;
  if (current->values.first == key) res = 1;
  return res + multicount(current->left, key) + multicount(current->right, key);
}

// возвращает итератор к первому элементу не меньше заданного ключа
template <typename Key, typename T>
typename multiset<Key, T>::iterator multiset<Key, T>::lower_bound(
    const Key &key) {
  iterator x(this->begin());
  iterator end(this->end());
  --end;
  if (*end < key) {
    x = this->end();
  } else {
    while (*x < key) ++x;
  }
  return x;
}

// возвращает итератор к первому элементу больше заданного ключа
template <typename Key, typename T>
typename multiset<Key, T>::iterator multiset<Key, T>::upper_bound(
    const Key &key) {
  iterator x(this->begin());
  iterator end(this->end());
  --end;
  if (*end < key) {
    x = this->end();
  } else {
    while (*x <= key) ++x;
  }
  return x;
}

// возвращает диапазон элементов, соответствующих определенному ключу
template <typename Key, typename T>
std::pair<SetIterator<Key, T>, SetIterator<Key, T>>
multiset<Key, T>::equal_range(const Key &key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}
}  // namespace s21

#endif  // S21_MULTISET_IMPL
