#ifndef S21_LIST_ITERATOR
#define S21_LIST_ITERATOR

#include "s21_list.h"

template <typename T>
s21::ListIterator<T>::ListIterator() : node(nullptr) {}

template <typename T>
s21::ListIterator<T>::ListIterator(Node<T> *n_node) : node(n_node) {}

template <typename T>
s21::ListIterator<T>::~ListIterator() {
  this->node = nullptr;
}

template <typename T>
typename s21::ListIterator<T>::value_type s21::ListIterator<T>::operator*()
    const {
  return node->data;
}

template <typename T>
typename s21::ListIterator<T>::self &s21::ListIterator<T>::operator++() {
  node = node->next;
  return *this;
}

template <typename T>
typename s21::ListIterator<T>::self &s21::ListIterator<T>::operator--() {
  node = node->prev;
  return *this;
}

template <typename T>
typename s21::ListIterator<T>::self s21::ListIterator<T>::operator++(int) {
  self tmp = *this;
  node = node->next;
  return tmp;
}

template <typename T>
typename s21::ListIterator<T>::self s21::ListIterator<T>::operator--(int) {
  self tmp = *this;
  node = node->prev;
  return tmp;
}

template <typename T>
bool s21::ListIterator<T>::operator==(const self &rhs) const {
  return this->node == rhs.node;
}

template <typename T>
bool s21::ListIterator<T>::operator!=(const self &rhs) const {
  return !(this->node == rhs.node);
}

template <typename T>
s21::ListConstIterator<T>::ListConstIterator()
    : iterator(nullptr), node(nullptr) {}

template <typename T>
s21::ListConstIterator<T>::ListConstIterator(const iterator &it)
    : iterator(it.node), node(it.node) {}

template <typename T>
s21::ListConstIterator<T>::ListConstIterator(const Node<T> *n_node)
    : iterator(n_node), node(n_node) {}

template <typename T>
s21::ListConstIterator<T>::~ListConstIterator() {
  this->node = nullptr;
}

template <typename T>
typename s21::ListConstIterator<T>::iterator
s21::ListConstIterator<T>::node_const_cast() const {
  return iterator(const_cast<Node<T> *>(node));
}

#endif  // S21_LIST_ITERATOR
