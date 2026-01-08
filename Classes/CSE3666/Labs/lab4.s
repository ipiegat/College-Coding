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

        # TODO
        
        addi	sp, sp, -8		# allocating memory
        sw	s1, 4(sp)
        sw	ra, 0(sp)
        
        beq	a1, x0, nothing
       	
       	srli	t0, a1, 1		# t0 = n/2 [half]
       	slli	t1, t0, 2		# t1 = (n/2) * 4
       	add	t2, t1, a0		# memory location of mid
       	lw	t3, 0(t2)		# t3 = half_v	[half_v = a[half]]
       	
       	beq	a2, t3, if		# [if (half_v == v)]
       	blt	a2, t3, elseif		# [else if (v < half_v)]
       	bge	a2, t3, else		# [else (v > half_v)]
       	
        
if:
	add	a0, t0, x0
	beq	x0, x0, endif
		
elseif:
	add	a1, t0, x0		# n = half
	jal	ra, binary_search	# binary_search(a, half, v)
	add	a0, a0, x0
	beq	x0, x0, endif
	
else:
	addi	s1, t0, 1		# s1 = t0 + 1 [left = half + 1]
	slli	t5, s1, 2		# t5 = t4 * 4
	add	a0, a0, t5		# update address of left to address of mid
	sub	a1, a1, s1		# t5 = a1 - t4 (n - left)
	jal	ra, binary_search
	
	blt	a0, x0, endif
	add	a0, a0, s1		# rv += left
	beq	x0, x0, endif
	
nothing:
	addi	a0, x0, -1

endif:

        lw	ra, 0(sp)
        lw	s1, 4(sp)
        addi	sp, sp, 8	# deallocating memory
        jalr	x0, ra, 0
