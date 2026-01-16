# Build and Run Guide

This guide walks you through building and running the C++ SDLC sample project.

## Prerequisites

Ensure you have the following installed:
- **CMake** 3.20 or higher
- **C++ Compiler**: GCC 10+, Clang 12+, or MSVC 2019+
- **vcpkg**: C++ package manager
- **Git**: Version control

## Step 1: Install vcpkg

### Windows
```powershell
# Clone vcpkg
git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
cd C:\vcpkg

# Bootstrap vcpkg
.\bootstrap-vcpkg.bat

# Add to PATH (optional)
$env:PATH += ";C:\vcpkg"
```

### Linux/macOS
```bash
# Clone vcpkg
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
cd ~/vcpkg

# Bootstrap vcpkg
./bootstrap-vcpkg.sh

# Add to PATH (optional)
export PATH="$HOME/vcpkg:$PATH"
```

## Step 2: Clone the Project

```bash
git clone https://github.com/MOHANKUMAR-IT/cppsdlc.git
cd cppsdlc
```

## Step 3: Configure the Build

### Windows
```powershell
cmake -B build -S . `
  -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake `
  -DCMAKE_BUILD_TYPE=Release `
  -DBUILD_TESTS=ON
```

### Linux/macOS
```bash
cmake -B build -S . \
  -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_TESTS=ON
```

## Step 4: Build

```bash
# Build the project
cmake --build build --config Release

# Or build with parallelization
cmake --build build --config Release --parallel 4
```

## Step 5: Run the Application

### Windows
```powershell
.\build\bin\Release\MyApp.exe
```

### Linux/macOS
```bash
./build/bin/MyApp
```

## Step 6: Run Tests

```bash
# Change to build directory
cd build

# Run all tests
ctest --output-on-failure

# Run tests with verbose output
ctest -V

# Run specific test
ctest -R calculator_test
```

## Build Options

### Enable Compiler Warnings
```bash
cmake -B build -S . \
  -DENABLE_WARNINGS=ON
```

### Enable Static Analysis
```bash
cmake -B build -S . \
  -DENABLE_STATIC_ANALYSIS=ON
```

### Debug Build
```bash
cmake -B build -S . \
  -DCMAKE_BUILD_TYPE=Debug
```

### Disable Tests
```bash
cmake -B build -S . \
  -DBUILD_TESTS=OFF
```

## Installation

Install the built application and libraries:

```bash
cmake --install build --prefix /path/to/install
```

## Cleaning

Remove build artifacts:

```bash
# Remove build directory
rm -rf build

# Or use CMake
cmake --build build --target clean
```

## Troubleshooting

### vcpkg not found
Ensure `CMAKE_TOOLCHAIN_FILE` points to the correct vcpkg toolchain file.

### Dependency installation fails
```bash
# Manual dependency installation
vcpkg install fmt gtest
```

### Build errors
```bash
# Clean and rebuild
rm -rf build
cmake -B build -S .
cmake --build build
```

### Test failures
```bash
# Run tests with verbose output
cd build
ctest --verbose
```

## IDE Integration

### Visual Studio Code
1. Install C++ and CMake extensions
2. Open project folder
3. Select CMake kit
4. Configure and build using status bar

### Visual Studio (Windows)
```powershell
# Generate Visual Studio solution
cmake -B build -S . -G "Visual Studio 17 2022"

# Open the solution
start build\MyApp.sln
```

### CLion
1. Open project folder
2. CLion will automatically detect CMakeLists.txt
3. Configure toolchain in Settings
4. Build and run using toolbar

## Next Steps

- Read [ARCHITECTURE.md](ARCHITECTURE.md) for project structure
- Check [API.md](API.md) for API documentation
- Review [CONTRIBUTING.md](../CONTRIBUTING.md) for development guidelines
