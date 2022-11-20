#ifndef S21_SET_IMPL
#define S21_SET_IMPL

#include "s21_set.h"

namespace s21 {

// создание нового элемента дерева
template <typename Key, typename T>
tree_element_<Key, T> *set<Key, T>::create_tree_element(Key new_value) {
  tree_element_<Key, T> *elem = new tree_element_<Key, T>;
  elem->values = std::make_pair(new_value, T());
  elem->left = nullptr;
  elem->right = nullptr;
  elem->back = nullptr;
  return elem;
}

// копируем сет
template <typename Key, typename T>
void set<Key, T>::copy_set(tree_element_<Key, T> *current) {
  insert(current->values.first);
  if (current->left != nullptr) {
    copy_set(current->left);
  }
  if (current->right != nullptr) {
    copy_set(current->right);
  }
}

// зачищаем память
template <typename Key, typename T>
void set<Key, T>::clear_set(tree_element_<Key, T> *current) {
  if (current) {
    if (current->left) {
      clear_set(current->left);
    }
    if (current->right) {
      clear_set(current->right);
    }
    this->obnul(current);
    delete current;
  }
}

// конструктор списка инициализаторов
template <typename Key, typename T>
set<Key, T>::set(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); it++) insert(*it);
}

// конструктор копирования
template <typename Key, typename T>
set<Key, T>::set(const set &s) {
  copy_set(s.head_);
}

// конструктор перемещения
template <class Key, typename T>
set<Key, T>::set(set &&s) {
  this->head_ = s.head_;
  s.head_ = nullptr;
}

// деструктор
template <typename Key, typename T>
set<Key, T>::~set() {
  clear_set(this->head_);
  delete this->find_;
}

// Перегрузка оператора присваивания
template <typename Key, typename T>
set<Key, T> &set<Key, T>::operator=(const set &s) {
  copy_set(s.head_);
  return *this;
}

// возвращает итератор в начало
template <typename Key, typename T>
typename set<Key, T>::iterator set<Key, T>::begin() {
  iterator cur(this->head_);
  while (cur.elem->left) {
    cur.elem = cur.elem->left;
  }
  end();
  return cur;
}

// возвращает итератор в конец
template <typename Key, typename T>
typename set<Key, T>::iterator set<Key, T>::end() {
  iterator cur(this->head_);
  while (cur.elem->right) {
    cur.elem = cur.elem->right;
  }
  if (!this->end_) {
    this->end_ = new tree_element_<Key, T>;
    this->end_->left = nullptr;
    this->end_->right = nullptr;
  } else {
    cur.elem = cur.elem->back;
  }
  cur.elem->right = this->end_;
  this->end_->back = cur.elem;
  return this->end_;
}

// очищает содержимое
template <typename Key, typename T>
void set<Key, T>::clear() {
  iterator x = begin();
  for (; x != end(); ++x) this->erase(x);
}

// вставляет узел и возвращает итератор туда, где элемент находится в контейнере
template <typename Key, typename T>
std::pair<typename set<Key, T>::iterator, bool> set<Key, T>::insert(
    const Key &value) {
  bool insertion = false;
  if (this->head_ == nullptr) {
    this->head_ = create_tree_element(value);
    this->find_ = create_tree_element(Key());
    insertion = true;
  } else {
    if (!contains(value)) {
      insertion = true;
      tree_element_<Key, T> *el = create_tree_element(value);
      this->insert_into_tree(this->head_, el);
    }
  }
  return std::make_pair(iterator(this->search_value(this->head_, value)),
                        insertion);
}

// меняет содержимое местами
template <typename Key, typename T>
void set<Key, T>::swap(set &other) {
  std::swap(this->head_, other.head_);
  std::swap(this->end_, other.end_);
  std::swap(this->find_, other.find_);
}

// соединяет узлы из другого контейнера
template <typename Key, typename T>
void set<Key, T>::merge(set &other) {
  this->insert_into_tree(this->head_, other.head_);
  other.head_ = nullptr;
}

// находит элемент с определенным ключом
template <typename Key, typename T>
typename set<Key, T>::iterator set<Key, T>::find(const Key &key) {
  iterator x(this->search_value(this->head_, key));
  return x;
}

// проверяет, содержит ли контейнер элемент с определенным ключом
template <typename Key, typename T>
bool set<Key, T>::contains(const Key &key) {
  return find(key).elem != this->find_;
}

template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename set<Key, T>::iterator, bool>>
set<Key, T>::emplace(Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;

  for (auto &i : {args...}) result.push_back(insert(i));
  return result;
}
}  // namespace s21

#endif  // S21_SET_IMPL
