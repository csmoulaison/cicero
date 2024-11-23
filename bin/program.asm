global _start
_start:
push rbp
mov rbp, rsp
sub rsp, 16
mov rax, 4
mov qword [rbp-16], rax
sub rsp, 16
mov rax, [rbp-16]
mov rbx, 6
add rax, rbx
mov rax, rax
mov qword [rbp-32], rax
mov rax, [rbp-32]
mov rbx, [rbp-16]
add rax, rbx
mov rdi, rax
mov rax, 60
syscall
