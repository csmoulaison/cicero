global _start
_start:
push rbp
mov rbp, rsp
sub rsp, 16
mov rax, 2
mov qword [rbp-16], rax
sub rsp, 16
mov rax, 3
mov rbx, [rbp-16]
mul rbx
mov rax, rax
mov qword [rbp-32], rax
mov rax, [rbp-16]
mov rbx, [rbp-32]
mul rbx
mov rax, rax
mov rbx, 6
sub rax, rbx
mov rax, rax
mov rbx, 4
add rax, rbx
mov rax, rax
mov rbx, [rbp-16]
add rax, rbx
mov rdi, rax
mov rax, 60
syscall
