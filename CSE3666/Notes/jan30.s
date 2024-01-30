1. s1 = s0 * 9
slli s1, s0, 3
add  s1, s0, s0

"Load 32-bit Constants into a register"

addi x1, x0, immd # cannot use
lui rd, immd # allows 20 bit immediate 
# The 20 bits are placed into bits 12 to 31, lower 12 are cleared

"Load 0x12345678 into register s0"
lui s0, 0x12345
addi s0, s0, 0x678
