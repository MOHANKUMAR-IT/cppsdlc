cmake_minimum_required(VERSION 3.20)

# Project metadata
project(MyApp
    VERSION 1.0.0
    DESCRIPTION "Sample C++ project demonstrating SDLC best practices"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for IDEs and tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Options
option(BUILD_TESTS "Build unit tests" ON)
option(ENABLE_WARNINGS "Enable compiler warnings" ON)
option(ENABLE_STATIC_ANALYSIS "Enable static analysis tools" OFF)

# Include custom CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Compiler warnings
if(ENABLE_WARNINGS)
    include(CompilerWarnings)
    set_project_warnings()
endif()

# Static analyzers
if(ENABLE_STATIC_ANALYSIS)
    include(StaticAnalyzers)
endif()

# Find dependencies via vcpkg
find_package(fmt CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

# Library target
add_library(myapp_lib STATIC
    src/calculator.cpp
)

target_include_directories(myapp_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(myapp_lib
    PUBLIC
        fmt::fmt
        JsonCpp::JsonCpp
)

# Generate version resource files
set(APP_NAME "MyApp")
set(APP_DESCRIPTION "C++ SDLC Sample Calculator Application")
configure_file(src/version.rc.in ${CMAKE_CURRENT_BINARY_DIR}/myapp_version.rc @ONLY)

set(APP_NAME "JsonExample")
set(APP_DESCRIPTION "JSON and fmt Library Example")
configure_file(src/version.rc.in ${CMAKE_CURRENT_BINARY_DIR}/jsonexample_version.rc @ONLY)

# Executable target
add_executable(MyApp
    src/main.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/myapp_version.rc
)

target_link_libraries(MyApp
    PRIVATE
        myapp_lib
        JsonCpp::JsonCpp
        fmt::fmt
)

# JSON Example executable
add_executable(JsonExample
    src/json_example.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/jsonexample_version.rc
)

target_link_libraries(JsonExample
    PRIVATE
        fmt::fmt
        JsonCpp::JsonCpp
)

# Tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Installation
include(GNUInstallDirs)

# Install runtime DLLs on Windows (for dynamic linking)
if(WIN32)
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP FALSE)
    include(InstallRequiredSystemLibraries)
    
    # Install vcpkg DLLs alongside executables
    install(CODE [[
        file(GET_RUNTIME_DEPENDENCIES
            EXECUTABLES $<TARGET_FILE:MyApp> $<TARGET_FILE:JsonExample>
            RESOLVED_DEPENDENCIES_VAR _r_deps
            UNRESOLVED_DEPENDENCIES_VAR _u_deps
            DIRECTORIES ${CMAKE_BINARY_DIR}/bin ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin
            PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
            POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
        )
        foreach(_file ${_r_deps})
            file(INSTALL
                DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
                TYPE SHARED_LIBRARY
                FOLLOW_SYMLINK_CHAIN
                FILES "${_file}"
            )
        endforeach()
    ]])
endif()

install(TARGETS MyApp JsonExample myapp_lib
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# CPack configuration for packaging
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR "Your Organization")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
include(CPack)
