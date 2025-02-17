//
#include <iostream>
using namespace std;

int main()
{
  // allocate an array of char in heap 
  char *px = new char[10];
  int ascii = 97;
  // set this array to 'a', 'b' and so on
  // your code here...

  // iterating
  for (int i = 0; i < 10; i++) {
    px[i] = char(ascii);
    ascii++;
  }
  
  //using pointers
  int ascii = 97;
  char *ptr = px; // point to beginning of array
  for (int i = 0; i < 10; i++) {
    *ptr = ascii;
    ascii ++;
    ptr++;
  }

  ptr = px; // reset pointer to start
  // print out
  for(int i=0; i<10; ++i)
  {
    cout << *(px+i);
  }
  cout << endl;

  delete [] px;

  return 0;
}
 
