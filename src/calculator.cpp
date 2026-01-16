#include "myapp/calculator.h"
#include <stdexcept>

namespace myapp {

int Calculator::add(int a, int b) const {
    return a + b;
}

int Calculator::subtract(int a, int b) const {
    return a - b;
}

int Calculator::multiply(int a, int b) const {
    return a * b;
}

double Calculator::divide(int a, int b) const {
    if (b == 0) {
        throw std::invalid_argument("Division by zero is not allowed");
    }
    return static_cast<double>(a) / static_cast<double>(b);
}

} // namespace myapp
