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





