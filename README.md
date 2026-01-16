# C++ SDLC Best Practices Sample Project

A sample C++ project demonstrating Software Development Lifecycle (SDLC) best practices, modern project structure, and dependency management using vcpkg.

## 📋 Table of Contents

- [Overview](#overview)
- [Project Structure](#project-structure)
- [Prerequisites](#prerequisites)
- [Building the Project](#building-the-project)
- [Running Tests](#running-tests)
- [Dependency Management](#dependency-management)
- [CI/CD](#cicd)
- [Contributing](#contributing)

## 🎯 Overview

This project demonstrates:
- **Modern C++ project structure** with clear separation of concerns
- **CMake-based build system** for cross-platform compatibility
- **vcpkg dependency management** including private registry configuration
- **Unit testing** with Google Test framework
- **CI/CD pipeline** using GitHub Actions
- **Code quality tools** and standards
- **Comprehensive documentation** following SDLC best practices

## 📁 Project Structure

```
cppsdlc/
├── cmake/                  # CMake modules and scripts
│   ├── CompilerWarnings.cmake
│   └── StaticAnalyzers.cmake
├── docs/                   # Documentation
│   ├── ARCHITECTURE.md
│   └── API.md
├── include/                # Public headers
│   └── myapp/
│       └── calculator.h
├── src/                    # Implementation files
│   ├── calculator.cpp
│   └── main.cpp
├── tests/                  # Unit tests
│   └── calculator_test.cpp
├── vcpkg-configuration.json  # vcpkg configuration
├── vcpkg.json             # Dependency manifest
├── CMakeLists.txt         # Root CMake file
├── .clang-format          # Code formatting rules
├── .gitignore             # Git ignore patterns
├── CHANGELOG.md           # Version history
└── README.md              # This file
```

## 🔧 Prerequisites

- **C++ Compiler**: GCC 10+, Clang 12+, or MSVC 2019+
- **CMake**: Version 3.20 or higher
- **vcpkg**: Package manager for C++
- **Git**: For version control

## 🚀 Building the Project

### 1. Install vcpkg

```bash
# Clone vcpkg
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh  # On Windows: .\bootstrap-vcpkg.bat
```

### 2. Configure and Build

```bash
# Configure with CMake
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build build --config Release

# Run the application
./build/bin/MyApp
```

## 🧪 Running Tests

```bash
# Build and run tests
cd build
ctest --output-on-failure

# Or run the test executable directly
./tests/MyAppTests
```

## 📦 Dependency Management

This project uses **vcpkg** for dependency management with support for private registries.

### vcpkg.json (Manifest Mode)

Dependencies are declared in `vcpkg.json`:
```json
{
  "dependencies": [
    "fmt",
    "gtest"
  ]
}
```

### Private vcpkg Registry

The `vcpkg-configuration.json` file demonstrates how to configure private registries:

```json
{
  "registries": [
    {
      "kind": "git",
      "repository": "https://github.com/MOHANKUMAR-IT/custom-vcpkg-registry",
      "baseline": "commit-hash",
      "packages": ["custom-package"]
    }
  ]
}
```

For internal/enterprise environments, you can:
1. Host your own Git-based registry
2. Use Azure Artifacts or similar
3. Create custom port overlays

## 🔄 CI/CD

The project includes GitHub Actions workflows for:
- **Build and Test**: Runs on every push/PR
- **Code Quality**: Static analysis and formatting checks
- **Release**: Automated versioning and artifact creation

See [.github/workflows/](.github/workflows/) for configuration.

## 👥 Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on:
- Code of conduct
- Coding standards
- Pull request process
- Testing requirements

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 📞 Support

For questions or issues, please create an issue in the repository.
