#ifndef QUEUE_HPP
#define QUEUE_HPP

template<class T>
class Queue
{
public:
  virtual ~Queue() = default;
  virtual void push(const T &e) = 0;
  virtual T pop() = 0;
  virtual bool isEmpty() const = 0;

};

#endif //QUEUE_HPP
