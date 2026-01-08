#include <iostream>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <set>
#include <vector>
#include <list>

#include "ECMapDecryption.cpp"
#include "ECIntersection.cpp"
#include "ECAccumulate.cpp"


using namespace std;
// c++ ECMainTests.cpp  -std=c++11

int main() {

    // Tests for ECMapDecryption

    map<char, char> cipher =  ECCreateCipherMap();
    
    // Need to maintain order, so we will use sequence containers
    vector<char> v = {'U', 'w', 'd', 'd', 'g', ' ', 'J', 'g', 'j', 'd', 'v', '!'}; // Example vector input 
    string s = "V se P++ Zsf sfv V se zwjw lg ksnw lzw vsq!";  // Example string input 
    list<char> l = {'0', '.', '8', '1', '8', '2', '6', '9', '3', '2', '0', '2'};  // Example list input 
    
    // You will know when your cipher map works, because these messages will be clear!
    cout << "\nVector input: " << ECDecryptMessage(cipher, v) << endl;
    cout << "String input: " << ECDecryptMessage(cipher, s) << endl;
    cout << "List input: " << ECDecryptMessage(cipher, l) << endl;



    // Tests for ECIntersection

    cout << "\nIntersection Test 1:" << endl;
    vector<char> v1 = {'a','b','c','d'};
    vector<char> v2 = {'c','o','w'};
    vector<char> res1 = ECSetIntersection(v1, v2);
    for (auto x : res1) cout << x << " ";
    cout << endl;
    vector<char> res2 = ECIntersection(v1, v2);
    for (auto x : res2) cout << x << " ";
    cout << endl;


    cout << "\nIntersection Test 2:"  << endl;
    string str1 = "hello";
    string str2 = "I like yellow";
    string res3 = ECSetIntersection(str1, str2);
    for (auto x : res3) cout << x << " ";
    cout << endl;
    string res4 = ECIntersection(str1, str2);
    for (auto x : res4) cout << x << " ";
    cout << endl;

    
    cout << "\nIntersection Test 3:"  << endl;
    set<int> v3 = {5, 6, 8};
    set<int> v4 = {1, 2, 3, 4};
    set<int> res7 = ECSetIntersection(v3, v4);
    for (auto x : res7) cout << x << " ";
    cout << endl;
    set<int> res8 = ECIntersection(v3, v4);
    for (auto x : res8) cout << x << " ";
    cout << endl;




    // Tests for ECAccumulate

    std::vector<int> point1 = {1, 2, 3};
    std::vector<int> point2 = {4, 5, 6};
    
    // Calculate Euclidean distance between point1 and point2
    double distance = ECEuclideanDistance(point1, point2);
    
    std::cout << "Euclidean Distance: " << distance << std::endl;  // Should output 5.19615 (sqrt(27))


    std::vector<int> vector1 = {2, 3, 4};
    std::vector<int> vector2 = {1, 2, 5};

    double result = ECDotProduct(vector1, vector2);
    
    std::cout << "Dot Product: " << result << std::endl;  // Should output 28

    //note we will test your implementation of ECAccumulate with different elementwise and accumulation functions
}