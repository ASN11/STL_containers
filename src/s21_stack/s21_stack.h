#ifndef S21_STACK_H
#define S21_STACK_H

#include <initializer_list>
#include <iostream>

#include "../node.h"

namespace s21 {
template <typename T>
class s21_stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  s21_stack();
  s21_stack(std::initializer_list<value_type> const &items);
  s21_stack(const s21_stack &s);
  s21_stack(s21_stack &&s);
  ~s21_stack();
  s21_stack operator=(s21_stack &&s);

  const_reference top() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(s21_stack &other);
  void reverse();

  template <typename... Args>
  void emplace_front(Args &&...args);

 private:
  Node<T> *head_;
  size_type size_;
};
}  // namespace s21

#include "s21_stack_impl.h"

#endif  //  S21_STACK_H
