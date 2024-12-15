#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

bool RPN::isOperator(const std::string &token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int RPN::performOperation(const std::string &operation, int operand1, int operand2)
{
    if (operation == "+")
        return operand1 + operand2;
    else if (operation == "-")
        return operand1 - operand2;
    else if (operation == "*")
        return operand1 * operand2;
    else if (operation == "/")
    {
        if (operand2 == 0)
        {
            std::cerr << "Error: division by zero" << std::endl;
            exit(EXIT_FAILURE);
        }
        return operand1 / operand2;
    }
    return 0;
}

int RPN::evaluate(const std::string &expression)
{
    std::istringstream iss(expression);
    std::stack<int> stack;
    std::string token;

    while (iss >> token)
    {
        if (isOperator(token))
        {
            if (stack.size() < 2)
            {
                std::cerr << "Error: invalid expression" << std::endl;
                exit(EXIT_FAILURE);
            }
            int operand2 = stack.top();
            stack.pop();
            int operand1 = stack.top();
            stack.pop();
            int result = performOperation(token, operand1, operand2);
            stack.push(result);
        }
        else
        {
            int number;
            std::istringstream tokenStream(token);
            if (!(tokenStream >> number))
            {
                std::cerr << "Error: invalid token" << std::endl;
                exit(EXIT_FAILURE);
            }
            stack.push(number);
        }
    }

    if (stack.size() != 1)
    {
        std::cerr << "Error: invalid expression" << std::endl;
        exit(EXIT_FAILURE);
    }

    return stack.top();
}