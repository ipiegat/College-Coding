"Question 1"

for (i = 0; i < 100; i += 4)
    B[i] = A[i] + 4;
    B[i+1] = A[i+1] + 4;
    B[i+2] = A[i+2] + 4;
    B[i+3] = A[i+3] + 4;

main:
    addi s4, x0, 100
    addi s1, x0, 0
    beq x0, x0, test # we know s1 < s4

loop:
    slli t0, s1, 2 # t0 = i * 4

    # B[i] = A[i] + 4;
    add t2, t0, s2 # compute addr of A[i]
    lw t1, 0(t2)
    addi t1, t1, 4 # add 4
    add t3, t0, s3 # compute addr of B[i]
    sw t1, 0(t3)

    # B[i+1] = A[i+1] + 4
    lw t4, 4(t2) # addr of A[i+1]
    addi t4, t4, 4 # add 4
    sw t4, 4(t3) # addr of B[i+1]

    # B[i+2] = A[i+2] + 4
    lw t5, 8(t2) # addr of A[i+2]
    addi t5, t5, 4 # add 4
    sw t5, 8(t3) # addr of B[i+2]

    # B[i+3] = A[i+3] + 4
    lw t6, 12(t2) # addr of A[i+3]
    addi t6, t6, 4 # add 4
    sw t6, 12(t3) # addr of B[i+3]

    # increment i
    addi s1, s1, 4

test: 
    bne s1, s4, loop 

"Question 2"

for (i = 0; i < 16; i++)
    for (j = 0; j < 8; j++)
        T[i][j] = 256 * i + j;

# T[0][0] at address 1000
# T[0][7] at address 1000 + 7(4) = 1028
# T[1][0] at address 1000 + 8(4) = 1032
# T[16][7] at address 1000 + 23(4) = 1092

main:
    addi s0, x0, 0     # i = 0
    addi s2, x0, 16    # i limit
    addi s3, x0, 8     # j limit

i_loop:
    bge s0, s2, exit   # if i >= 16, exit loop
    addi s1, x0, 0     # j = 0

j_loop:
    bge s1, s3, j_end   # if j >= 8, end j loop

    # Calculate the value 256 * i + j
    slli t0, s0, 8     # t0 = i * 256
    add t5, t0, s1     # t5 = 256 * i + j

    # Calculate address offset for T[i][j] assuming T's base address is in s9
    slli t1, s0, 5     # t1 = i * 32 (assuming 4 bytes per int and 8 ints per row)
    slli t2, s1, 2     # t2 = j * 4
    add t3, t1, t2     # t3 = offset for T[i][j]
    add t4, s9, t3     # t4 = address of T[i][j]

    # Store the calculated value into T[i][j]
    sw t5, 0(t4)       # Store value in T[i][j]

    addi s1, s1, 1     # increment j
    beq x0, x0, j_loop # Repeat j loop

j_end:
    addi s0, s0, 1     # i++
    beq x0, x0, i_loop # Repeat i loop

exit:
    # exit

"Question 3"

# Addition of decimal strings

# strings are stored in global data section 
        .data   
dst:    .space  128
str1:   .space  128
str2:   .space  128

# instructions are in text section
        .text
main: 
        # load adresses of strings into s1, s2, and s3
        # s3 is dst, where we store the result 

        lui     s3, 0x10010 
        addi    s1, s3, 128
        addi    s2, s1, 128

        # read the first number as a string
        addi    a0, s1, 0
        addi    a1, x0, 100
        addi    a7, x0, 8
        ecall

        # read the second number as a string
        addi    a0, s2, 0
        addi    a1, x0, 100
        addi    a7, x0, 8
        ecall

        # useful constants
        addi    a4, x0, '0'
        addi    a5, x0, 10

        #TODO
        # write a loop to find out the number of decimal digits in str1
        # the loop searches for the first character that is less than '0'
        
        # Note that we assume str1, str2, and dst have the same number of 
        # decimal digits. 

        # We then write a loop to add str1 and str2, and save the result in 
        # dst. 
        # Remember that dst should have a terminating NULL.

        # find the length


        # end of the loop
        # print the result
        
        addi 	s4, x0, 0 # s4 = i or counter
        addi 	s5, x0, 0 # s5 = carry
        
n_loop:
        add     t0, s1, s4 # Calculate address of the current character in str1
        lb      t1, 0(t0) # Load the byte (character) at the calculated address
        
        blt     t1, a4, add_loop # If character is less than '0', exit loop
        
        addi    s4, s4, 1 # Increment counter
        beq 	x0, x0, n_loop # Jump back to the start of the loop

add_loop:
        addi 	s4, s4, -1 # decrement i by one, counting in reverse
        add 	t0, s1, s4 # address of current character in s1
        add 	t1, s2, s4 # address of current character in s2
        
        lb 	t2, 0(t0) # t2 = s1 character at i
        lb 	t3, 0(t1) # t3 = s2 character at i
        
        addi	t2, t2, -48 # convert s1 ASCII value to number
        addi	t3, t3, -48 # convert s2 ASCII value to number
        
        add 	t4, t2, t3 # t4 = t2 + t3
        add 	t4, t4, s5 # add previous carry
        
        blt 	t4, a5, NoCarry # if t4 < 10, no carry
        
        addi 	t4, t4, -10 # subtract 10 for carry
        addi 	s5, x0, 1 # set carry to one
        beq 	x0, x0, StoreDigits # store digit

NoCarry:
	    addi 	s5, x0, 0 # set carry to 0 if there's none	

StoreDigits:
        add 	t4, t4, a4 # convert to ASCII
        
        add 	t0, s3, s4 # calc result store address
        sb 	t4, 0(t0) # store result
        
        bge 	s4, x0, add_loop # loop until i = 0 
	
print:
        addi    a0, s3, 0
        addi    a7, x0, 4
        ecall

        # exit
        addi    a7, x0, 10
        ecall

"Question 4"

or s1, s2, s3
or x9, x18, x19

R-type as there are three registers
funct7 | rs2 | rs1 | funct3 | rd | opcode

0000000 10011 10010 110 01001 0110011
0000 0001 0011 1001 0110 0100 1011 0011
0x013968B3 # answer

slli t1, t2, 16
slli x6, x7, 16

I-type as there is rd, rs1, immediate
imm[11:0] | rs1 | funct3 | rd | opcode 

000000001000 00111 001 00110 0010011
0000 0000 1000 0011 1001 0011 0001 0011
0x00839313 # answer

xori x1, x1, -1

I-type as there is rd, rs1, immediate
imm[11:0] | rs1 | funct3 | rd | opcode

111111111111 00001 100 00001 0010011
1111 1111 1111 0000 1100 0000 1001 0011
0xFFF0C093 # answer

lw x2, -100(x3)

I-type as the offset takes up the immediate bits
imm[11:0] | rs1 | funct3 | rd | opcode

000001100100 # take twos complement

111110011100 00011 010 00010 0000011
1111 1001 1100 0001 1010 0001 0000 0011
0xF9C1A1903 # answer

"Question 5"

A: 0xFEACA823
1111 1110 1010 1100 1010 1000 0010 0011
1111111 01010 11001 010 10000 0100011

Opcode = 0100011 # indicates store word instruction, s type
rs2 = 01010 # x10
funct3 = 010
rs1 = 11001
imm = 1111 1111 0000 -> 0000 0000 1111 + 1 -> 0000 0001 0000 = 16

sw x10, -16(x25)

B: 0x04020713
0000 0100 0000 0010 0000 0111 0001 0011

opcode = 0010011 # i type instruction
000001000000 00100 000 01110 0010011

rs1 = 00100 # x4
funct3 = 000
rd = 01110 # x14
imm = 000001000000

addi x14, x4, 64

C: 0x00557bb3
0000 0000 0101 0101 0111 1011 1011 0011

opcode = 0110011 # r type instruction
0000000 00101 01010 111 10111 0110011

funct3 = 111 # indicates and instruction
rs2 = 00101 # x5
rs1 = 01010 # x10
imm = 0
rd = 10111 # x23

add x23, x10, x5

D: 0x414FDF13

0100 0001 0100 1111 1101 1111 0001 0011

opcode = 0010011 # i type instruction
010000010100 11111 101 11110 0010011

imm = 010000010100 
rs2 = 11111 # x31
rs1 = 11110 # x30
funct3 = 101 # srai instruction

srai x30, x31, 20