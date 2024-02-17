#       CSE 3666 Lab 4
#	TAG: 5fd71ac11b8a14746aa31ed0caf142197fb20839

	.data
	.align	2	
word_array:     .word
        0,   10,   20,  30,  40,  50,  60,  70,  80,  90, 
        100, 110, 120, 130, 140, 150, 160, 170, 180, 190,
        200, 210, 220, 230, 240, 250, 260, 270, 280, 290,
        300, 310, 320, 330, 340, 350, 360, 370, 380, 390,
        400, 410, 420, 430, 440, 450, 460, 470, 480, 490,
        500, 510, 520, 530, 540, 550, 560, 570, 580, 590,
        600, 610, 620, 630, 640, 650, 660, 670, 680, 690,
        700, 710, 720, 730, 740, 750, 760, 770, 780, 790,
        800, 810, 820, 830, 840, 850, 860, 870, 880, 890,
        900, 910, 920, 930, 940, 950, 960, 970, 980, 990

        # code
        .text
        .globl  main
main:   
	addi	s0, x0, -1
	addi	s4, x0, -1
	addi	s5, x0, -1
	addi	s6, x0, -1
	addi	s7, x0, -1

	# help to check if any saved registers are changed during the function call
	# could add more...

        # la      s1, word_array
        lui     s1, 0x10010      # starting addr of word_array in standard memory config [LEFT]
        addi    s2, x0, 100      # 100 elements in the array [RIGHT]

        # read an integer from the console [V]
        addi    a7, x0, 5
        ecall

        addi    s3, a0, 0       # keep a copy of v in s3
        
        # call binary search
        addi	a0, s1, 0	# [LEFT]
        addi	a1, s2, 0	# [n]
        addi	a2, s3, 0	# [v]
        jal	ra, binary_search

        
          
exit:   addi    a7, x0, 10      
        ecall

#### Do not change lines above
binary_search:
    # stack allocation
    addi sp, sp, -16 
    sw s1, 0(sp)
    sw s2, 4(sp)
    sw s3, 8(sp)
    sw ra, 12(sp)
    
    beq s2, x0, bs_empty # Check if array is empty

    # Calculate midpoint
    srli t0, s2, 1 # t0 = n/2
    slli t1, t0, 2 # t1 = n/2 * 4 (byte offset for word array)
    add t2, s1, t1 # t2 = address of a[half]

    lw t3, 0(t2) # Load value at midpoint

    # Compare and branch
    beq s3, t3, bs_found # Target found at midpoint
    blt s3, t3, bs_search_left # Target is in the left half
    # Continue to search in the right half
    addi t4, t0, 1 # Calculate start of right half
    sub s2, s2, t4 # Adjust size for the right half search
    slli t5, t4, 2 # Calculate byte offset for the right half
    add s1, s1, t5 # Adjust array base address for right half
    jal ra, binary_search # Recursive call for right half

bs_return:
    # Restore stack and return
    lw s1, 0(sp)
    lw s2, 4(sp)
    lw s3, 8(sp)
    lw ra, 12(sp)
    addi sp, sp, 16
    jalr x0, ra, 0

bs_empty:
    addi a0, x0, -1 # Set return value to -1 for empty array
    beq x0, x0, bs_return

bs_found:
    addi a0, t0, 0 # Set return value to the index of the found element
    beq x0, x0, bs_return

bs_search_left:
    # Adjust size for left half search
    addi s2, t0, 0
    jal ra, binary_search # Recursive call for left half
    beq x0, x0, bs_return