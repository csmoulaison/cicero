section .text
extern printf
extern exit
global main
main:
push rbp
mov rbp, rsp
sub rsp, 16
mov rax, 22
mov qword [rbp-16], rax
sub rsp, 16
mov rax, 2
mov rbx, [rbp-16]
mul rbx
mov rax, rax
mov rbx, 6
add rax, rbx
mov rax, rax
mov qword [rbp-32], rax
mov rdi, fmt
mov rsi, [rbp-32]
call printf
mov rdi, [rbp-16]
call exit
section .data
fmt: db "%i", 10, 0
