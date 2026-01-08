"Question 4"

// char * means the address of a character
char * uint2decstr(char s[], unsigned int v)
{
unsigned int r;
if (v >= 10) {
    s = uint2decstr(s, v / 10);
    }

r = v % 10; // remainder
s[0] = '0' + r;
s[1] = 0;
return &s[1]; // return the address of s[1]}

main:   
        # create an array of 128 bytes on the stack
        addi    sp, sp, -128

        # copy array's address to a0
        addi    a0, sp, 0

	# set all bytes in the buffer to 'A'
        addi    a1, x0, 0       # a1 is the index
	addi	a2, x0, 128
	addi	t2, x0, 'A'
clear:
        add     t0, a0, a1
	sb	t2, 0(t0)
        addi    a1, a1, 1
	bne	a1, a2, clear
	
        # change -1 to other numbers to test
        # you can use li load other numbers for testing
        # li      a1, 36663666
        addi	a1, zero, -1
	jal	ra, uint2decstr

        # print the string
        addi    a0, sp, 0
        addi    a7, x0, 4
        ecall

exit:   addi    a7, x0, 10      
        ecall

# char * uint2decstr(char *s, unsigned int v) 
# the function converts an unsigned 32-bit value to a decimal string
# Here are some examples:
# 0:    "0"
# 2022: "2022"
# -1:   "4294967295"
# -3666:   "4294963630"

uint2decstr:
    addi s0, a0, 0 # s[]
    addi s1, a1, 0 # v
    addi s2, x0, 0 # r

    # stack allocation
    addi sp, sp, -16
    sw ra, 12(sp)
    sw s2, 8(sp)
    sw s1, 4(sp)
    sw s0, 0(sp) 


if:
    addi t0, x0, 10 # t0 = 10
    blt s1, t0, skip # skip if v < 10

    addi a0, s0, 0 # a0 = s
    div a1, s1, t0 # a1 = v / 10
    
    jal ra, uint2decstr
    addi s0, a0, 0 # move result to s0

skip:
    lw s1, 4(sp) # original v value

    rem s2, s1, t0 # r = v % 10

    addi t2, x0, 48
    add t1, t2, s2 # t1 = '0' + r

    sb t1, 0(s0) # s[0] = t1 = '0' + r
    sb x0, 1(s0) # s[1] = 0

    addi a0, s0, 1 # &s[1]

    # stack allocation
    lw ra, 12(sp)
    lw s2, 8(sp)
    lw s0, 0(sp) 
    addi sp, sp, 16

    jalr x0, ra, 0


