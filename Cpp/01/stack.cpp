#include <iostream>

#include "stack.h"

int main()
{
    stack<bool, 10> sb{};

    sb.push(true);
    sb.push(true);
    sb.push(true);
    sb.push(false);
    sb.push(false);
    sb.push(false);
    sb.push(false);
    sb.top() = true;

    while (!sb.empty())
    {
        std::cout << sb.top() << "\n";
        sb.pop();
    }
    std::cout << std::endl;
}