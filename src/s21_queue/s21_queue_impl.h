#ifndef S21_QUEUE_IMPL
#define S21_QUEUE_IMPL

#include "s21_queue.h"

namespace s21 {
template <typename T>
s21_queue<T>::s21_queue() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
s21_queue<T>::s21_queue(std::initializer_list<value_type> const &items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
}

template <typename T>
s21_queue<T>::s21_queue(const s21_queue &q)
    : head_(nullptr), tail_(nullptr), size_(0) {
  Node<int> *tmp = q.head_;
  while (tmp != nullptr) {
    push(tmp->data);
    tmp = tmp->next;
  }
}

template <typename T>
s21_queue<T>::s21_queue(s21_queue &&q)
    : head_(nullptr), tail_(nullptr), size_(0) {
  *this = std::move(q);
}

template <typename T>
s21_queue<T>::~s21_queue() {
  while (!empty()) pop();
}

template <typename T>
s21_queue<T> s21_queue<T>::operator=(s21_queue &&q) {
  if (this->head_ == q.head_ && this->tail_ == q.tail_) return *this;
  head_ = q.head_;
  q.head_ = nullptr;

  tail_ = q.tail_;
  q.tail_ = nullptr;

  size_ = q.size_;
  q.size_ = 0;
  return *this;
}

template <typename T>
typename s21_queue<T>::const_reference s21_queue<T>::front() const {
  if (tail_ == nullptr) throw std::out_of_range("queue: Nothing in the front");
  return this->head_->data;
}

template <typename T>
typename s21_queue<T>::const_reference s21_queue<T>::back() const {
  if (tail_ == nullptr) throw std::out_of_range("queue: Nothing in the back");
  return this->tail_->data;
}

template <typename T>
bool s21_queue<T>::empty() const {
  return this->size_ == 0;
}

template <typename T>
typename s21_queue<T>::size_type s21_queue<T>::size() const {
  return this->size_;
}

template <typename T>
void s21_queue<T>::push(const_reference data) {
  Node<T> *tmp = new Node<T>(data);
  size_++;
  if (tail_ == nullptr) {
    head_ = tail_ = tmp;
    return;
  }
  tail_->next = tmp;
  tail_ = tmp;
}

template <typename T>
void s21_queue<T>::pop() {
  if (empty()) throw std::out_of_range("queue: Nothing to pop");
  size_--;
  Node<T> *tmp = head_;
  head_ = head_->next;
  if (head_ == nullptr) tail_ = nullptr;
  delete tmp;
}

template <typename T>
void s21_queue<T>::swap(s21_queue &other) {
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->size_, other.size_);
}

template <typename T>
template <typename... Args>
void s21_queue<T>::emplace_back(Args &&...args) {
  for (auto &i : {args...}) push(i);
}

}  // namespace s21

#endif  // S21_QUEUE_IMPL
