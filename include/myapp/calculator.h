#ifndef MYAPP_CALCULATOR_H
#define MYAPP_CALCULATOR_H

namespace myapp {

/**
 * @brief A simple calculator class demonstrating basic operations
 * 
 * This class provides basic arithmetic operations for demonstration
 * purposes in the SDLC best practices sample project.
 */
class Calculator {
public:
    /**
     * @brief Construct a new Calculator object
     */
    Calculator() = default;
    
    /**
     * @brief Destroy the Calculator object
     */
    ~Calculator() = default;
    
    /**
     * @brief Add two integers
     * @param a First operand
     * @param b Second operand
     * @return Sum of a and b
     */
    int add(int a, int b) const;
    
    /**
     * @brief Subtract two integers
     * @param a First operand
     * @param b Second operand
     * @return Difference of a and b (a - b)
     */
    int subtract(int a, int b) const;
    
    /**
     * @brief Multiply two integers
     * @param a First operand
     * @param b Second operand
     * @return Product of a and b
     */
    int multiply(int a, int b) const;
    
    /**
     * @brief Divide two integers
     * @param a Dividend
     * @param b Divisor
     * @return Quotient of a and b (a / b)
     * @throws std::invalid_argument if b is zero
     */
    double divide(int a, int b) const;
};

} // namespace myapp

#endif // MYAPP_CALCULATOR_H
