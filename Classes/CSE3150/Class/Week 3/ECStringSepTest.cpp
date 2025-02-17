// Starter code
#include <iostream>

using namespace std;

extern string ECStringSep(const string &str);

int main()
{
  string str1 = "abc";
  cout << ECStringSep(str1) << endl;
  string str2 = "CSE3150";
  cout << ECStringSep(str2) << endl;
  string str3;
  cout << ECStringSep(str3) << endl;
  return 0;
}
