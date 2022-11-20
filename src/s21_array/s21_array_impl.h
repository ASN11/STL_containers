#ifndef S21_ARRAY_IMPL
#define S21_ARRAY_IMPL

#include "s21_array.h"

namespace s21 {

// копируем массив
template <typename T, size_t S>
void Array<T, S>::copy_array_(const Array &v) {
  for (size_t i = 0; i < m_size_; i++) arr_[i] = v.arr_[i];
}

// перемещаем указатели на массив
template <typename T, size_t S>
void Array<T, S>::move_array_(Array &v) {
  copy_array_(v);
}

// конструктор списка инициализаторов
template <typename T, size_t S>
Array<T, S>::Array(std::initializer_list<value_type> const &items) {
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i] = *it;
    i++;
  }
  if (i > (int)S) throw std::out_of_range("error: too many initializers");
}

// конструктор копирования
template <typename T, size_t S>
Array<T, S>::Array(const Array &v) {
  copy_array_(v);
}

// конструктор перемещения
template <typename T, size_t S>
Array<T, S>::Array(Array &&v) {
  move_array_(v);
}

// Перегрузка оператора присваивания для перемещаемого объекта
template <typename T, size_t S>
Array<T, S> &Array<T, S>::operator=(const Array &v) {
  copy_array_(v);
  return *this;
}

// доступ к указанному элементу с проверкой границ
template <typename T, size_t S>
typename Array<T, S>::reference Array<T, S>::at(size_type i) {
  if (i >= size()) throw std::out_of_range("Out of range");
  return arr_[i];
}

// доступ к указанному элементу
template <typename T, size_t S>
typename Array<T, S>::reference Array<T, S>::operator[](size_type pos) {
  return arr_[pos];
}

// доступ к первому элементу
template <typename T, size_t S>
typename Array<T, S>::const_reference Array<T, S>::front() {
  return arr_[0];
}

// доступ к последнему элементу
template <typename T, size_t S>
typename Array<T, S>::const_reference Array<T, S>::back() {
  return arr_[m_size_ - 1];
}

// проверяет, пуст ли контейнер
template <typename T, size_t S>
bool Array<T, S>::empty() {
  return m_size_ == 0;
}

// возвращает количество элементов
template <typename T, size_t S>
typename Array<T, S>::size_type Array<T, S>::size() {
  return m_size_;
}

// возвращает максимально возможное количество элементов
template <typename T, size_t S>
typename Array<T, S>::size_type Array<T, S>::max_size() {
  return S;
}

// меняет содержимое местами
template <typename T, size_t S>
void Array<T, S>::swap(Array &other) {
  Array<T, S> loc = std::move(other);
  other.move_array_(*this);
  move_array_(loc);
}

// присваивает заданное значение value всем элементам в контейнере
template <typename T, size_t S>
void Array<T, S>::fill(const_reference value) {
  for (size_t i = 0; i < m_size_; i++) arr_[i] = value;
}
}  // namespace s21

#endif  // S21_ARRAY_IMPL
