# CSE 3666
        
        .data                   #data segment
        .align 2

src:   .word   
  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,
 10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
 20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
 30,  31,  32,  33,  34,  35,  36,  37,  38,  39,
 40,  41,  42,  43,  44,  45,  46,  47,  48,  49,
 50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
 60,  61,  62,  63,  64,  65,  66,  67,  68,  69,
 70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
 80,  81,  82,  83,  84,  85,  86,  87,  88,  89,
 90,  91,  92,  93,  94,  95,  96,  97,  98,  99,
100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
120, 121, 122, 123, 124, 125, 126, 127

dst:    .space  1024

        .text
        .globl  main

main: 
        lui     s1, 0x10010     # hard-coded src address
        addi    s3, s1, 512     # s3 is the destination array

        # read n, the number of words to shuffle
        # n is even and 2 <= n <= 128
        addi    a7, x0, 5
        ecall

        # n is in a0
        
        srli s0, a0, 1 # s0 = n / 2
        addi s4, x0, 0 # s4 = i = 0
        slli s2, s0, 2 # byte offset for n/2 words
        add s2, s2, s1 # address of right half of src
        
        # TODO:
        # write a loop to shuffle n words
        # the address of the source array src is in s1
        # the address of the destination array dst is in s3
        # register s2 will store the address of the second half of src
        # the folloiwng code can use any t and a registers
loop:
        bge     s4, s0, exit    # Exit loop if i >= n/2
	    slli    t0, s4, 2       # Calculate byte offset for i
	
        # Load from left half
        add     t1, s1, t0      # Address of left[i]
        lw      t2, 0(t1)       # Load left[i]
        slli 	t6, s4, 3 	# t6 = i * 8 (double byte offset for dst indexing)
        add     t3, s3, t6      # Address of dst[i*2]
        sw      t2, 0(t3)       # Store left[i] at dst[i*2]

        # Load from right half
        add     t4, s2, t0      # Address of right[i]
        lw      t5, 0(t4)       # Load right[i]
        sw      t5, 4(t3)       # Store right[i] at dst[i*2+1]

        addi    s4, s4, 1       # Increment loop counter i
        beq	x0, x0, loop    # Jump back to start of loop
       

exit:   addi    a7, x0, 10      # syscall to exit
        ecall   


s1	9	0x10010000
s2	18	0x10010068
s3	19	0x10010200

0x1a

00011010
2+8+16 = 26
0x0000001a

0x1001022c -> 0x0000001f
00011111
1+2+4+8+16 = 31