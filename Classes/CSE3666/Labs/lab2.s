#       CSE 3666 Lab 2

        .globl  main

        .text
main:   
        # use system call 5 to read integer
        addi    a7, x0, 5
        ecall
        addi    s1, a0, 0       # copy to s1
	
        # TODO
        # Add you code here
        # print int binary = 35, print acii = 11
        #   reverse bits in s1 and save the results in s2
        #   print s1 in binary, with a system call
        #   print newline
        #   print '=' if s1 is palindrome, otherwise print s2 in binary
        #   print newline

        addi t0, s1, 0 # set t0 = s1
        addi s2, x0, 0  # set s2 = 0
        addi s3, x0, 32 # set s3 = 32
        
Loop:
	beq s3, x0, L1
	# isolate LSB of s1 and add it to s2
	slli s2, s2, 1 # shift s2 left 
	andi t1, t0, 1 #  t3 = s1 and 1
	or s2, s2, t1 # add isolate bit to s2
	
	# prepare for next bit
	srli t0, t0, 1 # shift 1 right to get next bit
	addi s3, s3, -1 # decrement counter
	beq x0, x0, Loop # loop
	
L1: 
	# print s1 in binary, with a system call
	add a0, s1, x0
	addi a7, x0, 35
	ecall
	
	# newline
	addi a0, x0, 10
	addi a7, x0, 11
	ecall
	
	# print '=' if s1 is palindrone
	beq s1, s2, L2
	
	# otherwise print s2 in binary
	add a0, s2, x0
	addi a7, x0, 35
	ecall
	beq x0, x0, exit
	
L2: 
	# newline 
	addi a0, x0, 61
	addi a7, x0, 11
	ecall
	
exit:   
	# newline
	addi	a0, x0, 10
        addi	a7, x0, 11
        ecall 

	# exit
	addi    a7, x0, 10      
        ecall
	
        
