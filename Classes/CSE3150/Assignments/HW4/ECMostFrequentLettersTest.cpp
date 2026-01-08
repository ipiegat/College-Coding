#include <string>
#include <vector>
#include <iostream>
using namespace std;

extern void ECMostFrequentLetters(const string &strText, vector<pair<char, int>> &letters);

bool testEqual(vector<pair<char, int>> result, vector<pair<char, int>> expected){
  if (result.size() != expected.size())
    return false;
	for (int i = 0; i < expected.size(); ++i){
		if (result[i] != expected[i]){
			return false;
		}
	}
	return true;
}

bool Test1(){
  cout << endl << "Test 1" << endl;
  string str = "I have bad dreams that have bad feelings";
  vector<pair<char, int>> result;
  ECMostFrequentLetters(str, result);
  pair<char, int> p1('a', 6), p2('e', 5), p3('d', 3);
  vector<pair<char, int>> expected = {p1, p2, p3};

  if (testEqual(result, expected)){
    cout << "TEST PASSED" << endl;
    return true;
  }
  cout << "TEST FAILED" << endl;
  return false;
}

bool Test2(){
  cout<<endl<<"Test 2"<<endl;
  string str = "how can I find the most frequent word, in an string, how?can I find how!how-string";
  vector<pair<char, int>> result;
  ECMostFrequentLetters(str, result);
  pair<char, int> p1('n', 9), p2('i', 7), p3('o', 6);
  vector<pair<char, int>> expected = {p1, p2, p3};
  if (testEqual(result, expected)){
    cout<<"TEST PASSED"<<endl;
    return true;
  }
  cout<<"TEST FAILED"<<endl;
  return false;
}

int main()
{
  Test1();
  Test2();
}
