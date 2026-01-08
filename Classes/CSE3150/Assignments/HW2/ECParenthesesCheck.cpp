// Check if the string contains valid parentheses
// The string may include '(', ')', '[', ']' and other characters
// These parentheses must be properly matched e.g. (), [()], [([])]

#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

bool ECParenthesesCheck(const std::string& strInput) {
    std::stack<char> stack;
    std::unordered_map<char, char> closingToOpening = {
        {')', '('},
        {']', '['}
    };

    for (char ch : strInput) {
        if (ch == '(' || ch == '[') {
            stack.push(ch);
        }
        else if (ch == ')' || ch == ']') {
            if (stack.empty() || stack.top() != closingToOpening[ch]) {
                return false;
            }
            stack.pop();
        }
    }
    
    return stack.empty();
}
