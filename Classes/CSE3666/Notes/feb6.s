"JAL"

jal rd, function_name

"How do we return?"

jalr rd, rs1, offset
jalr x0, ra, 0

"Example:"

main:
jal ra, foo
add s0, s0, a0

foo:
# stuff
jalr x0, ra, 0

1. JAL sets PC = foo, ra = main + 4
2. continue from foo
3. JALR sets PC = ra

"Passing and returning values"

a0, a1, a2, a3, a4, a5, a6, a7 (eight can be passed)
a0, a1 (two can be returned)

"Example:"

int abs (int n)
{
    int rv = n;
    if (n < 0)
        rv = -n;
    return rv;
}

abs:
    bge a0, x0, exit
    sub a0, x0, a0

exit:
    jalr x0, ra, 0

"Stack"

Goes from higher addresses to lower addresses

# push x1
addi sp, sp, -4
sw x1, 0(sp)

# pop x1
lw x1, 0(sp)
addi sp, sp 4

"Push multiple words"

addi sp, sp, -12
sw s1, 8(sp)
sw s2, 4(sp)
sw s3, 0(sp)

"Push and pop pairs"

# pop s1, s2, and s3
lw s1, 8(sp)
lw s2, 4(sp)
lw s3, 0(sp)
addi sp, sp, 12 # restore sp after loads

