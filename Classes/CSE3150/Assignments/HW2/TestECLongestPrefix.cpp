#include <iostream>
#include <string>
#include <vector>
using namespace std;

//To remind you to run use ./ECLongestPrefix once it has compiled

string ECLongestPrefix(const vector<string> &words);

int main()
{
    std::vector<std::string> words1;
    words1.push_back("green");
    words1.push_back("great");
    words1.push_back("greetings");
    words1.push_back("grebe");
    words1.push_back("greek");
    words1.push_back("greed");

    std::vector<std::string> words2;
    words2.push_back("apple");
    words2.push_back("apple");
    words2.push_back("banana");
    words2.push_back("orange");
    words2.push_back("watermelon");
    
    std::vector<std::string> words3; 
    words3.push_back("abcdefghijabcdefghijabcdefghij");
    words3.push_back("abcdefghijabcdefghijabcdefgxyz");
    words3.push_back("abcdefghijabcdefghijabcdef");
    words3.push_back("abcdefghijabcdefghijabc");
    words3.push_back("abcdefghijabcdefghijabccniewaosd");

    std::vector<std::string> words4;
    words4.push_back("a"); 
    words4.push_back("able"); 
    words4.push_back("app");
    words4.push_back("aim");
    words4.push_back("ape"); 
    words4.push_back("apple");
    words4.push_back("applications");
    words4.push_back("arm");
    words4.push_back("ate");
    words4.push_back("army");
    words4.push_back("arggg!");

    cout << "Longest Common Prefix (Test 1): " << ECLongestPrefix(words1) << endl;
    cout << "Longest Common Prefix (Test 2): " << ECLongestPrefix(words2) << endl;
    cout << "Longest Common Prefix (Test 3): " << ECLongestPrefix(words3) << endl;
    cout << "Longest Common Prefix (Test 4): " << ECLongestPrefix(words4) << endl;
    
    return 0;
}