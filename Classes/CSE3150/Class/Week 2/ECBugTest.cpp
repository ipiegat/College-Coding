#include <stdio.h>
#include "ECBug.cpp"
//extern int ECSillyCalc(int a);

int main()
{
  int a = 2;
  printf("a=2: %d \n", ECSillyCalc(a));
  a = 1;
  printf("a=2: %d \n", ECSillyCalc(a));
  a = -1;
  printf("a=2: %d \n", ECSillyCalc(a));
}
