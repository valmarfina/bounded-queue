#ifndef QUEUE_OVERFLOW_HPP
#define QUEUE_OVERFLOW_HPP

#include <exception>

class QueueOverflow : public std::exception
{
public:
  QueueOverflow(): reason_("Queue Overflow") {}
  const char *what() const noexcept override { return reason_; }

private:
  const char *reason_;
};

#endif //QUEUE_OVERFLOW_HPP
