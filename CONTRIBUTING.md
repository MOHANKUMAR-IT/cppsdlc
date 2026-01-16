# Contributing Guidelines

Thank you for considering contributing to this project!

## Code of Conduct

- Be respectful and inclusive
- Focus on constructive feedback
- Help maintain a positive environment

## Development Process

### 1. Fork and Clone

```bash
git clone https://github.com/MOHANKUMAR-IT/cppsdlc.git
cd cppsdlc
```

### 2. Create a Branch

```bash
git checkout -b feature/your-feature-name
```

### 3. Make Changes

- Follow the coding standards (see below)
- Add tests for new functionality
- Update documentation as needed

### 4. Test Your Changes

```bash
cmake -B build -S .
cmake --build build
cd build && ctest
```

### 5. Commit Your Changes

Follow conventional commits format:
```
<type>(<scope>): <subject>

<body>

<footer>
```

Types: `feat`, `fix`, `docs`, `style`, `refactor`, `test`, `chore`

Example:
```
feat(calculator): add division operation

- Implement division method
- Add error handling for division by zero
- Update tests

Closes #123
```

### 6. Submit Pull Request

- Ensure all tests pass
- Update CHANGELOG.md
- Reference related issues

## Coding Standards

### C++ Style Guide

- Follow **C++17** standard minimum
- Use **snake_case** for functions and variables
- Use **PascalCase** for classes
- Use **UPPER_CASE** for constants
- Max line length: **100 characters**

### Code Formatting

Run clang-format before committing:
```bash
clang-format -i src/*.cpp include/**/*.h
```

### Naming Conventions

```cpp
// Classes
class CalculatorEngine { };

// Functions
int calculate_sum(int a, int b);

// Variables
int user_count = 0;
std::string file_name;

// Constants
const int MAX_BUFFER_SIZE = 1024;

// Private members
class MyClass {
private:
    int value_;  // Trailing underscore
};
```

### Documentation

Use Doxygen-style comments:
```cpp
/**
 * @brief Calculates the sum of two integers
 * @param a First operand
 * @param b Second operand
 * @return Sum of a and b
 */
int add(int a, int b);
```

## Testing Requirements

- All new features must include unit tests
- Maintain or improve code coverage
- Test edge cases and error conditions

## Review Process

1. **Automated Checks**: CI/CD must pass
2. **Code Review**: At least one approval required
3. **Testing**: Reviewer tests the changes locally
4. **Merge**: Squash and merge to main branch

## Questions?

Feel free to open an issue for any questions or clarifications.
