#ifndef S21_STACK_IMPL
#define S21_STACK_IMPL

#include "s21_stack.h"

namespace s21 {
template <typename T>
s21_stack<T>::s21_stack() : head_(nullptr), size_(0) {}

template <typename T>
s21_stack<T>::s21_stack(std::initializer_list<value_type> const &items)
    : head_(nullptr), size_(0) {
  for (auto it = items.begin(); it != items.end(); it++) push(*it);
}

template <typename T>
s21_stack<T>::s21_stack(const s21_stack &s) : head_(nullptr), size_(0) {
  Node<T> *ptr = s.head_;
  while (ptr != nullptr) {
    push(ptr->data);
    ptr = ptr->next;
  }
  reverse();
}

template <typename T>
s21_stack<T>::s21_stack(s21_stack &&s) : head_(nullptr), size_(0) {
  *this = std::move(s);
}

template <typename T>
s21_stack<T>::~s21_stack() {
  while (!empty()) pop();
}

template <typename T>
s21_stack<T> s21_stack<T>::operator=(s21_stack &&s) {
  this->head_ = s.head_;
  this->size_ = s.size_;
  s.head_ = nullptr;
  s.size_ = 0;
  return *this;
}

template <typename T>
void s21_stack<T>::push(const_reference value) {
  Node<T> *node = new Node<T>(value);
  node->data = value;
  node->next = this->head_;
  this->head_ = node;
  size_++;
}

template <typename T>
void s21_stack<T>::pop() {
  if (empty()) throw std::out_of_range("stack: Nothing to pop");
  Node<T> *tmp = head_;
  head_ = head_->next;
  delete tmp;
  size_--;
}

template <typename T>
void s21_stack<T>::swap(s21_stack &other) {
  std::swap(this->head_, other.head_);
  std::swap(this->size_, other.size_);
}

template <typename T>
void s21_stack<T>::reverse() {
  Node<T> *prev, *cur, *succ;
  cur = prev = head_;
  cur = cur->next;
  prev->next = NULL;
  while (cur != NULL) {
    succ = cur->next;
    cur->next = prev;
    prev = cur;
    cur = succ;
  }
  head_ = prev;
}

template <typename T>
template <typename... Args>
void s21_stack<T>::emplace_front(Args &&...args) {
  for (auto &i : {args...}) push(i);
}

template <typename T>
typename s21_stack<T>::const_reference s21_stack<T>::top() const {
  if (empty()) throw std::out_of_range("stack: Nothing to show");
  return head_->data;
}

template <typename T>
typename s21_stack<T>::size_type s21_stack<T>::size() const {
  return this->size_;
}

template <typename T>
bool s21_stack<T>::empty() const {
  return this->size_ == 0;
}
}  // namespace s21

#endif  // S21_STACK_IMPL
