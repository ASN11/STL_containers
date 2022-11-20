#ifndef S21_SET_H
#define S21_SET_H

#include <initializer_list>
#include <iostream>
#include <vector>

#include "../node.h"

#define MAXSIZE 230584300921369395

namespace s21 {
template <class Key, typename T>
class set;
template <class Key, typename T>
class SetIterator;

template <typename Key, typename T>
class tree_element_ {
 public:
  std::pair<Key, T> values;
  tree_element_<Key, T> *left, *right, *back;

  friend set<Key, T>;
  friend SetIterator<Key, T>;
};

template <class Key, typename T>
class SetIterator : public MainIterator<Key, T> {
 public:
  SetIterator(tree_element_<Key, T> *current) { this->elem = current; }
  Key &operator*() { return this->elem->values.first; }

  friend set<Key, T>;
};

template <class Key, typename T = int>
class set : public Tree<Key, T> {
 public:
  using value_type = Key;
  using reference = Key &;
  using const_reference = const Key &;
  using iterator = SetIterator<Key, T>;
  using size_type = size_t;

  set() {}  // конструктор по умолчанию
  set(std::initializer_list<value_type> const
          &items);  // конструктор списка инициализаторов
  set(const set &s);  // конструктор копирования
  set(set &&s);       // конструктор перемещения
  ~set();             // деструктор
  set &operator=(const set &s);  // Перегрузка оператора присваивания

  iterator begin();  // возвращает итератор в начало
  iterator end();    // возвращает итератор в конец

  size_type max_size() {
    return MAXSIZE;
  }  // возвращает максимально возможное количество элементов

  void clear();  // очищает содержимое
  std::pair<iterator, bool> insert(
      const value_type &value);  // вставляет узел и возвращает итератор туда,
                                 // где элемент находится в контейнере
  void swap(set &other);  // меняет содержимое местами
  void merge(set &other);  // соединяет узлы из другого контейнера

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args);

  iterator find(const Key &key);  // находит элемент с определенным ключом
  bool contains(const Key &key);  // проверяет, содержит ли контейнер элемент с
                                  // определенным ключом

 protected:
  tree_element_<Key, T> *create_tree_element(
      Key new_value);  // создание нового элемента дерева
  void copy_set(tree_element_<Key, T> *current);  // копируем сет
  void clear_set(tree_element_<Key, T> *current);  // зачищаем память
};
}  // namespace s21

#include "s21_set_impl.h"

#endif  // S21_SET_H
