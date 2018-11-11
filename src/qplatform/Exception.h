#ifndef QPLATFORM_EXCEPTION_H
#define QPLATFORM_EXCEPTION_H

#include <string>
#include <exception>

class Exception : public std::exception
{
public:
  Exception(std::string message)
  {
    this->message = message;
  }

  virtual ~Exception() throw()
  {

  }

  virtual const char* what() const throw()
  {
    return message.c_str();
  }

private:
  std::string message;

};

#endif
