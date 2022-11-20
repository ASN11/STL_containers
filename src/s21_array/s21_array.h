#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T, size_t S>
class Array {
 public:  // просто переназначаем другие названия для шаблонов (до конца не
          // разобрался)
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Array() : m_size_(S) {}  // конструктор по умолчанию
  Array(std::initializer_list<value_type> const
            &items);  // конструктор списка инициализаторов
  Array(const Array &v);  // конструктор копирования
  Array(Array &&v);       // конструктор перемещения
  Array &operator=(const Array &v);  // Перегрузка оператора присваивания

  reference at(size_type i);  // доступ к указанному элементу с проверкой границ
  reference operator[](size_type pos);  // доступ к указанному элементу
  const_reference front();  // доступ к первому элементу
  const_reference back();  // доступ к последнему элементу
  value_type *data() { return arr_; };  // прямой доступ к базовому массиву

  iterator begin() { return arr_; }  // возвращает итератор в начало
  iterator end() { return arr_ + m_size_; }  // возвращает итератор в конец

  bool empty();  // проверяет, пуст ли контейнер
  size_type size();  //  возвращает количество элементов
  size_type
  max_size();  // возвращает максимально возможное количество элементов

  void swap(Array &other);  // меняет содержимое местами
  void fill(const_reference value);  // присваивает заданное значение value всем
                                     // элементам в контейнере

  reference operator+(int n) { return *(arr_ += n); }
  reference operator-(int n) { return *(arr_ -= n); }
  reference operator++(int) { return *arr_++; }
  reference operator--(int) { return *arr_--; }
  reference operator++() { return *++arr_; }
  reference operator--() { return *--arr_; }
  bool operator!=(const iterator &it) { return arr_ != it.arr_; }
  bool operator==(const iterator &it) { return arr_ == it.arr_; }
  reference operator*() { return *arr_; }

 private:
  void copy_array_(const Array &v);  // копируем массив
  void move_array_(Array &v);  // перемещаем указатели на массив

  size_type m_size_ = S;  // размер вектора
  value_type arr_[S];     // указатель на массив
};
}  // namespace s21

#include "s21_array_impl.h"

#endif  // S21_ARRAY_H
