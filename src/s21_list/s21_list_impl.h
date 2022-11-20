#ifndef S21_LIST_IMPL
#define S21_LIST_IMPL

#include "s21_list.h"
#include "s21_list_iterator.h"

namespace s21 {
template <typename T>
s21_list<T>::s21_list()
    : end_ptr_(new node_type(0)), head_(end_ptr_), size_(0) {}

template <typename T>
s21_list<T>::s21_list(size_type n)
    : end_ptr_(new node_type(0)), head_(end_ptr_), size_(0) {
  if (n == 0) return;
  do push_front(0);
  while (--n);
}

template <typename T>
s21_list<T>::s21_list(std::initializer_list<value_type> const &items)
    : end_ptr_(new node_type(0)), head_(end_ptr_), size_(0) {
  for (auto it = items.begin(); it != items.end(); it++) push_back(*it);
}

template <typename T>
s21_list<T>::s21_list(const s21_list &l)
    : end_ptr_(new node_type(0)), head_(end_ptr_), size_(0) {
  for (auto it = l.begin(); it != l.end(); it++) push_back(*it);
}

template <typename T>
s21_list<T>::s21_list(s21_list &&l)
    : end_ptr_(new node_type(0)), head_(end_ptr_), size_(0) {
  *this = std::move(l);
}

template <typename T>
s21_list<T>::~s21_list() {
  while (!empty()) pop_front();
  if (end_ptr_ != nullptr) delete end_ptr_;
}

template <typename T>
s21_list<T> s21_list<T>::operator=(s21_list &&l) {
  this->head_ = l.head_;
  delete this->end_ptr_;
  this->end_ptr_ = l.end_ptr_;
  this->size_ = l.size_;

  l.head_ = nullptr;
  l.end_ptr_ = nullptr;
  l.size_ = 0;
  return *this;
}

template <typename T>
s21_list<T> s21_list<T>::operator=(const s21_list &l) {
  for (auto it = l.begin(); it != l.end(); it++) {
    push_back(*it);
  }
  return *this;
}

/// @return Access the first element (head)
template <typename T>
typename s21_list<T>::const_reference s21_list<T>::front() const {
  return head_->data;
}

/// @return Access the last element (end_ptr)
template <typename T>
typename s21_list<T>::const_reference s21_list<T>::back() const {
  return end_ptr_->prev->data;
}

/// @return Returns an iterator to the beginning
template <typename T>
typename s21_list<T>::iterator s21_list<T>::begin() const {
  return iterator(this->head_);
}

/// @return Returns an iterator to the end
template <typename T>
typename s21_list<T>::iterator s21_list<T>::end() const {
  return iterator(this->end_ptr_);
}

/// @brief Возвращает количество элементов
/// @return Текущий размер контейнера
template <typename T>
typename s21_list<T>::size_type s21_list<T>::size() const {
  return this->size_;
}

template <typename T>
typename s21_list<T>::size_type s21_list<T>::max_size() const {
  return 384307168202282325;
}

/// @brief Проверяет, пуст ли контейнер
/// @return true если пуст, иначе false
template <typename T>
bool s21_list<T>::empty() const {
  return this->size_ == 0;
}

/// @brief Очищает содержимое
template <typename T>
void s21_list<T>::clear() {
  for (auto it = begin(); it != end(); it++) {
    erase(it);
  }
}

/// @brief Вставляет элемент в конкретный pos
/// @param pos iterator position
/// @param value Значение нового элемента
/// @return iterator, указывающий на новый элемент
template <typename T>
typename s21_list<T>::iterator s21_list<T>::insert(iterator pos,
                                                   const_reference value) {
  if (pos == this->begin()) {
    push_front(value);
    return --pos;
  }
  node_type *n = new node_type(value);
  n->next = pos.node;
  n->prev = pos.node->prev;

  pos.node->prev->next = n;
  pos.node->prev = n;

  size_++;
  return --pos;
}

/// @brief Стирает элемент в позиции pos
/// @param pos iterator position
template <typename T>
void s21_list<T>::erase(iterator pos) {
  if (pos == begin()) {
    pop_front();
    return;
  }
  if (pos == end()) {
    throw std::out_of_range("list: erase: Invalid position");
  }
  pos.node->prev->next = pos.node->next;
  pos.node->next->prev = pos.node->prev;
  delete pos.node;
  size_--;
}

/// @brief Добавляет элемент в конец (end_ptr)
/// @param value Значение нового элемента
template <typename T>
void s21_list<T>::push_back(const_reference value) {
  if (head_ == end_ptr_) {
    push_front(value);
    return;
  }
  node_type *n = new node_type(value);

  n->next = end_ptr_;
  n->prev = end_ptr_->prev;

  end_ptr_->prev->next = n;
  end_ptr_->prev = n;

  size_++;
}

/// @brief Удаляет последний элемент (end_ptr)
template <typename T>
void s21_list<T>::pop_back() {
  if (empty()) throw std::out_of_range("list: pop_back: Nothing to pop");
  node_type *n = end_ptr_;
  end_ptr_ = end_ptr_->prev;
  end_ptr_->next = nullptr;
  delete n;
  size_--;
}

/// @brief Добавляет элемент в head
/// @param value Значение нового элемента
template <typename T>
void s21_list<T>::push_front(const_reference value) {
  node_type *n = new node_type(value);
  n->next = head_;
  head_->prev = n;
  head_ = n;
  size_++;
}

/// @brief Удаляет первый элемент (head)
template <typename T>
void s21_list<T>::pop_front() {
  if (empty()) throw std::out_of_range("list: pop_front: Nothing to pop");
  node_type *n = head_;
  head_ = n->next;
  delete n;
  size_--;
}

/// @brief Меняет местами списки
/// @param other Другой список
template <typename T>
void s21_list<T>::swap(s21_list &other) {
  std::swap(this->end_ptr_, other.end_ptr_);
  std::swap(this->head_, other.head_);
  std::swap(this->size_, other.size_);
}

/// @brief Объединяет два отсортированных списка
/// @param other Другой список
template <typename T>
void s21_list<T>::merge(s21_list &other) {
  node_type *result = nullptr;

  node_type **lastPtr = &result;
  node_type *endptr = nullptr;
  while (true) {
    if (this->head_ == this->end_ptr_) {
      *lastPtr = other.head_;
      endptr = other.end_ptr_;
      break;
    }
    if (other.head_ == other.end_ptr_) {
      *lastPtr = this->head_;
      endptr = this->end_ptr_;
      break;
    }
    if (this->head_->data <= other.head_->data) {
      move_node_(lastPtr, &this->head_);
    } else {
      move_node_(lastPtr, &other.head_);
    }
    lastPtr = &((*lastPtr)->next);
  }

  this->head_ = result;
  if (this->end_ptr_ != endptr) delete this->end_ptr_;
  this->end_ptr_ = endptr;
  this->size_ += other.size_;

  other.head_ = nullptr;
  other.size_ = 0;
  if (this->end_ptr_ == other.end_ptr_) other.end_ptr_ = nullptr;
}

/// @brief Двигает указатель head
/// @param dest Записать значение head
/// @param source Чей head двигать
template <typename T>
void s21_list<T>::move_node_(node_type **dest, node_type **source) {
  node_type *new_node = *source;
  *source = new_node->next;

  new_node->next = *dest;
  *dest = new_node;
}

/// @brief Переносит элементы из другого списка, начиная с pos
/// @param pos Iterator position in place of which will be inserted other list
/// @param other Insert list
template <typename T>
void s21_list<T>::splice(const_iterator pos, s21_list &other) {
  iterator n_pos = pos.node_const_cast();

  if (pos != begin()) n_pos.node->prev->next = other.head_;
  if (pos != begin()) other.head_->prev = n_pos.node->prev;
  n_pos.node->prev = other.end_ptr_->prev;
  other.end_ptr_->prev->next = n_pos.node;

  if (pos == begin()) this->head_ = other.head_;
  this->size_ += other.size_;
  other.size_ = 0;

  other.head_ = nullptr;
  delete other.end_ptr_;
  other.end_ptr_ = nullptr;
}

/// @brief Изменяет порядок элементов
template <typename T>
void s21_list<T>::reverse() {
  s21_list reversed;
  auto it = this->end();
  it--;
  for (; it != this->begin(); it--) reversed.push_back(*it);
  reversed.push_back(*it);
  this->clear();
  *this = std::move(reversed);
}

/// @brief Удаляет последовательные дублирующие элементы
template <typename T>
void s21_list<T>::unique() {
  for (auto it = begin(); it != end(); it++)
    if (it.node->data == it.node->next->data) erase(it);
}

/// @brief Sort a list
template <typename T>
void s21_list<T>::sort() {
  s21_list<T> sorted;

  while (this->size() > 0) {
    auto largest_iter = this->begin();
    auto iter = largest_iter;

    for (; iter != this->end(); iter++)
      if (*iter > *largest_iter) largest_iter = iter;

    sorted.push_front(*largest_iter);
    this->erase(largest_iter);
  }
  *this = sorted;
}

template <typename T>
template <typename... Args>
typename s21_list<T>::iterator s21_list<T>::emplace(const_iterator pos,
                                                    Args &&...args) {
  for (auto &i : {args...}) insert(pos, i);
  return pos.node_const_cast();
}

template <typename T>
template <typename... Args>
void s21_list<T>::emplace_back(Args &&...args) {
  for (auto &i : {args...}) push_back(i);
}

template <typename T>
template <typename... Args>
void s21_list<T>::emplace_front(Args &&...args) {
  for (auto &i : {args...}) push_front(i);
}
}  // namespace s21

#endif  // S21_LIST_IMPL
