#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include <initializer_list>
#include <iostream>

#include "../s21_set/s21_set.h"

namespace s21 {

template <class Key, typename T = int>
class multiset : public set<Key, T> {
 public:
  using value_type = Key;
  using reference = Key &;
  using const_reference = const Key &;
  using iterator = SetIterator<Key, T>;
  using size_type = size_t;

  multiset() {}  // конструктор по умолчанию
  multiset(std::initializer_list<value_type> const
               &items);  // конструктор списка инициализаторов
  multiset(const multiset &s);  // конструктор копирования
  multiset(multiset &&s);       // конструктор перемещения
  multiset &operator=(const multiset &s);  // Перегрузка оператора присваивания

  iterator insert(
      const value_type &value);  // вставляет узел и возвращает итератор туда,
                                 // где элемент находится в контейнере

  size_type count(const Key &key);  // возвращает количество элементов,
                                    // соответствующих определенному ключу
  std::pair<iterator, iterator> equal_range(
      const Key &key);  // возвращает диапазон элементов, соответствующих
                        // определенному ключу
  iterator lower_bound(const Key &key);  // возвращает итератор к первому
                                         // элементу не меньше заданного ключа
  iterator upper_bound(const Key &key);  // возвращает итератор к первому
                                         // элементу больше заданного ключа

 private:
  size_type multicount(tree_element_<Key, T> *current, const Key &key);
};
}  // namespace s21

#include "s21_multiset_impl.h"

#endif  // S21_MULTISET_H
