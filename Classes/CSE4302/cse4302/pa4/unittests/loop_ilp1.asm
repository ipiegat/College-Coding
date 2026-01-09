.text
# Preload all three A[i] values, using extra temps
lw   s0, 256(a0)  # A[0]
lw   t5, 257(a0)  # A[1]
lw   t6, 258(a0)  # A[2]

# Compute B[0], C[0], D[0] from A[0]
addi s1, s0, 2# 2 + A[0]
addi s2, s0, 3# 3 + A[0]
addi s3, s0, 4# 4 + A[0]

# Start using A[1] in between stores for A[0]
sw   s1, 259(a0)  # B[0]
addi s1, t5, 2# 2 + A[1]

sw   s2, 260(a0)  # C[0]
addi s2, t5, 3# 3 + A[1]

sw   s3, 261(a0)  # D[0]
addi s3, t5, 4# 4 + A[1]

# Store results for A[1]
sw   s1, 262(a0)  # B[1]
addi s1, t6, 2# 2 + A[2]

sw   s2, 263(a0)  # C[1]
addi s2, t6, 3# 3 + A[2]

sw   s3, 264(a0)  # D[1]
addi s3, t6, 4# 4 + A[2]

# Store results for A[2]
sw   s1, 265(a0)  # B[2]
sw   s2, 266(a0)  # C[2]
sw   s3, 267(a0)  # D[2]


addi zero, zero, 1

.data
256: .word 10
257: .word 20
258: .word 30