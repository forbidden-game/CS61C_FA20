.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
    # Prologue
    addi sp sp -4
    sw s0 0(sp)
    # END Prologue

    li t0 1
    li t1 0
    bge a1 t0 loop_start
    li a0 36
    j exit
    
loop_start:
    bge t1 a1 loop_end
    slli t2 t1 2
    add t2 a0 t2
    lw s0 0(t2)
    blt s0 x0 loop_continue
    addi t1 t1 1
    j loop_start
    
loop_continue:
    sw x0 0(t2)
    addi t1 t1 1
    j loop_start
    
loop_end:
    li a0 17
    li a1 0
    ecall

    # Epilogue
    lw s0 0(sp)
    addi sp sp 4
    # END Epilogue
    
    jr ra
