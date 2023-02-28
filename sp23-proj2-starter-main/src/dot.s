.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:

    # Prologue
    addi sp sp -4
    sw s0 0(sp)
    #END Prologue

    li t0 0
    li t1 0
    li s0 0
    blt t0 a2 assert_stride_arr0
    li a0 36
    j exit

assert_stride_arr0:
    blt t0 a3 assert_stride_arr1
    li a0 37
    j exit

assert_stride_arr1:
    blt t0 a4 loop_start
    li a0 37
    j exit

loop_start:
    bge t0 a2 loop_end
    mul t3 t0 a3
    mul t4 t0 a4
    slli t3 t3 2
    slli t4 t4 2
    add t3 t3 a0
    add t4 t4 a1
    lw t3 0(t3)
    lw t4 0(t4)
    mul t5 t3 t4
    add s0 s0 t5
    addi t0 t0 1
    j loop_start

loop_end:
    mv a0 s0

    # Epilogue
    lw s0 0(sp)
    addi sp sp 4
    #END Epilogue

    jr ra
