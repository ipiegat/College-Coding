#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Integers a and b are provided.
int multiply(int a, int b) {

    int res = 0;

    while (b > 0){
        if (b % 2 == 1) {
            res += a;
        a = a << 1;
        b = b >> 1;
        }
    }
    return res;


}

int main() {
    int b = rand();
    multiply(60, b);
}