#include "myapp/calculator.h"
#include <gtest/gtest.h>
#include <stdexcept>

/**
 * Test fixture for Calculator tests
 */
class CalculatorTest : public ::testing::Test {
protected:
    myapp::Calculator calculator;
};

// ============================================================================
// Addition Tests
// ============================================================================

TEST_F(CalculatorTest, AddPositiveNumbers) {
    EXPECT_EQ(calculator.add(5, 3), 8);
}

TEST_F(CalculatorTest, AddNegativeNumbers) {
    EXPECT_EQ(calculator.add(-5, -3), -8);
}

TEST_F(CalculatorTest, AddMixedNumbers) {
    EXPECT_EQ(calculator.add(5, -3), 2);
    EXPECT_EQ(calculator.add(-5, 3), -2);
}

TEST_F(CalculatorTest, AddZero) {
    EXPECT_EQ(calculator.add(5, 0), 5);
    EXPECT_EQ(calculator.add(0, 5), 5);
    EXPECT_EQ(calculator.add(0, 0), 0);
}

// ============================================================================
// Subtraction Tests
// ============================================================================

TEST_F(CalculatorTest, SubtractPositiveNumbers) {
    EXPECT_EQ(calculator.subtract(10, 3), 7);
}

TEST_F(CalculatorTest, SubtractNegativeNumbers) {
    EXPECT_EQ(calculator.subtract(-10, -3), -7);
}

TEST_F(CalculatorTest, SubtractMixedNumbers) {
    EXPECT_EQ(calculator.subtract(5, -3), 8);
    EXPECT_EQ(calculator.subtract(-5, 3), -8);
}

TEST_F(CalculatorTest, SubtractZero) {
    EXPECT_EQ(calculator.subtract(5, 0), 5);
    EXPECT_EQ(calculator.subtract(0, 5), -5);
}

// ============================================================================
// Multiplication Tests
// ============================================================================

TEST_F(CalculatorTest, MultiplyPositiveNumbers) {
    EXPECT_EQ(calculator.multiply(4, 3), 12);
}

TEST_F(CalculatorTest, MultiplyNegativeNumbers) {
    EXPECT_EQ(calculator.multiply(-4, -3), 12);
}

TEST_F(CalculatorTest, MultiplyMixedNumbers) {
    EXPECT_EQ(calculator.multiply(4, -3), -12);
    EXPECT_EQ(calculator.multiply(-4, 3), -12);
}

TEST_F(CalculatorTest, MultiplyByZero) {
    EXPECT_EQ(calculator.multiply(5, 0), 0);
    EXPECT_EQ(calculator.multiply(0, 5), 0);
}

TEST_F(CalculatorTest, MultiplyByOne) {
    EXPECT_EQ(calculator.multiply(5, 1), 5);
    EXPECT_EQ(calculator.multiply(1, 5), 5);
}

// ============================================================================
// Division Tests
// ============================================================================

TEST_F(CalculatorTest, DividePositiveNumbers) {
    EXPECT_DOUBLE_EQ(calculator.divide(10, 2), 5.0);
    EXPECT_NEAR(calculator.divide(10, 3), 3.333333, 0.0001);
}

TEST_F(CalculatorTest, DivideNegativeNumbers) {
    EXPECT_DOUBLE_EQ(calculator.divide(-10, -2), 5.0);
}

TEST_F(CalculatorTest, DivideMixedNumbers) {
    EXPECT_DOUBLE_EQ(calculator.divide(10, -2), -5.0);
    EXPECT_DOUBLE_EQ(calculator.divide(-10, 2), -5.0);
}

TEST_F(CalculatorTest, DivideByOne) {
    EXPECT_DOUBLE_EQ(calculator.divide(5, 1), 5.0);
}

TEST_F(CalculatorTest, DivideZeroByNumber) {
    EXPECT_DOUBLE_EQ(calculator.divide(0, 5), 0.0);
}

TEST_F(CalculatorTest, DivideByZeroThrowsException) {
    EXPECT_THROW(calculator.divide(10, 0), std::invalid_argument);
}

TEST_F(CalculatorTest, DivideByZeroExceptionMessage) {
    try {
        calculator.divide(10, 0);
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Division by zero is not allowed");
    } catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(CalculatorTest, MaxIntAddition) {
    // Note: This may overflow, but demonstrates boundary testing
    int max_int = std::numeric_limits<int>::max();
    EXPECT_NO_THROW(calculator.add(max_int, 0));
}

TEST_F(CalculatorTest, MinIntSubtraction) {
    int min_int = std::numeric_limits<int>::min();
    EXPECT_NO_THROW(calculator.subtract(min_int, 0));
}

// ============================================================================
// Main
// ============================================================================

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
