"Addi -> Addition with an immediate"
addi rd, rsl, imm # rd = rsl + imm

"operations"
add s1, s1, 4 # s1 += 4
sub s2, s2, 1 # s2 -= 1
li s3, 10 # s3 = 10
li s4, s3 # s4 = s3

"branches"
beq rs1, rs2, L1 # if (rs1 == rs2) goto L1
bne rs1, rs2, L2 # if (rs1 != rs2) goto L2
blt rs1, rs2, L3 # if (rs1 < rs2) goto L3
bge rs1, rs2, L4 # if (rs1 >= rs2) goto L4

"while loop, method 1"
Loop:
    if (! cond) goto Exit
    Statements
    goto Loop
Exit:

"RISC-V code"
    addi s0, x0, 0 # i = 0
    addi s1, x0, 0 # sum = 0
    addi s2, x0, 100 
loop:   
    bge s1, s2, exit
    add s1, s1, s0
    addi s0, s0, 1
    beq x0, x0, loop
exit:

# Above code total instructions 3 + 100(4) + 1 = 404

"while loop method 2"
    goto Test
Loop:
    Statements

Test:
    if (cond) goto Loop

"RISC-V code"
    addi s0, x0, 0 # i = 0
    addi s1, x0, 0 # sum = 0
    addi s2, x0, 100
    beq x0, x0, Test
loop:
    add s1, s1, s0
    addi s0, s0, 1
test:
    blt s0, s2, loop

# Above code total instructions 3 + 100(3) + 1 = 304





    