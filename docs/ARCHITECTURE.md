# Project Architecture

## Overview

This document describes the architecture and design patterns used in this sample C++ project.

## Architecture Diagram

```
┌─────────────────────────────────────────────────┐
│                  Application                     │
│                  (main.cpp)                      │
└────────────────┬────────────────────────────────┘
                 │
                 │ uses
                 ↓
┌─────────────────────────────────────────────────┐
│              Calculator Library                  │
│             (myapp namespace)                    │
│                                                  │
│  ┌──────────────────────────────────────────┐  │
│  │         Calculator Class                 │  │
│  │  - add()                                 │  │
│  │  - subtract()                            │  │
│  │  - multiply()                            │  │
│  │  - divide()                              │  │
│  └──────────────────────────────────────────┘  │
└─────────────────────────────────────────────────┘
                 │
                 │ depends on
                 ↓
┌─────────────────────────────────────────────────┐
│           External Dependencies                  │
│                                                  │
│  - fmt (formatting library)                     │
│  - gtest (testing framework)                    │
└─────────────────────────────────────────────────┘
```

## Directory Structure

### `/include/myapp/`
**Public Headers**
- Contains public API headers
- Installed with the library
- Used by external consumers
- Well-documented with Doxygen comments

### `/src/`
**Implementation Files**
- Contains `.cpp` implementation files
- Private implementation details
- Not exposed to library consumers

### `/tests/`
**Unit Tests**
- Google Test framework
- Each source file has corresponding test file
- Tests are isolated and independent
- Run automatically in CI/CD

### `/cmake/`
**CMake Modules**
- Reusable CMake configuration
- Compiler warnings setup
- Static analyzer configuration
- Build system utilities

### `/docs/`
**Documentation**
- Architecture documentation (this file)
- API documentation
- User guides
- Development guides

## Design Patterns

### 1. Separation of Concerns
- **Interface**: Public headers in `include/`
- **Implementation**: Source files in `src/`
- **Tests**: Separate `tests/` directory

### 2. Namespace Organization
- All library code is in `myapp` namespace
- Prevents naming conflicts
- Clear ownership of symbols

### 3. Exception Safety
- Use RAII principles
- Proper exception handling for error conditions
- Clear error messages via exceptions

### 4. Const Correctness
- Member functions marked `const` when appropriate
- Parameters passed by const reference where suitable
- Enables compiler optimizations

## Build System

### CMake Structure
```
CMakeLists.txt (root)
├── Library target (myapp_lib)
├── Executable target (MyApp)
└── tests/CMakeLists.txt
    └── Test target (MyAppTests)
```

### Target Dependencies
```
MyApp (executable)
  └── myapp_lib (static library)
      └── fmt (external dependency)

MyAppTests (test executable)
  ├── myapp_lib
  └── GTest (external dependency)
```

## Dependency Management

### vcpkg Manifest Mode
- Dependencies declared in `vcpkg.json`
- Version constraints specified
- Automatic dependency resolution
- Reproducible builds

### Private Registry Support
- Custom packages via private registry
- `vcpkg-configuration.json` configures registries
- Overlay ports for local customizations

## Testing Strategy

### Unit Testing
- **Framework**: Google Test
- **Coverage Target**: >80%
- **Test Organization**: Mirror source structure
- **Naming Convention**: `<class>_test.cpp`

### Test Types
1. **Positive Tests**: Expected behavior
2. **Negative Tests**: Error conditions
3. **Edge Cases**: Boundary values
4. **Exception Tests**: Error handling

### Running Tests
```bash
cmake -B build -S .
cmake --build build
cd build && ctest
```

## CI/CD Pipeline

### Continuous Integration
1. **Build**: Multiple platforms (Linux, Windows, macOS)
2. **Test**: Run all unit tests
3. **Quality**: Static analysis, formatting checks
4. **Coverage**: Track code coverage

### Continuous Deployment
1. **Documentation**: Auto-generate and deploy
2. **Releases**: Package and publish artifacts
3. **Versioning**: Semantic versioning (SemVer)

## Code Quality

### Static Analysis
- **clang-tidy**: Modern C++ best practices
- **cppcheck**: Bug detection
- **Compiler warnings**: Strict warning levels

### Code Formatting
- **clang-format**: Automated formatting
- **Style Guide**: Based on Google C++ Style Guide
- **Pre-commit**: Format on commit

## Performance Considerations

### Compilation
- **Precompiled Headers**: For large projects
- **Unity Builds**: Faster compilation (when needed)
- **ccache**: Build caching

### Runtime
- **Inlining**: Small functions in headers
- **Move Semantics**: For performance-critical paths
- **RAII**: Zero-overhead abstraction

## Security

### Best Practices
- Input validation
- Bounds checking
- Exception safety
- Memory safety (smart pointers)

### Static Analysis
- Buffer overflow detection
- Integer overflow detection
- Use-after-free detection

## Scalability

### Adding New Components
1. Create header in `include/myapp/`
2. Create implementation in `src/`
3. Create tests in `tests/`
4. Update CMakeLists.txt
5. Add documentation

### Adding Dependencies
1. Update `vcpkg.json`
2. Find package in CMakeLists.txt
3. Link to targets
4. Update documentation

## Future Enhancements

### Potential Additions
- [ ] Benchmarking framework
- [ ] Sanitizer support (ASan, UBSan)
- [ ] Integration tests
- [ ] Performance profiling
- [ ] Documentation generation (Doxygen)
- [ ] Package distribution (Conan, vcpkg port)

## References

- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [CMake Best Practices](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [vcpkg Documentation](https://vcpkg.io/)
