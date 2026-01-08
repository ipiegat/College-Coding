#include <iostream>

void ECSumArray(const int *listNums, int size)
{
  // You need to loop through the array using pointer. How to define this pointer?
  const int* ptr = listNums;
  int sum = 0;

  for (int i = 0; i < size; i++) {
    sum += ptr[i];
  }
  std::cout << sum << std::endl;
  
}

int main()
{
  int array[] = {1,2,3,5};
  ECSumArray(array, 4);
  return 0;
}
