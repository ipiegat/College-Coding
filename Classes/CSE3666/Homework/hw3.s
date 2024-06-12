"Question 1"

/ prototype of bar
// the first argument is an address of an integer
int bar(int a[], int i);
{
    # assume implementation
}
int foo(int d[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i += 1) {
        int t = bar(&d[i], n - i); // &d[i] means d[i]’s address
        if (t > 0)
            count += 1;
    }
    
    return count;
}

main:
    # assume working functionality

foo:
    # stack allocation 
    addi sp, -16
    sw s0, 0(sp) # assume address stored here
    sw s1, 4(sp) # count
    sw s2, 8(sp) # i 
    sw s3, 12(sp) # n

    addi s1, x0, 0 
    addi s2, x0, 0
    addi s3, x0, 10 # 10 represents n

    # beginning of loop
    loop: 
        bge s2, s3, exit # if i >= n, exit

        slli t0, s2, 2 # i offset
        
        add a0, t0, s0 # add offset and save &d[i] in a0
        sub a1, s3, s2 # save n - i in a1

        jal ra, bar # stores return value in a0

        addi t1, x0, 1
        blt a0, t1, skip_increment # skip count if t < 1
        addi s1, s1, 1 # else, increment count

        skip_increment:
            addi s2, s2, 1 # increment i
            beq x0, x0, loop

    # set a0 to count
    add a0, s1, x0 
    
    # stack allocation
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    addi sp, 16

    # return 
    jalr x0, ra, 0

exit:
    # assume functionality

"Question 2"

void merge(intc[], int d1[], int n1, int d2[], int n2);
void copy(int d[], int c[], int n);

void msort(int d[], int n)
{
    int c[256];
    if (n <= 1)
        return;
    
    int n1 = n/2;

    msort(d, n1);
    msort(&d[n1], n - n1);
    merge(c, d, n1, &d[n1], n - n1);
    copy(d, c, n);
}

main:
    # assume functionality

msort:
    # stack allocation
    addi sp, -1036 # c[256] = 1024 bytes
    sw s0, 1024(sp) # address of c[]
    sw s1, 1028(sp) # address of d[]
    sw s2, 1032(sp) # n

    addi t0, x0, 2 # t0 = 2
    blt s2, t0, function_return

    # msort(d, n1);
    srli t1, s2, 1 # t1 = n / 2 = n1

    addi a0, s1, 0 # a0 = address of d[]
    addi a1, t1, 0 # a1 = n1
    
    jal ra, msort

    # msort(&d[n1], n - n1);
    slli t2, t1, 2 # n1*4 = offset
    add t3, s1, t2 # add offset, t3 = &d[n1]
    sub t4, s2, t1 # t4 = n - n1

    add a0, t3, x0 # a0 = t3
    sub a1, t4, x0 # a1 = t4

    jal ra, msort

    # merge(c, d, n1, &d[n1], n - n1);
    add a0, s0, x0 # a0 = c
    add a1, s1, x0 # a1 = d
    add a2, t1, x0 # a2 = n1
    add a3, t3, x0 # a3 = &d[n1]
    add a4, t4, x0 # a4 = n - n1

    jal ra, merge

    # copy(d, c, n);
    add a0, s1, x0 # a0 = d
    add a1, s0, x0 # a1 = c
    add a2, s2, x0 # a2 = n

    jal ra, copy

    # stack allocation 
    lw s0, 1024(sp) # address of c[]
    lw s1, 1028(sp) # address of d[]
    lw s2, 1032(sp) # n
    addi sp, 1036

    function_return:
        jalr x0, ra, 0


"Question 3"

I10 : BGE x10, x20, I100

rs1 : 01010
rs2 : 10010
funct3 : 101
opcode : 1100011

imm[12|10:5] 10100 01010 101 imm[4:1|11] 1100011

I100 - I10 = (100 - 10) * 4 = 360
0000101101000

0001011 10100 01010 101 01000 1100011
0001 0111 0100 0101 0101 0100 0110 0011

0x17455463 # answer

I11 : BEQ x10, x0, I1

rs1 : 01010
rs2 : 00000
funct3 : 000
opcode : 1100011

imm[12|10:5] 00000 01010 000 imm[4:1|11] 1100011

I1 - I11 = (1-11)*4 = -40
000000101000 -> 111111010111 + 1 = 111111011000

1111101 00000 01010 000 11001 1100011
1111 1101 0000 0101 0000 1100 1110 0011

0xFC050CE3 # answer

I140 : JAL x0, I100

rd : 00000
opcode : 1101111

imm[20|10:1|11|19:12] 00000 1101111

I100 - I140 = (100-140)*4 = -160
00000000000010100000 -> 11111111111101011111 + 1
11111111111101100000

1 1110110000 1 11111111 00000 1101111
1111 0110 0001 1111 1111 0000 0110 1111

0xF61FF06F # answer

"Question 4"

0x0400366C : 0xDB5A04E3

instructions address -> 0000 0100 0000 0000 0011 0110 0110 1100 
instruction -> 1101 1011 0101 1010 0000 0100 1110 0011

opcode : 1100011 # branch instruction, SB-type
imm : 111001011000 -> 0001101010 = 600 thus -600

 0x0400366C
-0x00000258
 0x04003414

0x04208888 : 0xFA9FF0EF

instructions address -> 0000 0100 0010 0000 1000 1000 1000 1000
instruction -> 1111 1010 1001 1111 1111 0000 1110 1111

opcode : 1101111
imm : 0101 1000 -> 10101000 = 88 thus -88

 0x04208888
-0x00000058
 0x04208830