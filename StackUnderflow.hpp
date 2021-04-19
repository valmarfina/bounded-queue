#ifndef STACK_UNDERFLOW_HPP
#define STACK_UNDERFLOW_HPP

#include <exception>
#include <string>

class StackUnderflow : public std::exception
{
public:
  StackUnderflow() : reason_("Stack underflow!") {}
  const char* what() const noexcept override{ return reason_; }

private:
  const char* reason_;
};

#endif //STACK_UNDERFLOW_HPP
