/**
 * ===========================================================================
 * TEST Macro (Basic Test Case)
 * ===========================================================================
 * - Purpose: Standalone tests with no shared setup/teardown.
 * - Best for: Stateless tests, pure functions, or simple assertions.
 * - Isolation: Each test runs independently.
 * - No access to fixture members.
 * - Example: Basic arithmetic, logic validation.
 * ===========================================================================
 */

#include "calculator.hpp"
#include "gtest/gtest.h"

TEST(AdditionTestByIndependently, GivenTwoNumbers_WhenAddCalled_ThenReturnsCorrectSum)
{
    Calculation::Calculator calculator;
    EXPECT_EQ(calculator.add(1, 2), 3);
    EXPECT_EQ(calculator.add(-1, 1), 0);
    EXPECT_EQ(calculator.add(-1, -1), -2);
    EXPECT_EQ(calculator.add(INT_MAX, 0), INT_MAX);
    EXPECT_EQ(calculator.add(INT_MIN, 0), INT_MIN);
    EXPECT_EQ(calculator.add(0, 0), 0);
}

TEST(SubtractTestByIndependently, GivenTwoNumbers_WhenSubCalled_ThenReturnsCorrectDifference)
{
    Calculation::Calculator calculator;
    EXPECT_EQ(calculator.sub(1, 2), -1);
    EXPECT_EQ(calculator.sub(-1, 1), -2);
    EXPECT_EQ(calculator.sub(-1, -1), 0);
    EXPECT_EQ(calculator.sub(INT_MAX, INT_MAX), 0);
    EXPECT_EQ(calculator.sub(INT_MIN, INT_MIN), 0);
    EXPECT_EQ(calculator.sub(0, 0), 0);
}

TEST(DivisionTestByIndependently, GivenTwoDoubles_WhenDivCalled_ThenReturnsCorrectQuotient)
{
    Calculation::Calculator calculator;
    EXPECT_DOUBLE_EQ(calculator.div(4.0, 2.0), 2.0);
    EXPECT_DOUBLE_EQ(calculator.div(-4.0, 2.0), -2.0);
    EXPECT_DOUBLE_EQ(calculator.div(0.0, 1.0), 0.0);
    EXPECT_DOUBLE_EQ(calculator.div(1.0, 1.0), 1.0);
    EXPECT_DOUBLE_EQ(calculator.div(INT_MAX, 1), INT_MAX);
    EXPECT_DOUBLE_EQ(calculator.div(INT_MIN, 1), INT_MIN);
}

TEST(DivisionTestByIndependently, GivenDivisorZero_WhenDivCalled_ThenProgramTerminates)
{
    Calculation::Calculator calculator;
    // Test division by zero
    EXPECT_DEATH(calculator.div(1.0, 0.0), " ");
}