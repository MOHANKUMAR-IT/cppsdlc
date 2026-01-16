#include "myapp/calculator.h"
#include <fmt/core.h>
#include <iostream>
#include <exception>

/**
 * @brief Main entry point for the application
 * 
 * Demonstrates the Calculator class with various operations
 * and proper error handling.
 */
int main() {
    try {
        myapp::Calculator calc;
        
        // Display application header
        fmt::print("==================================\n");
        fmt::print("  C++ SDLC Sample Application\n");
        fmt::print("  Simple Calculator Demo\n");
        fmt::print("==================================\n\n");
        
        // Perform arithmetic operations
        int a = 10;
        int b = 5;
        
        fmt::print("Operands: a = {}, b = {}\n\n", a, b);
        
        int sum = calc.add(a, b);
        fmt::print("Addition:       {} + {} = {}\n", a, b, sum);
        
        int diff = calc.subtract(a, b);
        fmt::print("Subtraction:    {} - {} = {}\n", a, b, diff);
        
        int product = calc.multiply(a, b);
        fmt::print("Multiplication: {} * {} = {}\n", a, b, product);
        
        double quotient = calc.divide(a, b);
        fmt::print("Division:       {} / {} = {:.2f}\n\n", a, b, quotient);
        
        // Demonstrate error handling
        fmt::print("Testing error handling:\n");
        try {
            calc.divide(a, 0);
        } catch (const std::invalid_argument& e) {
            fmt::print("Caught expected exception: {}\n", e.what());
        }
        
        fmt::print("\n==================================\n");
        fmt::print("  Application completed successfully!\n");
        fmt::print("==================================\n");
        
        return 0;
        
    } catch (const std::exception& e) {
        fmt::print(stderr, "Error: {}\n", e.what());
        return 1;
    }
}
