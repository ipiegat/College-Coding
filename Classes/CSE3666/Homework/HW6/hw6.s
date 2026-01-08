"Question 1"

0x00400200 : 0xFE542023

1111 1110 0101 0100 0010 0000 0010 0011

opcode : 0100011 # s-type
rs2 : 00101
rs1 : 01000
funct3 : 010 # sw instruction
imm : 1111 1110 0000 = 0xFFFFFFE0
rd : 00000
ALU Op : 0b0010 # addition 
Branch Target : 0x00400200 + 0xFFFFFFE0 = 0x004002E0
PCSrc : 0
NextPC : 0x00400204

"Question 2"

x4 = 0x0000FFF0, x16 = 0x09AB000C

0x0040033C : 0x01020233 # add x4, x4, x16
