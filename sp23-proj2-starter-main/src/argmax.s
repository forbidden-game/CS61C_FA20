.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    # Prologue
    addi sp sp -4
    sw s0 0(sp)
    # END Prologue

    li t0 0
    li s0 0
    lw t1 0(a0)
    blt t0 a1 loop_start
    li a0 36
    j exit

loop_start:
    bge t0 a1 loop_end
    slli t2 t0 2
    add t2 t2 a0
    lw t3 0(t2)
    blt t1 t3 loop_continue
    addi t0 t0 1
    j loop_start

loop_continue:
    mv s0 t0
    mv t1 t3
    addi t0 t0 1
    j loop_start

loop_end:
    mv a0 s0

    # Epilogue
    lw s0 0(sp)
    addi sp sp 4
    # END Epilogue

    jr ra
