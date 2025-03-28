#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

// we want to define two functions ECSetIntersection and ECIntersection that find the overlap between two generic containers
// ECSetIntersection does NOT include duplicates. You are free to use functions from the set library as necessary
// ECIntersection DOES include duplicates. For example the ECIntersection between "aaabc" and "aabb" will be "aab".


using namespace std;

template <typename container>
container ECSetIntersection(const container &c1, const container &c2) {
    // TO DO: find the set intersection of the two containers.
    // ie, no duplicates allowed in the result
    set<typename container::value_type> set1(c1.begin(), c1.end());
    set<typename container::value_type> set2(c2.begin(), c2.end());

    container result;
    for (const auto &item : set1) {
        if (set2.find(item) != set2.end()) {
            result.insert(result.end(), item);
        }
    }
    return result; 
}



template <typename container>
container ECIntersection(const container &c1, const container &c2) {
    // TO DO: find the general intersection of the two containers
    // For this version duplicates are preserved such that if 'e' appears 2 time in EACH container
    // it will appear twice in the result, if it appears 3 times in EACH, then it will appear
    // thrice in the result
    // Use a brute-force algrothim in O(n^2)
    container result;
    vector<bool> used(c2.size(), false);

    for (auto it1 = c1.begin(); it1 != c1.end(); ++it1) {
        auto it2 = c2.begin();
        for (size_t i = 0; it2 != c2.end(); ++it2, ++i) {
            if (!used[i] && *it1 == *it2) {
                result.insert(result.end(), *it1);
                used[i] = true;
                break;
            }
        }
    }
    return result;

}