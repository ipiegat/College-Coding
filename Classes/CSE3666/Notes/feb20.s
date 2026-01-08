"ASCII characters"

byte-wise storage

"Load small constant vs large constant"

Small : addi s0, x0, 0x12

If imm is large : 0x12345678

lui s0, 0x12345
addi s0, s0, 0x678

"Data of different sizes"

32-bit integer : 0A0B0C0D

Positions : a, a+1, a+2, a+3
Big-endian : 0A, 0B, 0C, 0D 
Little-endian : 0D, 0C, 0B, 0A

"Exercise"

addi x5, x0, 0x0C4
addi x5, x5, 4
lb x7, 0(x5)

0x000000C8 0xDB733A56

56 = least significant byte

0101 0110 # sign bit is 0, thus
0000 0000 0000 0000 0000 0000 0101 0110

x7 = 0x00000056

lb x8, 2(x5)

0x000000C8 0xDB733A56

with offset 2 use byte 73

0000 0000 0000 0000 0000 0000 <- 0111 0011

x8 = 0x00000073

"Decoding"

address : machine code
0x0040004C : 0xFCB5510E3

1111 1100 1011 0101 0001 0000 1110 0011

opcode : 110 0011 # branch instruction, SB
funct3 : 001 # indicates bne instruction
rs2 : 01011
rs1 : 01010 # 
imm : 1111 1110 0000 -> 0000 0001 1111 -> 64 thus -64

bne x10, x11, label

 0000 0000 0100 0000 0000 0000 0100 1100
+1111 1111 1111 1111 1111 1111 1110 0000
 0000 0000 0000 0000 0000 0000 000 1100


 "Encoding"

 beq x5, x6, 32

 rs1 : 0101
 rs2 : 0110
 imm : 0000 0000 0010 0000
