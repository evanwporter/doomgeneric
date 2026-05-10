.section .text
.global __syscall3
.type __syscall3, @function

# long __syscall3(long num, long arg0, long arg1, long arg2)

__syscall3:
    mv a7, a0
    mv a0, a1
    mv a1, a2
    mv a2, a3
    ecall
    ret