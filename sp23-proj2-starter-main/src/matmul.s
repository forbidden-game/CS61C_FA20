.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:

    # Error checks
    ble a1 x0 exit_38
    ble a2 x0 exit_38
    ble a4 x0 exit_38
    ble a5 x0 exit_38
    bne a2 a4 exit_38

    # Prologue
    addi sp sp -32
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw s5 20(sp)
    sw s6 24(sp)
    sw ra 28(sp)
    # END Prologue

    mv s0 a0
    mv s1 a1
    mv s2 a2
    mv s3 a3
    mv s4 a4
    mv s5 a5
    mv s6 a6

    li t0 0 # row index of m0
    li t1 0 # offset of m0
    li t2 0 # column index of m1
    li t3 0 # offset of m1
    li t4 0 # offset of d
    li t5 1 # stripe of m0

outer_loop_start:
    bge t0 s1 outer_loop_end
    mul t1 t0 s2
    slli t1 t1 2
    add t1 t1 s0
    li t2 0

inner_loop_start:
    bge t2 s5 inner_loop_end
    slli t3 t2 2
    add t3 t3 s3

    mv a0 t1
    mv a1 t3
    mv a2 s2
    mv a3 t5
    mv a4 s5

    addi sp sp -24
    sw t0 0(sp)
    sw t1 4(sp)
    sw t2 8(sp)
    sw t3 12(sp)
    sw t4 16(sp)
    sw t5 20(sp)

    jal ra dot

    lw t0 0(sp)
    lw t1 4(sp)
    lw t2 8(sp)
    lw t3 12(sp)
    lw t4 16(sp)
    lw t5 20(sp)
    addi sp sp 24

    mul t4 t0 s5
    add t4 t4 t2
    slli t4 t4 2
    add t4 t4 s6
    sw a0 0(t4)
    addi t2 t2 1
    j inner_loop_start

inner_loop_end:
    addi t0 t0 1
    j outer_loop_start

outer_loop_end:
    li a0 17

    # Epilogue
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    lw s5 20(sp)
    lw s6 24(sp)
    lw ra 28(sp)
    addi sp sp 32
    # END Epilogue

    jr ra

exit_38:
    li a0 38
    j exit