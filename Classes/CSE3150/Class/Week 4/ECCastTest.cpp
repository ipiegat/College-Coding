#include <iostream>
using namespace std;

// function takes a const int pointer and then modify it
void foo(const int *px)
{
  // cast to non-const and then modify the int pointed by it
  *pcx = 1;
}

// do the following casting work?
int main()
{
  // cast an int to char
  char ch1 = 'a';	// no cast
  int x1 = ch1;
  cout << "x1 = " << x1 << ", ch1 = " << ch1 << endl;
  
  // cast a pointer to an int to a ponter to a double
  int y1 = 10;
  double *py1 = (double *)(&y1);
  cout << "*py1: " << *py1 << endl;

  // cast a pointer to char to a pointer to int
  char ch = 'a';
  int *pch = (int *)(&ch);
  cout << "*pch: " << *pch << endl; 

  // cast a void pointer to point to int
  int x4 = 20;
  void *px4 = &x4;
  int *px4i = ???;
  cout << "*px4i: " << *px4i << endl;

  // const_cast
  // cast a const int pointer to a non-const pointer to int and then modify it
  const int x5 = 0;
  int *px5 = ????;
  *px5 = 1;
  cout << "x5: " << x5 << ", *px5: " << *px5 << endl;

  // const_cast and function call
  const int x6 = 0;
  foo(&x6);
  cout << "x6: " << x6 << endl;

  return 0;
}
