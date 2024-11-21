global _start
_start:
push rbp
mov rbp, rsp
sub rsp, 8
mov qword [rbp-8], 5
mov rdi, 2
mov rax, 60
syscall
