#include <string>
#include <iostream>
#include <vector>
using namespace std;

int ECNumGroups( const string &str, vector<int> &positions );

bool testEqual(vector<int> result, vector<int> expected){
	if (result.size() != expected.size())
    	return false;
	for (int i = 0; i < expected.size(); ++i){
		if (result[i] != expected[i])
			return false;
	}
	return true;
}

bool Test1(){
  cout<<endl<<"Test 1"<<endl;
  string str = "11344466711";
  vector<int> result;
  int runs = ECNumGroups(str, result);
  vector<int> expected = {0, 2, 3, 6, 8, 9};

  if (testEqual(result, expected) && runs == 6){
    cout<<"TEST PASSED"<<endl;
    return true;
  }
  cout<<"TEST FAILED"<<endl;
  return false;
}

bool Test2(){
  cout<<endl<<"Test 2"<<endl;
  string str = "4445583447772234567";
  vector<int> result;
  int runs = ECNumGroups(str, result);
  vector<int> expected = {0, 3, 5, 6, 7, 9, 12, 14, 15, 16, 17, 18};
  if (testEqual(result, expected) && runs == 12){
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
