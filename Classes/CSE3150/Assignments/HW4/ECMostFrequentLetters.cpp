// Given a string, find the 3 most frequent letters; if there is a tie, choose alphabetically smallest
// for example, for "I have bad dreams that have bad feelings", return "[(a, 6)(e, 5)(d, 3)]"
#include <cctype>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

void ECMostFrequentLetters( const string &Str, vector<pair<char, int>> &letters ) {
    map<char, int> freq;
    
    for (char c : Str) {
        if (isalpha(c)) {
            freq[tolower(c)]++;
        }
    }
    
    vector<pair<char, int>> freqVec(freq.begin(), freq.end());
    
    auto compare = [](const pair<char, int> &a, const pair<char, int> &b) {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        return a.first < b.first;
    };
    
    sort(freqVec.begin(), freqVec.end(), compare);
    
    letters.assign(freqVec.begin(), freqVec.begin() + min(3, (int)freqVec.size()));
}