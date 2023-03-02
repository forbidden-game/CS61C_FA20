.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
#   - If malloc returns an error,
#     this function terminates the program with error code 26
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fread error or eof,
#     this function terminates the program with error code 29
# ==============================================================================
read_matrix:

    # Prologue
    addi sp sp -24
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw ra 20(sp)
    # END Prologue

    mv s3 a1
    mv s4 a2

    li a1 0
    jal fopen
    li t0 -1
    beq a0 t0 exit_27
    mv s0 a0 # save file pointer to s0

    li s2 8 # malloc 2 32-bit space
    mv a0 s2
    jal malloc
    beqz a0 exit_26
    mv s1 a0 # save malloced address

    mv a0 s0
    mv a1 s1
    mv a2 s2
    jal fread
    bne a0 s2 exit_29

    lw t0 0(s1)
    lw t1 4(s1)
    sw t0 0(s3)
    sw t1 0(s4)

    mul t0 t0 t1 # get the result of row*col
    slli t0 t0 2 # matrix bytes
    mv s2 t0
    mv a0 s2
    jal malloc
    beqz a0 exit_26
    mv s1 a0 # save malloced address

    mv a0 s0
    mv a1 s1
    mv a2 s2
    jal fread
    bne a0 s2 exit_29

    mv a0 s0
    jal fclose
    bnez a0 exit_28

    mv a0 s1

    # Epilogue
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    lw ra 20(sp)
    addi sp sp 24
    # END Epilogue

    jr ra

exit_26:
    li a0 26
    j exit

exit_27:
    li a0 27
    j exit

exit_28:
    li a0 28
    j exit

exit_29:
    li a0 29
    j exit