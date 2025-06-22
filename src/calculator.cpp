#include "calculator.hpp"
#include <cassert>

namespace Calculation
{
    int Calculator::add(int a, int b)
    {
        return a + b;
    }

    int Calculator::sub(int a, int b)
    {
        return a - b;
    }

    double Calculator::div(double a, double b)
    {
        assert(b != 0 && "Division by zero is not allowed.");
        return a / b;
    }
}