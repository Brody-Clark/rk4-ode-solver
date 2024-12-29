#pragma once
#include <string>
#include <vector>
#include "exprtk.hpp"

class RungeKuttaSolver
{
public:

    RungeKuttaSolver();

    void Solve(const float& y0, const float& h, const float& t, const float& t0,
        const std::string& expr, std::vector<std::vector<float>>& out);

    template <typename T>
    bool IsExpressionValid(const std::string& expression_str)
    {
        typedef exprtk::symbol_table<T> symbol_table_t;
        typedef exprtk::expression<T> expression_t;
        typedef exprtk::parser<T>       parser_t;

        symbol_table_t symbol_table;
        float t = 0.0;
        float y = 0.0;
        symbol_table.add_variable("t", t);
        symbol_table.add_variable("y", y);

        expression_t expression;
        expression.register_symbol_table(symbol_table);

        parser_t parser;
        return parser.compile(expression_str, expression);
    }

private:

    template <typename T>
    const float dydt(T t, T y, const std::string& expression_string )
    {
        typedef exprtk::symbol_table<T> symbol_table_t;
        typedef exprtk::expression<T> expression_t;
        typedef exprtk::parser<T>       parser_t;

        symbol_table_t symbol_table;
        symbol_table.add_variable("t", t);
        symbol_table.add_variable("y", y);
        symbol_table.add_constants();

        expression_t expression;
        expression.register_symbol_table(symbol_table);
 
        parser_t parser;
        parser.compile(expression_string, expression);

        return static_cast<float>(expression.value());
    }

     

};

