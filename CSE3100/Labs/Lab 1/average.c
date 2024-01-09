#include <stdio.h>
#include <stdlib.h>

int main() {

double total = 0.0;
double average = 0.0;
double x;
int counter = 0;

while (scanf("%lf", &x) == 1) { // pay attention to %lf
    counter += 1;
    total += x;
    average = total / counter;
    printf("Total=%f Average=%f\n", total, average); // pay attention to %f
    }

    return 0;
    
}
