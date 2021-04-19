#ifndef STACK_OVERFLOW_HPP
#define STACK_OVERFLOW_HPP

#include <exception>
#include <string>

class StackOverflow : public std::exception
{
public:
  StackOverflow() : reason_("Stack overflow!") {}
  const char* what() const noexcept override{ return reason_; }

private:
  const char* reason_;
};

#endif //STACK_OVERFLOW_HPP
  