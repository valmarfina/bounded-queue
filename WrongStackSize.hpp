#ifndef WRONG_STACK_SIZE_HPP
#define WRONG_STACK_SIZE_HPP

#include <exception>
#include <string>

class WrongStackSize : public std::exception
{
public:
  WrongStackSize() : reason_("Wrong stack size!") {}
  const char* what() const noexcept override{ return reason_; }

private:
  const char* reason_;
};

#endif //WRONG_STACK_SIZE_HPP
