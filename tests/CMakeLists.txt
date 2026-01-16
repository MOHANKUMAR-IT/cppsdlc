# Find GTest package
find_package(GTest CONFIG REQUIRED)

# Enable testing
include(GoogleTest)

# Test executable
add_executable(MyAppTests
    calculator_test.cpp
)

target_link_libraries(MyAppTests
    PRIVATE
        myapp_lib
        GTest::gtest
        GTest::gtest_main
)

# Discover tests
gtest_discover_tests(MyAppTests
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    PROPERTIES
        LABELS "unit"
)

# Add custom target for running tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS MyAppTests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running unit tests"
)
