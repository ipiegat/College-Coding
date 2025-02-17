// Starter code
#include <string>
#include <iostream>


extern std::string ECSwapCase(std::string str);

int main()
{
  std::string str1("Abcd");
  std::cout << ECSwapCase(str1) << std::endl;
  std::string str2("Cse 3150");
  std::cout << ECSwapCase(str2) << std::endl;
  return 0;
}

