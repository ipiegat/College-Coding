lui rd, immd # load

"operations"
add s1, s1, 4 # s1 += 4
addi rd, rsl, imm # rd = rsl + imm\
sub s2, s2, 1 # s2 -= 1
li s3, 10 # s3 = 10
li s4, s3 # s4 = s3
mulh rd, rs1, rs2 # both are signed
mulhu rd, rs1, rs2 # both are unsigned
mulhsu rd, rs1, rs2 # rs1 is signed, rs2 is unsigned
div rd, rs1, rs2 # rs1 / rs2
rem rd, rs1, rs2 # rs1 % rs2
divu rd, rs1, rs2
remu rd, rs1, rs2

"branches"
beq rs1, rs2, L1 # if (rs1 == rs2) goto L1
bne rs1, rs2, L2 # if (rs1 != rs2) goto L2
blt rs1, rs2, L3 # if (rs1 < rs2) goto L3
bge rs1, rs2, L4 # if (rs1 >= rs2) goto L4
bltu rs1, rs2, L # if (rs1 < rs2) goto L UNSIGNED
bgeu rs1, rs2, L # if (rs1 >= rs2) goto L UNSIGNED

"logical operations"
# "i" means immediate, without i must use register
sll t0, t1, t2 | slli, t0, t1, 4
srl | srli # shift right bits
sra | srai
and | andi, t0, t1, t2 # t0 = t1 and t2
or | ori
xor | xori
not -> xori rd, rs1, -1 # NOT operation

"loading/storing instructions"
lb/lh rd, offset(rs1) # load signed (sign extended) byt/halfword
lbu/lhu rd, offset(rs1) # load unsigned (0 extended) byte/halfword
sb/sh rs2, offset(rs1) # store the lowest byte/halfword
