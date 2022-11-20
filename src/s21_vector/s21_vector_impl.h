#ifndef S21_VECTOR_IMPL
#define S21_VECTOR_IMPL

#include "s21_vector.h"

namespace s21 {

// конструктор списка инициализаторов
template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const &items) {
  arr_ = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i] = *it;
    i++;
  }
  m_size_ = items.size();
  m_capacity_ = items.size();
}

// конструктор копирования
template <typename T>
Vector<T>::Vector(const Vector &v) {
  copy_vector_(v);
}

// конструктор перемещения
template <typename T>
Vector<T>::Vector(Vector &&v) {
  move_vector_(v);
}

// Перегрузка оператора присваивания для перемещаемого объекта
template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &v) {
  copy_vector_(v);
  return *this;
}

// выделение памяти под увиличенный массив
template <typename T>
void Vector<T>::reserve_more_capacity_(size_type size) {
  value_type *buff = new value_type[size];
  for (size_t i = 0; i < m_size_; ++i) buff[i] = std::move(arr_[i]);
  delete[] arr_;
  arr_ = buff;
  m_capacity_ = size;
}

// копируем вектор
template <typename T>
void Vector<T>::copy_vector_(const Vector &v) {
  m_size_ = v.m_size_;
  m_capacity_ = v.m_capacity_;
  arr_ = new T[m_size_];
  for (size_t i = 0; i < m_size_; i++) arr_[i] = v.arr_[i];
}

// перемещаем указатели на вектор
template <typename T>
void Vector<T>::move_vector_(Vector &v) {
  m_size_ = v.m_size_;
  m_capacity_ = v.m_capacity_;
  arr_ = v.arr_;
  v.arr_ = nullptr;
  v.m_size_ = 0;
  v.m_capacity_ = 0;
}

// доступ к указанному элементу с проверкой границ
template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type i) {
  if (i >= size()) throw std::out_of_range("Out of range");
  return arr_[i];
}

// доступ к указанному элементу
template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  return arr_[pos];
}

// доступ к первому элементу
template <typename T>
typename Vector<T>::const_reference Vector<T>::front() {
  return arr_[0];
}

// доступ к последнему элементу
template <typename T>
typename Vector<T>::const_reference Vector<T>::back() {
  return arr_[m_size_ - 1];
}

// проверяет, пуст ли контейнер
template <typename T>
bool Vector<T>::empty() {
  return m_size_ == 0;
}

// возвращает количество элементов
template <typename T>
typename Vector<T>::size_type Vector<T>::size() {
  return m_size_;
}

// возвращает максимально возможное количество элементов
template <typename T>
typename Vector<T>::size_type Vector<T>::max_size() {
  std::allocator<T> alloc;
  return alloc.max_size();
}

// выделяет хранилище элементов размера и копирует текущие элементы массива в
// новый выделенный массив
template <typename T>
void Vector<T>::reserve(size_type size) {
  if (size > max_size()) throw std::out_of_range("lenght error");
  if (size > m_capacity_) reserve_more_capacity_(size);
}

// возвращает количество выделенной памяти
template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() {
  return m_capacity_;
}

// уменьшает использование памяти, освобождая неиспользуемую память
template <typename T>
void Vector<T>::shrink_to_fit() {
  reserve_more_capacity_(m_size_);
}

// очищает содержимое
template <typename T>
void Vector<T>::clear() {
  m_size_ = 0;
}

// вставляет элементы в конкретную позицию и возвращает итератор, указывающий на
// новый элемент
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  Vector<T> local(*this);
  arr_[pos - begin()] = value;
  for (size_t i = (pos - begin() + 1); i < m_size_; i++) {
    arr_[i] = local.arr_[i - 1];
  }
  push_back(local.back());
  return pos;
}

// стирает элемент в позиции
template <typename T>
void Vector<T>::erase(iterator pos) {
  Vector<T> local(*this);
  for (size_t i = (pos - begin()); i < m_size_ - 1; i++) {
    arr_[i] = local.arr_[i + 1];
  }
  m_size_--;
}

// добавляет элемент в конец
template <typename T>
void Vector<T>::push_back(value_type v) {
  if (m_size_ == m_capacity_) {
    if (m_size_ == 0)
      reserve_more_capacity_(1);
    else
      reserve_more_capacity_(m_size_ * 2);
  }
  arr_[m_size_++] = v;
}

// удаляет последний элемент
template <typename T>
void Vector<T>::pop_back() {
  if (!empty()) m_size_--;
}

// меняет содержимое местами
template <typename T>
void Vector<T>::swap(Vector &other) {
  Vector<T> loc = std::move(other);
  other.move_vector_(*this);
  move_vector_(loc);
}

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::emplace(iterator pos, Args &&...args) {
  for (auto &i : {args...}) insert(pos, i);
  return pos;
}

template <typename T>
template <typename... Args>
void Vector<T>::emplace_back(Args &&...args) {
  for (auto &i : {args...}) push_back(i);
}
}  // namespace s21

#endif  // S21_VECTOR_IMPL
