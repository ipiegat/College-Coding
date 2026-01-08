"Question 1"

lb t0, 0x201(x0)

0x0000 0201 | 0x81
answer: 0xFFFF FF81

"Question 2"

lh t0, 0x200(x0)

0x0000 0201 | 0x81
0x0000 0200 | 0xAC
answer: 0xFFFF 81AC

"What information do you want to keep in the instruction word?"

# Instruction type | Operand
add rd, rs1, rs2
addi rd, rs1, immd
lw rd, offset(rs1)
sw rs2, offset(rs1)

"R Type instructions"

# For instructions that have 3 registers as operands
opcode: 7-bit operation code
rd: destination register number (5 bits)
rs1: first sourse register number (5 bits)
rs2: second source register number (5 bits)
funct3: additional function code (3 bits)
funct7: even more function code (7 bits)

funct7 | rs2 | rs1 | funct3 | rd | opcode

"R type Example: ADD"

add x1, x2, x3
0 | 3 | 2 | 0 | 1 | 0x33
000 0000 | 00011 | 00010 | 000 | 00001 | 011 0011 

"I type Example: ADDI"

opcode: operation code (7)
rd: destination source register (5)
rs1: first source register number (5)
funct3: additional function code (3)
imm: lower 12 bits of imm, in the place of funct7 and rs2

imm[11:0] | rs1 | funct3 | rd | opcode

addi x1, x2, 32
0000 0010 0000 | 00010 | 000 | 00001 | 0010011

"I type Example: SRLI vs SRAI"

srli x1, x2, 16
0000000 | 10000 | 00010 | 101 | 00001 | 0010011

srai x1, x2, 16
0100000 | 10000 | 00010 | 101 | 00001 | 0010011

"What format would you use to load instructions?"

lw rd, offset(rs1) -> I-type

lw x1, 32(x2)
0000 0010 0000 | 00010 | 010 | 00001 | 000 0011

"How about store instructions?"

store instructions have rs2, but not rd
sw rs2, offset(rs1)

"S Type Instructions"

imm{11:5] | rs2 | rs1 | funct3 | imm[4:0] | opcode

imm[11:5] and imm[4:0]:
    - the lower 12 bits of the immediate are stored into two fields
    - bits 11 to 5 are in funct7 and bits 4 to 0 are in rd

sw rs2, offset(rs1)


