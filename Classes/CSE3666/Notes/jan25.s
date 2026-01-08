"Negate 2's complement numbers

Step 1: Complement all the bits in x, i.e.e, 1->0 and 0->1
Step 2: Add  to the complemented bits

Sign Extension:

If MSB = 0 pad '0s', if MSB = 1 pad '1s'

1111 0010 -> 1111 1111 0010
0010 -> 0000 00010 

Hexidemal:

0-9, a, b, c, d, e, f
More copact for representing bits

When converting binary to hex, represent each hex digit as 4 bi5s

ECA8 -> 6420 base 16
= 1110 1100 1010 1000 0110 0100 0010 0000

1010 1001 1010 -> hex -> A9A
"

addi s1, x0, '0' # ASCII value
addi s2, x0, 48
addi s3, x0, 0x30
# s1 == s2 and s1 == s3
# lower eight bits are 0011 0000

add s4, x0, x0
# s4 != s1

"Shift bits:

Shifting left multiplies by 2 (<< n), right divides by 2 (>> n)

11110000 shift right 2

unsigned: 00111100 = 60
signed (two's complement) = 11111100 = -4

"

