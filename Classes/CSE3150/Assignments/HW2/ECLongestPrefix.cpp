// Find the longest common prefix string amongst the list of strings and return the string
// If there is no common prefix return an empty string ""

#include <vector>
#include <string>
using namespace std;

std::string ECLongestPrefix(const std::vector<std::string> &words) 
{
  // Implement the ECContainsPermutation function here...
  
  string prefix = words[0];
  
  for (int i = 0; i < prefix.length(); i++) {
    char currentChar = prefix[i];

    for(const auto& word : words) {
      if (i >= word.length() || word[i] != currentChar) {
        return prefix.substr(0, i);
      }
    }
  }
  
  return prefix;
}
