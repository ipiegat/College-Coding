// Enumerate all subsets of a vector of characters which may contain duplicates
// First, a function for counting the number of subsets
// return the number of subsets (without duplicates) of the vector of chars
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// (1): counting the number of subsets
int ECSubsetEnumCount( const vector<char> &vecChars ) {
  // return the number of subsets (without duplicates) of the vector of chars
  // for example, for [a, b, b], return 6: (), (a), (b), (a,b), (b,b), (a,b,b) 
  // Approach: first store in a map to count the number of occurance of each char
  // The number of subsets is equal to the product of (1+occur number of each char)
  map<char, int> freq;
  for (char c : vecChars) {
      freq[c]++;
  }
  int count = 1;
  for (auto &pair : freq) {
      count *= (pair.second + 1);
  }
  return count;
}

// (2): enumerating the subsets, and store the found subsets in setSubsets
// Note: the found subsets can be of any order (but cannot contain duplicates)
// Also note: you should try to make your code as efficient as you can (avoid excessive data copying)
void ECSubsetEnum( const vector<char> &vecChars, vector<vector<char> > &listSubsets ) {
  map<char, int> freq;
  for (char c : vecChars) {
      freq[c]++;
  }
  
  vector<vector<char>> subsets = { {}}; 
  for (auto &[ch, count] : freq) {
      int size = subsets.size();
      for (int i = 0; i < size; ++i) {
          vector<char> base = subsets[i];
          for (int j = 0; j < count; ++j) {
              base.push_back(ch);
              subsets.push_back(base);
          }
      }
  }
  listSubsets = subsets;
}
