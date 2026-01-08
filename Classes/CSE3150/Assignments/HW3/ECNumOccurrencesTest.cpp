#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
using namespace std::chrono;

#include "ECNumOccurrences.h"

template<class T>
void ASSERT_EQ(T x, T y)
{
  if( x == y )
  {
    cout << "Test passed: equal: " << x << " --- " << y << endl;
  }
  else
  {
    cout << "Test FAILED: equal: " << x << " --- " << y << endl;
  }
}

int main()
{
  vector<int> arrayA = {1, 3};

  // Populate arrayB
  vector<int> arrayB;

  mt19937 rng(1);
  uniform_int_distribution<int> dis(0, 100);

  for(int i = 0; i < 1000000; i++){
    arrayB.push_back(dis(rng));
  }
  std::sort(arrayB.begin(), arrayB.end());
  
  // Time and run foreign function
  auto start = high_resolution_clock::now();
  vector<int> arrayC = ECNumOccurrences(arrayA, arrayB);
  auto end = high_resolution_clock::now();

  auto duration1 = chrono::duration<double, milli>(end-start);

  // Time and run domestic function
  start = high_resolution_clock::now();
  vector<int> correctC(arrayA.size());
  for(int i = 0; i < arrayA.size(); i++){
    correctC[i] = count(arrayB.begin(), arrayB.end(), arrayA[i]);
  }
  end = high_resolution_clock::now();

  auto duration2 = chrono::duration<double, milli>(end-start);

  // Validate results
  if((duration1.count() * 2) > duration2.count()){
    cout << "Test FAILED: timeout exceeded (" << duration1.count() << " ms vs. "
      << duration2.count() << " ms)" << endl;
    return 1;
  }
  else{
    cout << "Test passed: timeout passed (" << duration1.count() << " ms)" << endl;
  }

  for(int x = 0; x < arrayC.size(); x++){
    ASSERT_EQ(arrayC[x], correctC[x]);
  }
}

