#ifndef WRONG_QUEUE_SIZE_HPP
#define WRONG_QUEUE_SIZE_HPP

#include <exception>

class WrongQueueSize : public std::exception
{
public:
  WrongQueueSize(): reason_("Queue's size is not correct") {}
  const char *what() const noexcept override { return reason_; }

private:
  const char *reason_;
};

#endif //WRONG_QUEUE_SIZE_HPP
