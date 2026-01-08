"Questions 1"




"Question 2: Write RISC-V instructions to reverse the order of bytes in register s2 
and save the results ins4. For example, if s2 is 0x12345678, the four bytes in s2 
are 0x12, 0x34, 0x56, and 0x78.Register s4 should be 0x78563412 after the execution 
of the instruction sequence. Usetemporary registers like t0 and t1 to save 
intermediate values."

#       CSE 3666 Homework

        .globl  main

        .text
main:   
        # use system call 5 to read integer
        addi    a7, x0, 5
        ecall
        addi    s1, a0, 0       # copy to s1
        
        # print int hex = 34, print acii = 11
        #   reverse bits in s2 and save the results in s4
        #   print s2 in hex, with a system call
        #   print newline
        #   print s4 in hex, with a system call
        
        addi t0, s1, 0 # set t0 = s1
        addi s2, x0, 0  # set s2 = 0
        addi s3, x0, 32 # set s3 = 32
        
 Loop:
	beq s3, x0, L1
	# isolate LSB of s1 and add it to s2
	slli s2, s2, 1 # shift s2 left 
	andi t1, t0, 1 #  t1 = t0 and 1
	or s2, s2, t1 # add isolate bit to s2
	
	# prepare for next bit
	srli t0, t0, 1 # shift 1 right to get next bit
	addi s3, s3, -1 # decrement counter
	beq x0, x0, Loop # loop

L1: 
	# print s1 in hex, with a system call
	add a0, s1, x0
	addi a7, x0, 34
	ecall
	
	# newline
	addi a0, x0, 10
	addi a7, x0, 11
	ecall
	
	# print s2 in hex
	add a0, s2, x0
	addi a7, x0, 34
	ecall
	beq x0, x0, exit

	# newline
	addi a0, x0, 10
	addi a7, x0, 11
	ecall

"Question 3a -> s0 = 0xFF00FF00"

main:
    addi s1, x0, 0 # s1 = 0
    addi t0, x0, 1 # Use t0 as a mask to test each bit in s0
loop:
    and t1, s0, t0 # extract bit with a mask
    beq t1, x0, skip # if the bit is 0, do not increment s1
    addi s1, s1, 1 # increment the counter
skip:
    slli t0, t0, 1 # shift the mask to left by 1
    bne t0, x0, loop # if the mask is not 0, continue

Initial values
s0 = 1111 1111 0000 0000 1111 1111 0000 0000
t0 = 0000 0000 0000 0000 0000 0000 0000 0001

Initial instructions - 2.

The and / beq / slli / bne instructions execute for every bit in s0, thus 
32*4 = 128. The addi instruction will only execute for the 1 
bits in s0, thus 128 + 16 = 144. Adding the initial instructions
gives us a total value of 146 instructions. 

The location of the 1 bits do not matter, but the number of executed instructions
(at least for the addi instruction) does matter as addi will only run when the bit
is equal to 1. 

"Question 3b -> s0 = 0xFF00FF00 but 2's complement number"

# s0 = 1111 1111 0000 0000 1111 1111 0000 0000
1. check if MSB = 1
2. if 1, increase counter and decrement loop
3. if 0, just decrement loop
4. continue 32 times

main:
    addi s1, x0, 0 # counter
    add t0, s0, x0 # make a copy so s0 is not changed
    addi t1, x0, 32 # count down from 32 

loop: 
    blt t0, x0, counter # if MSB = 1, goto counter
    beq x0, x0, decrement # else, goto decrement

counter:
    addi s1, s1, 1 # increment counter

decrement:
    srai t0, t0, 1 # right shift to next MSB
    addi t1, t1, -1 # decrement loop counter
    bne t1, x0, loop # jump to loop 32 times

Initial instructions - 3.

Inside loop:
    blt / beq instructions will only run 32 times in total. 

Inside counter:
    addi instruction only runs when MSB = 1, thus 16 times.

Inside decrement: 
    srai / addi / bne / instructions each run 32 times, thus 32 * 3 = 96.

Total - 96 + 32 + 16 + 3 = 147 instructions. 

"Question 4: 

for (i = 0; i < a; i += 1)
    if ((i & 0xA5) != 0)
        r ^= i << 8;
    else
        r += i >> 4;"

main: 
    addi s1, x0, 10 # a = 10, counter
    addi s2, x0, 0 # i = 0
    addi s3, x0, 0 # r = 0

loop:
    bge s2, s1, exit
    andi t0, s2, 0xA5 # t0 = i and 0x45
    beq t0, x0, else # else, goto else

    # If portion
    slli t1, s2, 8 # t0 as placeholder for i << 8
    xor s3, s3, t1 # r = r xor t1
    beq x0, x0, increment 

else:
    srli t2, s2, 4 # t1 as placeholder for i >> 4
    addi s3, s3, t2 # r += t2

increment:
    addi s2, s2, 1 # increment i by 1
    beq x0, x0, loop # jump to start

exit:
    # exit

"Question 5: The Collatx Conjecture"
        
    .text
    .globl main

main:
    # System call to read an integer
    addi a7, x0, 5         # System call number for read_int
    ecall                  # Perform the system call, result in a0

    add t0, a0, x0         # Move input number to t0 for manipulation
    addi s1, x0, 0         # Initialize counter (s1) to 0
    addi t1, x0, 1         # Set t1 = 1, for comparison and incrementing counter

loop:
    beq t0, t1, exit       # If t0 is 1, exit loop

    andi t2, t0, 1         # t2 = t0 & 1, to check if t0 is even or odd
    bne t2, x0, odd           # If t2 != 0 (t0 is odd), go to odd

    # Even case: n = n / 2
    srli t0, t0, 1         # Right shift to divide t0 by 2
    beq x0, x0, increment_counter    # Jump to increment counter

odd:
    # Odd case: n = 3n + 1
    slli t2, t0, 1         # t2 = t0 * 2
    add t2, t2, t0         # t2 = t2 + t0 = 3*t0
    addi t0, t2, 1         # t0 = 3*t0 + 1

increment_counter:
    addi s1, s1, 1         # Increment counter
    beq x0, x0, loop                 # Jump back to start of loop

exit:
    # Prepare for system call to print the counter value
    add a0, s1, x0         # Move counter value to a0 for printing
    addi a7, x0, 1         # System call number for print_int
    ecall                  # Perform the system call to print s1

    # Exit the program
    addi a7, x0, 10        # System call number for exit
    ecall                  # Perform the exit system call

