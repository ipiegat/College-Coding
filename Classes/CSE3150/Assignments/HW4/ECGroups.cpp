#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Return the number of groups, and the starting positions of a new group (Saved in positions)
int ECNumGroups( const string &str, vector<int> &positions ) {
    if (str.empty()) return 0;
    
    int groupCount = 1;
    positions.push_back(0);
    
    for (size_t i = 1; i < str.size(); ++i) {
        if (str[i] != str[i - 1]) {
            positions.push_back(i);
            groupCount++;
        }
    }
    return groupCount;
}