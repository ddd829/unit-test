/**
 * ===========================================================================
 * TEST_P Macro (Parameterized Test)
 * ===========================================================================
 * - Purpose: Runs the same test logic with different input parameters.
 * - Requires:
 *   1. Fixture deriving from `::testing::TestWithParam<T>`.
 *   2. `INSTANTIATE_TEST_SUITE_P` to define parameter sets.
 * - Access params: `GetParam()` within tests.
 * - Best for: Data-driven testing (boundary values, configurations).
 * - Example: Testing algorithms with multiple input combinations.
 * ===========================================================================
 */

#include "calculator.hpp"
#include "gtest/gtest.h"

// add test
class AdditionParamTestBySameLogic : public ::testing::TestWithParam<std::tuple<int, int, int>>
{
protected:
    Calculation::Calculator calculator;
};

INSTANTIATE_TEST_SUITE_P(
    AdditionTests,
    AdditionParamTestBySameLogic,
    ::testing::Values(
        std::make_tuple(1, 2, 3),
        std::make_tuple(-1, 1, 0),
        std::make_tuple(-1, -1, -2),
        std::make_tuple(0, 0, 0),
        std::make_tuple(INT_MAX, 0, INT_MAX),
        std::make_tuple(INT_MIN, 0, INT_MIN)));

TEST_P(AdditionParamTestBySameLogic, AddTest)
{
    auto [a, b, expected] = GetParam();
    EXPECT_EQ(calculator.add(a, b), expected);
}

// sub test
class SubtractParamTestBySameLogic : public ::testing::TestWithParam<std::tuple<int, int, int>>
{
protected:
    Calculation::Calculator calculator;
};

INSTANTIATE_TEST_SUITE_P(
    SubtractTests,
    SubtractParamTestBySameLogic,
    ::testing::Values(
        std::make_tuple(5, 3, 2),
        std::make_tuple(0, 0, 0),
        std::make_tuple(-1, -1, 0),
        std::make_tuple(100, 50, 50),
        std::make_tuple(INT_MAX, INT_MAX, 0),
        std::make_tuple(INT_MIN, INT_MIN, 0)));

TEST_P(SubtractParamTestBySameLogic, SubtractTest)
{
    auto [a, b, expected] = GetParam();
    EXPECT_EQ(calculator.sub(a, b), expected);
}

// div test normal
class DivisionParamTestBySameLogic : public ::testing::TestWithParam<std::tuple<double, double, double>>
{
protected:
    Calculation::Calculator calculator;
};

INSTANTIATE_TEST_SUITE_P(
    DivisionTests,
    DivisionParamTestBySameLogic,
    ::testing::Values(
        std::make_tuple(6, 3, 2),
        std::make_tuple(0, 1, 0),
        std::make_tuple(-1, -1, 1),
        std::make_tuple(100, 50, 2),
        std::make_tuple(INT_MAX, INT_MAX, 1),
        std::make_tuple(INT_MIN, INT_MIN, 1)));

TEST_P(DivisionParamTestBySameLogic, DivisionTest)
{
    auto [a, b, expected] = GetParam();
    EXPECT_EQ(calculator.div(a, b), expected);
}

// div test by zero
class DivisionByZeroParamTestBySameLogic : public ::testing::TestWithParam<std::tuple<double, double>>
{
protected:
    Calculation::Calculator calculator;
};

INSTANTIATE_TEST_SUITE_P(
    DivisionByZeroTests,
    DivisionByZeroParamTestBySameLogic,
    ::testing::Values(
        std::make_tuple(6, 0),
        std::make_tuple(0, 0),
        std::make_tuple(-1, 0),
        std::make_tuple(100, 0),
        std::make_tuple(INT_MAX, 0),
        std::make_tuple(INT_MIN, 0)));

TEST_P(DivisionByZeroParamTestBySameLogic, DivisionByZeroTest)
{
    auto [a, b] = GetParam();
    EXPECT_DEATH(calculator.div(a, b), " ");
}
