"Question 1"

/ prototype of bar
// the first argument is an address of an integer
int bar(int a[], int i);
{
    # assume implementation
}
int foo(int d[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i += 1) {
        int t = bar(&d[i], n - i); // &d[i] means d[i]’s address
        if (t > 0)
            count += 1;
    }
    
    return count;
}

main:
    # assume working functionality

foo:
    # stack allocation 
    addi sp, -16
    sw s0, 0(sp) # assume address stored here
    sw s1, 4(sp) # count
    sw s2, 8(sp) # i 
    sw s3, 12(sp) # n

    addi s1, x0, 0 
    addi s2, x0, 0
    addi s3, x0, 10 # 10 represents n

    # beginning of loop
    loop: 
        bge s2, s3, exit # if i >= n, exit

        slli t0, s2, 2 # i offset
        
        add a0, t0, s0 # add offset and save &d[i] in a0
        sub a1, s3, s2 # save n - i in a1

        jal ra, bar # stores return value in a0

        addi t1, x0, 1
        blt a0, t1, skip_increment # skip count if t < 1
        addi s1, s1, 1 # else, increment count

        skip_increment:
            addi s2, s2, 1 # increment i
            beq x0, x0, loop

    # set a0 to count
    add a0, s1, x0 
    
    # stack allocation
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    addi sp, 16

    # return 
    jalr x0, ra, 0

exit:
    # assume functionality

"Question 2"

void merge(intc[], int d1[], int n1, int d2[], int n2);
void copy(int d[], int c[], int n);

void msort(int d[], int n)
{
    int c[256];
    if (n <= 1)
        return;
    
    int n1 = n/2;

    msort(d, n1);
    msort(&d[n1], n - n1);
    merge(c, d, n1, &d[n1], n - n1);
    copy(d, c, n);
}

main:
    # assume functionality

msort:
    # stack allocation
    addi sp, -1036 # c[256] = 1024 bytes
    sw s0, 1024(sp) # address of c[]
    sw s1, 1028(sp) # address of d[]
    sw s2, 1032(sp) # n

    addi t0, x0, 2 # t0 = 2
    blt s2, t0, function_return

    # msort(d, n1);
    srli t1, s2, 1 # t1 = n / 2 = n1

    addi a0, s1, 0 # a0 = address of d[]
    addi a1, t1, 0 # a1 = n1
    
    jal ra, msort

    # msort(&d[n1], n - n1);
    slli t2, t1, 2 # n1*4 = offset
    add t3, s1, t2 # add offset, t3 = &d[n1]
    sub t4, s2, t1 # t4 = n - n1

    add a0, t3, x0 # a0 = t3
    sub a1, t4, x0 # a1 = t4

    jal ra, msort # second msort call

    # merge(c, d, n1, &d[n1], n - n1);
    add a0, s0, x0 # a0 = c
    add a1, s1, x0 # a1 = d
    add a2, t1, x0 # a2 = n1
    add a3, t3, x0 # a3 = &d[n1]
    add a4, t4, x0 # a4 = n - n1

    jal ra, merge

    # copy(d, c, n);
    add a0, s1, x0 # a0 = d
    add a1, s0, x0 # a1 = c
    add a2, s2, x0 # a2 = n

    jal ra, copy

    # stack allocation 
    lw s0, 1024(sp) # address of c[]
    lw s1, 1028(sp) # address of d[]
    lw s2, 1032(sp) # n
    addi sp, 1036

    function_return:
        jalr x0, ra, 0