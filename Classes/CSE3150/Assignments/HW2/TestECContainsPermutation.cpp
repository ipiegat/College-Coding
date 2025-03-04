#include <iostream>
using namespace std;

bool ECContainsPermutation(const std::string& s1, const std::string& s2);

int main() 
{
    cout << boolalpha; // Print "true"/"false" instead of 1/0
    cout << "Test 1: " << ECContainsPermutation("cse3150", "xyz1053ecsabc") << endl; // true
    cout << "Test 2: " << ECContainsPermutation("cse3150", "xyz1503hescabc") << endl; // false
    cout << "Test 3: " << ECContainsPermutation("abc", "miuoniynbcaefg") << endl; // true
    cout << "Test 4: " << ECContainsPermutation("xyz", "zyxabcdef") << endl; // true
    cout << "Test 5: " << ECContainsPermutation("abcd", "aabbcdd") << endl; // false
    cout << "Test 6: " << ECContainsPermutation("abcd", "efghijkl") << endl; // false
    return 0;
}