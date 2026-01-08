#include <string>
#include <iostream>
#include <vector>
using namespace std;

bool ECParenthesesCheck(const std::string& strInput);

int main()
{
    vector<string> testCases;

    //************VALID************//
    testCases.push_back("()"); // Simple valid case
    testCases.push_back("[[]]"); // Simple valid brackets
    testCases.push_back("[[[][]]]"); // Nested valid brackets
    testCases.push_back("([()[]])"); // Mixed valid nesting
    testCases.push_back("a(b)c"); // Valid with letters

    //************INVALID************//
    testCases.push_back("[(])"); // Incorrectly nested
    testCases.push_back("([)]"); // Incorrect nesting
    testCases.push_back("[1+2*(3/4)"); // Missing closing bracket
    testCases.push_back("abc(def]"); // Mismatched parentheses and brackets

    for (const auto &test : testCases) {
        cout << "Input: \"" << test << "\" -> Output: " 
             << (ECParenthesesCheck(test) ? "Valid" : "Invalid") << endl;
    }

    return 0;
}