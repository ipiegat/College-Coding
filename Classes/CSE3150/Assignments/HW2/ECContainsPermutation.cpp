//Checks whether string s2 contains any permutation of string s1 
//Otherwise return false

#include <string>
#include <vector>
using namespace std;

bool ECContainsPermutation(const std::string& s1, const std::string& s2)
{
    if (s1.size() > s2.size())
        return false;
    
    const int CHAR_COUNT = 128;
    vector<int> freqS1(CHAR_COUNT, 0);
    vector<int> freqWindow(CHAR_COUNT, 0);
    
    int m = s1.size();
    int n = s2.size();
    
    for (int i = 0; i < m; i++) {
        freqS1[s1[i]]++;
        freqWindow[s2[i]]++;
    }
    
    if (freqS1 == freqWindow)
        return true;
    
    for (int i = m; i < n; i++) {
        freqWindow[s2[i - m]]--;
        freqWindow[s2[i]]++;
        
        if (freqS1 == freqWindow)
            return true;
    }
    
    return false;
}
