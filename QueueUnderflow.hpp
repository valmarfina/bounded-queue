#ifndef QUEUE_UNDERFLOW_HPP
#define QUEUE_UNDERFLOW_HPP

#include <exception>

class QueueUnderflow : public std::exception
{
public:
  QueueUnderflow(): reason_("Queue Underflow") {}
  const char *what() const noexcept override { return reason_; }

private:
  const char *reason_;
};

#endif //QUEUE_UNDERFLOW_HPP
