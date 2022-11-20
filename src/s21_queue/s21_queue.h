#ifndef S21_QUEUE
#define S21_QUEUE

#include "../node.h"

namespace s21 {
template <typename T>
class s21_queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  s21_queue();
  s21_queue(std::initializer_list<value_type> const &items);
  s21_queue(const s21_queue &q);
  s21_queue(s21_queue &&q);
  ~s21_queue();
  s21_queue operator=(s21_queue &&q);

  const_reference front() const;
  const_reference back() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(s21_queue &other);

  template <typename... Args>
  void emplace_back(Args &&...args);

 private:
  Node<T> *head_, *tail_;
  size_type size_;
};
}  // namespace s21

#include "s21_queue_impl.h"

#endif  //  S21_QUEUE
