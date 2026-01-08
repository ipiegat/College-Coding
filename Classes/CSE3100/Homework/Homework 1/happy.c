#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n;
  printf("n = ");
  scanf("%d", &n);

  int original_n = n;
  int sum = 0;

  //printf("%d", n);
  while (n != 4 && n != 1) {
    sum = 0;
    while (n != 0) {
      int digit = n % 10;
      // printf("Taking digit %d\n", digit);
      sum += digit * digit;
      // printf("Sum is now %d\n", sum);
      n /= 10;
      // printf("Rightshifting n to %d\n", n);
    }
    n = sum;
    printf("%d\n", n);
  }
  //printf("\n");

  if (n == 1) {
    printf("%d is a happy number.\n", original_n);
  } else {
    printf("%d is NOT a happy number.\n", original_n);
  }

  return 0;
}