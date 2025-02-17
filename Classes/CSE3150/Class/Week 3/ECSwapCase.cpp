// Starter code
#include <string>
#include <iostream>

std::string ECSwapCase(std::string str)
{
  // your code here...
  std::string res;
  int len = str.length();

  for (int i = 0; i < len; i++) {
    if (str[i] >= 'A' & str[i] <= 'Z') { // capital letter
      res += char(int(str[i]) + 32);
    }

    else if (str[i] >= 'a' & str[i] <= 'z') {
      res += char(int(str[i]) - 32);
    }

  }
  
  return res;

}

