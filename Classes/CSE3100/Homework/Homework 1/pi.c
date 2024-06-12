#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n;

  printf("n = ");
  scanf("%d", &n);

  if (n <= 0) {
    return 1;
  }

  double pi = 0.0;
  double temp = 1.0;
  double i;
  
  for (i = 0.0; i <= n; i++) {
    
    pi += (4.0 / (8.0 * i + 1.0) - 2.0 / (8.0 * i + 4.0) -
           1.0 / (8.0 * i + 5.0) - 1.0 / (8.0 * i + 6.0)) *
          (1.0 / temp);

    temp *= 16;
  }

  printf("PI = %.10f\n", pi);
  return 0;
}