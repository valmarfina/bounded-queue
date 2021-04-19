#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP

#include <iostream>
#include "stack.hpp"
#include "WrongStackSize.hpp"
#include "StackOverflow.hpp"
#include "StackUnderflow.hpp"

template<class T>
class StackArray : public Stack<T> {
public:
  explicit StackArray(size_t size = 100);
  StackArray(const StackArray<T> &src);
  StackArray(StackArray<T> &&src) noexcept;
  StackArray<T> &operator=(const StackArray<T> &src);
  StackArray<T> &operator=(StackArray<T> &&src) noexcept;
  virtual ~StackArray();

  void push(const T &e);
  const T &pop();
  bool isEmpty();

private:
  T *array_;
  size_t top_{};
  size_t size_{};

  void swap(StackArray<T> &src);
};

template<class T>
StackArray<T>::StackArray(size_t size):
    size_(size),
    top_(0) {
  try {
    array_ = new T[size + 1];
  }
  catch (...) {
    throw WrongStackSize();
  }
}

template<class T>
StackArray<T>::StackArray(const StackArray<T> &src):
    size_(src.size_),
    top_(src.top_) {
  try {
    array_ = new T[src.size_ + 1];
  }
  catch (...) {
    throw WrongStackSize();
  }
  for (size_t i = 1; i <= src.top_; i++) {
    array_[i] = src.array_[i];
  }
}

template<class T>
StackArray<T> &StackArray<T>::operator=(const StackArray<T> &src) {
  if (this == &src) {
    return *this;
  }
  StackArray<T> temp(src);
  this->swap(temp);
  return *this;
}

template<class T>
StackArray<T>::StackArray(StackArray<T> &&src) noexcept {
  this->top_ = src.top_;
  this->size_ = src.size_;
  this->array_ = src.array_;
  src.array_ = nullptr;
  src.top_ = 0;
  src.size_ = 0;
}

template<class T>
StackArray<T> &StackArray<T>::operator=(StackArray<T> &&src) noexcept {
  delete[] this->array_;
  this->array_ = src.array_;
  this->top_ = src.top_;
  this->size_ = src.size_;
  src.array_ = nullptr;
  return *this;
}

template<class T>
void StackArray<T>::swap(StackArray<T> &src) {
  std::swap(array_, src.array_);
  std::swap(top_, src.top_);
  std::swap(size_, src.size_);
}

template<class T>
void StackArray<T>::push(const T &e) {
  if (top_ == size_) {
    throw StackOverflow();
  }
  array_[++top_] = e;
}

template<class T>
const T &StackArray<T>::pop() {
  if (top_ == 0) {
    throw StackUnderflow();
  }
  return array_[top_--];
}

template<class T>
bool StackArray<T>::isEmpty() {
  return (top_ == 0);
}

template<class T>
StackArray<T>::~StackArray() {
  delete[] array_;
}

#endif //STACK_ARRAY_HPP
