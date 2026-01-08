#include <iostream>
using namespace std;

// complete the definition of the sorting function ...
void ECSortFP(int *listNumbers, int size, bool(*compare)(int, int))
{
  // your code here
  for (int i = 0; i < size - 1; i++) {
    for (int j  = 0; j < size - 1 - i; j++) {
      
      int *ptr_1 = &listNumbers[j];
      int *ptr_2 = ptr_1 + 1;

      if (compare(*ptr_1, *ptr_2)) {
        int temp = *ptr_1;
        *ptr_1 = *ptr_2;
        *ptr_2 = temp;
      }
    }

  }
}

bool compare(int x, int y)
{
  if (x < y) {
    return false;
  } else {
    return true;
  }
}

int main()
{
  int arr[] = {1,3,2,4};
  ECSortFP(arr, 4, *compare);

  // print it out
  for(int i=0; i<4; ++i)
  {
    cout << arr[i] << " ";
  }
  cout << endl;
}

