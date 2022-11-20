#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Vector()
      : m_size_(0U),
        m_capacity_(0U),
        arr_(nullptr) {}  // конструктор по умолчанию
  explicit Vector(size_type n)
      : m_size_(n),
        m_capacity_(n),
        arr_(n ? new T[n] : nullptr) {}  // конструктор с указанием параметров
  Vector(std::initializer_list<value_type> const
             &items);  // конструктор списка инициализаторов
  Vector(const Vector &v);      // конструктор копирования
  Vector(Vector &&v);           // конструктор перемещения
  ~Vector() { delete[] arr_; }  // деструктор
  Vector &operator=(const Vector &v);  // Перегрузка оператора присваивания

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
  void reserve(
      size_type size);  // выделяет хранилище элементов размера и копирует
                        // текущие элементы массива в новый выделенный массив
  size_type capacity();  // возвращает количество выделенной памяти
  void shrink_to_fit();  // уменьшает использование памяти, освобождая
                         // неиспользуемую память

  void clear();  // очищает содержимое
  iterator insert(iterator pos,
                  const_reference value);  // вставляет элементы в конкретную
                                           // позицию и возвращает итератор,
                                           // указывающий на новый элемент
  void erase(iterator pos);  // стирает элемент в позиции
  void push_back(value_type v);  // добавляет элемент в конец
  void pop_back();           // удаляет последний элемент
  void swap(Vector &other);  // меняет содержимое местами

  template <typename... Args>
  iterator emplace(iterator pos, Args &&...args);

  template <typename... Args>
  void emplace_back(Args &&...args);

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
  void reserve_more_capacity_(
      size_type size);  // выделение памяти под увиличенный массив
  void copy_vector_(const Vector &v);  // копируем вектор
  void move_vector_(Vector &v);  // перемещаем указатели на вектор

  size_t m_size_;      // размер вектора
  size_t m_capacity_;  // количество выделенной памяти
  value_type *arr_;    // указатель на массив
};
}  // namespace s21

#include "s21_vector_impl.h"

#endif  // S21_VECTOR_H
