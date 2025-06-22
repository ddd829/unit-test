/**
 * ===========================================================================
 * TEST_F Macro (Fixture-Based Test)
 * ===========================================================================
 * - Purpose: Tests with shared setup/teardown (via a test fixture).
 * - Fixture: Derives from `::testing::Test`; defines `SetUp()`/`TearDown()`.
 * - Per-test behavior: Fresh fixture instance per test (isolated state).
 * - Best for: Tests requiring common initialization (e.g., same instance).
 * - Example: Resource management, stateful object testing.
 * ===========================================================================
 */

#include "calculator.hpp"
#include "gtest/gtest.h"

class CalculatorTestBySameInit : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    Calculation::Calculator calculator{}; // 所有测试用例共享测试对象 calculator
};

TEST_F(CalculatorTestBySameInit, GivenTwoNumbers_WhenAddCalled_ThenReturnsCorrectSum)
{
    EXPECT_EQ(calculator.add(1, 2), 3);
    EXPECT_EQ(calculator.add(-1, 1), 0);
    EXPECT_EQ(calculator.add(-1, -1), -2);
    EXPECT_EQ(calculator.add(0, 0), 0);
    EXPECT_EQ(calculator.add(INT_MAX, 0), INT_MAX);
    EXPECT_EQ(calculator.add(INT_MIN, 0), INT_MIN);
    EXPECT_EQ(calculator.add(INT_MAX, INT_MIN), -1); // 特殊情况
}

TEST_F(CalculatorTestBySameInit, GivenTwoNumbers_WhenSubCalled_ThenReturnsCorrectDifference)
{
    EXPECT_EQ(calculator.sub(1, 2), -1);
    EXPECT_EQ(calculator.sub(-1, 1), -2);
    EXPECT_EQ(calculator.sub(-1, -1), 0);
    EXPECT_EQ(calculator.sub(0, 0), 0);
    EXPECT_EQ(calculator.sub(INT_MAX, INT_MAX), 0);
    EXPECT_EQ(calculator.sub(INT_MIN, INT_MIN), 0);
}

TEST_F(CalculatorTestBySameInit, GivenTwoDoubles_WhenDivCalled_ThenReturnsCorrectQuotient)
{
    EXPECT_DOUBLE_EQ(calculator.div(4.0, 2.0), 2.0);
    EXPECT_DOUBLE_EQ(calculator.div(-4.0, 2.0), -2.0);
    EXPECT_DOUBLE_EQ(calculator.div(0.0, 1.0), 0.0);
    EXPECT_DOUBLE_EQ(calculator.div(1.0, 1.0), 1.0);
    EXPECT_DOUBLE_EQ(calculator.div(INT_MAX, 1), INT_MAX);
    EXPECT_DOUBLE_EQ(calculator.div(INT_MIN, 1), INT_MIN);

    // Test division by zero
    EXPECT_DEATH(calculator.div(1.0, 0.0), " ");
}

TEST_F(CalculatorTestBySameInit, GivenDivisorZero_WhenDivCalled_ThenProgramTerminates)
{
    // Test division by zero
    EXPECT_DEATH(calculator.div(1.0, 0.0), " ");
}