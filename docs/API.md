# API Documentation

## Calculator Class

### Overview

The `Calculator` class provides basic arithmetic operations. It's designed as a simple example for demonstrating project structure and testing practices.

### Namespace

`myapp`

### Header File

```cpp
#include <myapp/calculator.h>
```

---

## Public Methods

### Constructor

```cpp
Calculator()
```

**Description**: Default constructor. Creates a Calculator instance.

**Parameters**: None

**Example**:
```cpp
myapp::Calculator calc;
```

---

### add

```cpp
int add(int a, int b) const
```

**Description**: Adds two integers and returns the result.

**Parameters**:
- `a` (int): First operand
- `b` (int): Second operand

**Returns**: `int` - Sum of a and b

**Complexity**: O(1)

**Example**:
```cpp
myapp::Calculator calc;
int result = calc.add(5, 3);  // result = 8
```

---

### subtract

```cpp
int subtract(int a, int b) const
```

**Description**: Subtracts the second integer from the first.

**Parameters**:
- `a` (int): Minuend
- `b` (int): Subtrahend

**Returns**: `int` - Difference (a - b)

**Complexity**: O(1)

**Example**:
```cpp
myapp::Calculator calc;
int result = calc.subtract(10, 3);  // result = 7
```

---

### multiply

```cpp
int multiply(int a, int b) const
```

**Description**: Multiplies two integers.

**Parameters**:
- `a` (int): First factor
- `b` (int): Second factor

**Returns**: `int` - Product of a and b

**Complexity**: O(1)

**Example**:
```cpp
myapp::Calculator calc;
int result = calc.multiply(4, 3);  // result = 12
```

---

### divide

```cpp
double divide(int a, int b) const
```

**Description**: Divides the first integer by the second. Returns a floating-point result for precision.

**Parameters**:
- `a` (int): Dividend
- `b` (int): Divisor

**Returns**: `double` - Quotient (a / b)

**Throws**: 
- `std::invalid_argument` - When divisor (b) is zero

**Complexity**: O(1)

**Example**:
```cpp
myapp::Calculator calc;
double result = calc.divide(10, 2);  // result = 5.0

try {
    calc.divide(10, 0);  // Throws exception
} catch (const std::invalid_argument& e) {
    std::cout << "Error: " << e.what() << std::endl;
}
```

---

## Usage Examples

### Basic Usage

```cpp
#include <myapp/calculator.h>
#include <iostream>

int main() {
    myapp::Calculator calc;
    
    // Perform calculations
    std::cout << "5 + 3 = " << calc.add(5, 3) << std::endl;
    std::cout << "10 - 3 = " << calc.subtract(10, 3) << std::endl;
    std::cout << "4 * 3 = " << calc.multiply(4, 3) << std::endl;
    std::cout << "10 / 2 = " << calc.divide(10, 2) << std::endl;
    
    return 0;
}
```

### Error Handling

```cpp
#include <myapp/calculator.h>
#include <iostream>
#include <exception>

int main() {
    myapp::Calculator calc;
    
    try {
        double result = calc.divide(10, 0);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
```

### Using with fmt Library

```cpp
#include <myapp/calculator.h>
#include <fmt/core.h>

int main() {
    myapp::Calculator calc;
    
    int a = 15;
    int b = 4;
    
    fmt::print("Addition: {} + {} = {}\n", a, b, calc.add(a, b));
    fmt::print("Subtraction: {} - {} = {}\n", a, b, calc.subtract(a, b));
    fmt::print("Multiplication: {} * {} = {}\n", a, b, calc.multiply(a, b));
    fmt::print("Division: {} / {} = {:.2f}\n", a, b, calc.divide(a, b));
    
    return 0;
}
```

---

## Thread Safety

The `Calculator` class is **thread-safe** for concurrent reads since:
- All methods are `const`
- No mutable state
- No shared data modifications

Multiple threads can safely use separate `Calculator` instances concurrently.

---

## Performance Notes

- All operations are O(1) constant time
- Methods are lightweight and can be inlined
- No dynamic memory allocation
- Exception throwing only on error conditions

---

## Version History

| Version | Date | Changes |
|---------|------|---------|
| 1.0.0 | 2026-01-15 | Initial release with basic operations |

---

## See Also

- [Architecture Documentation](ARCHITECTURE.md)
- [Contributing Guidelines](../CONTRIBUTING.md)
- [Project README](../README.md)
