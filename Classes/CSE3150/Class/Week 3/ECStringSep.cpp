// Starter code
#include <iostream>
#include <cstring>

using namespace std;

string ECStringSep(const string &str)
{
  string res;

  // your code goes here
  int len = str.length();

  if(str.empty()) {
    return "";
  }
  
  for (int i = 0; i < len; i++) {
    res += str[i];
    if (i < len - 1) {
      res += ",";
    }
  }
  
  return res;
}

