// Copyright 2026 Maksim

#include <string>
#include "../StackMas_lib/Stack.h"
bool check_breckets(std::string expression) {
    size_t size = expression.size();
    Stack<char> stack(size);
    int i = 0;
    while(i<size) {
        char skoba = expression[i];
        if (skoba == '(' || skoba == '[' || skoba == '{') {
            stack.push(skoba);
            i++;continue;
        }
        if (stack.is_empty()) { return false; }
        char stack_skoba = stack.top();
        if (skoba == ')' && stack_skoba == '(') { stack.pop();i++;continue; }
        if (skoba == ']' && stack_skoba == '[') { stack.pop();i++;continue; }
        if (skoba == '}' && stack_skoba == '{') { stack.pop();i++;continue; }
        return false;
    }
    return stack.is_empty();
}