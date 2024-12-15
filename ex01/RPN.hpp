#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <sstream>

class RPN
{
public:
    RPN();
    ~RPN();
    int evaluate(const std::string &expression);

private:
    bool isOperator(const std::string &token);
    int performOperation(const std::string &operation, int operand1, int operand2);
};