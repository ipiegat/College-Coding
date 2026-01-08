"Core Instruction Format"

imm[11:0] means bits 11, 10, ... , 1, and 0 in imm

"LUI Examples"

lui x19, 0x3D0 
0000 0000 0011 1101 0000 0000 0000 0000

addi x19, x19, 0x500
0000 0000 0011 1101 0000 0101 0000 0000

"Encoding LUI: U-type Instructions"

imm[31:12] | rd | opcode

"Excerise"
lui x1, 0xABCDE # the 32-bit imm is 0xABCDE000

# In machine code
                           # rd    #opcode
1010 1011 1100 1101 1110 | 00001 | 0110111

"Format for branches"

Which is best type? R, I, or S?

"Encoding and executing branches"

branch offset = target address - PC
> 0, jump forward
== 0, the branch itself
< 0, jump backward

target address = PC + imm


