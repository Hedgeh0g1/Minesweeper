#ifndef NUMBEREXCEPTION_H
#define NUMBEREXCEPTION_H

#include <stdexcept>
#include <string>

class NumberException : public std::runtime_error {
public:
    NumberException(const std::string& message) : std::runtime_error(message) {}
};

#endif // NUMBEREXCEPTION_H
