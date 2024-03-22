"Question 1a"

0x45652000

0 10001010 11001010010000000000000 
sign - 0
exponent - 10001010 = 138 - 127 = 11
significand - 11001010010000000000000

1.11001010010000000000000

1 + 1/2 + 1/4 + 1/32 + 1/128 = 1.789

1.789 * 2^(11) = 3664.0 # answer

"Question 1b"

0x00070000

0 00000000 00001110000000000000000

sign - 0
exponent - 00000000 = 0 - 127 = -127
significand - 00001110000000000000000

0.00001110000000000000000

0 + 1/32 + 1/64 + 1/128 = 0.0546875

0.0546875 * 2(^-127) # answer

"Question 2a"

-15.82 * 2^(-10)

-1111.1101 # shift left by 3, rememeber to add 3 to exponennt
-1.1111101

sign - 1
exponent - (117+3) - 127 = -10 
120 = 01111000

significand = 11111010000000000000000

1 01111000 11111010000000000000000

1011 1100 0111 1101 0000 0000 0000 0000

0xBC7D1EB8 # answer

"Question 2b"

-831.9

-110011111.11100 # shift left 8, add 8 to exponent
-1.11001111111100 * 2^(8)

sign - 1
exponent - (0+8) - 127 = -119
8 = 00001000

significand = 11001111111100000000000

1 00001000 11001111111100000000000

1000 0100 0110 0111 1111 1000 0000 0000

0x8467F800

"Question 3"

exponent - 11111111 = 254 - 127 = 127

2^(127)

2^23 # largest num allowed in IEEE 754
2^24 # implicit leading 1
2^24 - 1 = 16777215 # ensure it is odd

0100 1011 0111 1111 1111 1111 1111 1111

0x4B7FFFFF

"Question 4"

float dot_product(float x[], float y[], int n)
{
    float sum = 0.0;

    for (int i = 0; i < n; i += 1)
        sum += x[i] * y[i];
    return sum;
}

dot_product:
    addi sp, sp, -16

    sw ra, 12(sp)
    sw s2, 8(sp)
    sw s1, 4(sp)
    sw s0, 0(sp)

    addi s0, a2, 0 # int n
    addi s1, a0, 0 # address of x[]
    addi s2, a1, 0 # address of y[]
    addi s3, t0, 0 # i

    fmv.w.x f8, 0 # float sum
    

loop:
    bge s3, s0, exit

    slli t0, s1, 2 # offset for x
    slli t1, s2, 2 # offset for y 

    flw f0, t0 # t1 = x[i]
    flw f1, t1 # t2 = y[i]

    fmul.s f2, f0, f1 # x[i] * y[i]
    fadd.s f8, f8, f2 # add to sum

    addi s3, s3, 1 # increment i

    beq x0, x0, loop

exit:
    fmv.s f10, f8 # move sum to return value register
    
    lw ra, 16(sp)
    lw s2, 8(sp)
    lw s1, 4(sp)
    lw s0, 0(sp)
    addi sp, sp, 16

    jalr x0, 0(ra)









