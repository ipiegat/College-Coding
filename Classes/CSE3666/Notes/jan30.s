"s1 = s0 * 9"
slli s1, s0, 3
add  s1, s0, s0

"Load 32-bit Constants into a register"

addi x1, x0, immd # cannot use
lui rd, immd # allows 20 bit immediate 
# The 20 bits are placed into bits 12 to 31, lower 12 are cleared

"Load 0x12345678 into register s0"
lui s0, 0x12345
addi s0, s0, 0x678

"Load 0x789ABCDE into register s0"
lui s0, 0x789AC
addi s0, s0, 0xFFFFFCDE

"Using data in memory"
Load: memory to register
Store: register to memory

"How to get the address of a variable in the register?"
load address # psuedoinstructions in LA

# load a word from memory into rd
# Reg[rd] = Mem[Reg[rs1] + offset]
lw rd, offset(rs1)

# save a word to mem
# Mem[Reg[rs1] + offset] = Reg[rs2]
sw rs2, offset(rs1)
# effective address = Reg[rs1] + offset

"Copy a word from one address to another"
lw t0, 0(s1)
sw t0, 0(s2) # assume s1 != s2

"Addressing mode"
offset(rs1)

#mistakes
lw x1(x3) # offset must be an immediate
lw x1, 20000(x3) # offset is too large
lw x1, (x3) # missing offset, write 0(x3)

"b = a;"
lui t1, 0x00FE9 # t1 = a's address
lw t0, 0(t1) # 9004
sw t0, 4(t1) # 9000, thus offset 4

"How do we load the following array elements into registers?"
# note A's address is in s1
A[0] -> lw t0, 0(s1)
A[1] -> lw t0, 4(s1)
A[2] -> lw t0, 8(s1)

A[i] # i is in s2

"Memory example: A[20] = h + A[4]"
lw t0, 16(s3) # load A[4]
add t1, t0, s2
sw t1, 80(s3) # save to A[20]

"Example: Clearing an array"
for (i = 0; i < 8; i = i + 1)
    a[i] = 0

    addi t0, x0, 0 # i = 0
    addi t1, x0, 8 # end = 8

loop: 
    slli t2, t0, 2 # 4 * i
    add t3, t2, s1 # actual address
    sw x0, 0(t3) #clearing
    addi t0, t0, 1
    blt t0 ,t1, loop

"How is word stored in memory? Which byte goes to address 0x100?"

# x1 is 0x01020304
sw x1, 0x100(x0)

Big-endian: The highest btye goes to the lowest memory address
Little-endian: The lowest byte goes to the lowest memory address

"Data of other sizes"

# load signed (sign extended) byt/halfword
lb/lh rd, offset(rs1)

# load unsigned (0 extended) byte/halfword
lbu/lhu rd, offset(rs1)

# store the lowest byte/halfword
sb/sh rs2, offset(rs1)




