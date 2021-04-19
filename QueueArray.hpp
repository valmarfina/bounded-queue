#ifndef QUEUE_ARRAY_HPP
#define QUEUE_ARRAY_HPP

#include <exception>
#include "Queue.hpp"
#include "QueueOverflow.hpp"
#include "QueueUnderflow.hpp"
#include "WrongQueueSize.hpp"

template<typename T>
class QueueArray final : public Queue<T> {
public:
  explicit QueueArray(size_t size);
  QueueArray(const QueueArray<T> &src) = delete;
  QueueArray(QueueArray<T> &&src) noexcept;
  QueueArray<T> &operator=(QueueArray<T> &src) = delete;
  QueueArray<T> &operator=(QueueArray<T> &&src) noexcept;
  ~QueueArray() override { delete[] array_; }

  template<typename H>
  friend std::ostream &operator<<(std::ostream &out, const QueueArray<H> &queue);
  void push(const T &e) override;
  T pop() override;
  T getHead() const;
  bool isEmpty() const override { return head_ == tail_ && count_ == 0; }

private:
  T *array_;
  size_t head_ = 1;
  size_t tail_ = 1;
  size_t size_;
  size_t count_;

  void swap(QueueArray<T> &right);
};

template<typename T>
QueueArray<T>::QueueArray(size_t size):
    size_(size), head_(1), tail_(1), count_(0) {
  try {
    array_ = new T[size + 1];
  }
  catch (...) {
    throw WrongQueueSize();
  }
}

template<typename T>
void QueueArray<T>::swap(QueueArray<T> &right) {
  std::swap(array_, right.array_);
  std::swap(head_, right.head_);
  std::swap(tail_, right.tail_);
  std::swap(size_, right.size_);
  std::swap(count_, right.count_);
}

template<typename T>
QueueArray<T>::QueueArray(QueueArray<T> &&src) noexcept {
  swap(src);
}

template<typename T>
QueueArray<T> &QueueArray<T>::operator=(QueueArray<T> &&src) noexcept {
  if (this == &src) {
    return *this;
  }
  swap(src);
  return *this;
}

template<typename T>
void QueueArray<T>::push(const T &e) {
  if (isEmpty()) {
    array_[tail_] = e;
    count_++;
    return;
  }
  tail_ = (tail_ == size_) ? 1 : tail_ + 1;
  if (head_ == tail_) {
    throw QueueOverflow();
  }
  array_[tail_] = e;
  count_++;
}

template<typename T>
T QueueArray<T>::pop() {
  if (isEmpty()) {
    throw QueueUnderflow();
  }
  int headTemp = head_;
  if (headTemp != tail_ || count_ != 1) {
    head_ = (head_ == size_) ? 1 : head_ + 1;
  }
  count_--;
  return array_[headTemp];
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const QueueArray<T> &queue) {
  if (queue.isEmpty()) {
    out << "\n";
    return out;
  }
  if (queue.tail_ >= queue.head_) {
    for (size_t i = queue.head_; i <= queue.tail_; i++) {
      out << queue.array_[i] << " ";
    }
  } else {
    for (size_t i = queue.head_; i <= queue.size_; i++) {
      out << queue.array_[i] << " ";
    }
    for (size_t i = 1; i <= queue.tail_; i++) {
      out << queue.array_[i] << " ";
    }
  }
  out << "\n";
  return out;
}

template<typename T>
T QueueArray<T>::getHead() const {
  return array_[head_];
}

#endif //QUEUE_ARRAY_HPP
