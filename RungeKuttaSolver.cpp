#include "RungeKuttaSolver.h"

void RungeKuttaSolver::Solve(const float& y0, const float& h, const float& t, const float& t0, const std::string& expr, std::vector<std::vector<float>>& out)
{
    if (!IsExpressionValid(expr))
    {
        throw std::runtime_error(std::string("Invalid expression"));
    }

    if (t0 > t)
    {
        return;
    }

    const int x = int(std::ceil((t - t0) / h)) + 1;
    out.resize(x, std::vector<float>(2));

    float w = y0;
    float k1, k2, k3, k4;
    float i = t0;
    int index = 0;

    while (i < t)
    {
        out[index] = { i, w };

        k1 = h * dydt<float>(i, w, expr);
        k2 = h * dydt<float>(i + h/2, w + k1/2, expr);
        k3 = h * dydt<float>(i + h/2, w + k2/2, expr);
        k4 = h * dydt<float>(i + h, w + k3, expr);

        w = w + (k1 + k2 + k3 + k4) / 6;

        index++;
        i += h;
    }

}

const bool RungeKuttaSolver::IsExpressionValid(const std::string expression) {

    for (int i = 0; i < expression.size(); i++)
    {
        if (expression[i] != 't' && expression[i] != 'y' && std::isalpha(expression[i])) return false;
    }

    return true;
    
}





