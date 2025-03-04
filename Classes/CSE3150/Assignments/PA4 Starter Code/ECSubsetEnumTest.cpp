#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

extern int ECSubsetEnumCount(const vector<char> &vecChars);
extern void ECSubsetEnum(const vector<char> &vecChars, vector<vector<char> > &listSubsets);

bool testEqual(vector<vector<char>> result, vector<vector<char>> expected){
  if (result.size() != expected.size())
    return false;
	for (int i = 0; i < expected.size(); ++i){
		if (result[i] != expected[i])
			return false;
	}
	return true;
}

bool Test1()
{
  cout<<endl<<"Test 1"<<endl;
  vector<char> vec1 = {'a', 'b', 'b'};

  vector<vector<char> > listSubsets;
  ECSubsetEnum(vec1, listSubsets);
  // sort the subsets
  sort( listSubsets.begin(), listSubsets.end() );
  vector<char> vecs0, vecs1 = {'a'}, vecs2 = {'a', 'b'}, vecs3 = {'a', 'b', 'b'}, vecs4 = {'b'} , vecs5 = {'b', 'b'};
  vector<vector<char>> expected = {vecs0, vecs1, vecs2, vecs3, vecs4, vecs5};
  if (testEqual(listSubsets, expected) && ECSubsetEnumCount(vec1) == listSubsets.size())
  {
    cout<<"TEST PASSED"<<endl;
    return true;
  }
  cout<<"TEST FAILED"<<endl;
  return false;
}

bool Test2()
{
  cout<<endl<<"Test 2"<<endl;
  vector<char> vec1 = {'a', 'b', 'c'};

  vector<vector<char> > listSubsets;
  ECSubsetEnum(vec1, listSubsets);
  // sort the subsets
  sort( listSubsets.begin(), listSubsets.end() );
  vector<char> vecs0, vecs1 = {'a'}, vecs2 = {'a', 'b'}, vecs3 = {'a', 'b', 'c'}, vecs4 = {'a', 'c'} , vecs5 = {'b'}, vecs6 = {'b', 'c'}, vecs7 = {'c'};
  vector<vector<char>> expected = {vecs0, vecs1, vecs2, vecs3, vecs4, vecs5, vecs6, vecs7};
  if (testEqual(listSubsets, expected) && ECSubsetEnumCount(vec1) == listSubsets.size())
  {
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
