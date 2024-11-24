section .text
extern printf
extern exit
global main
main:
push rbp
mov rbp, rsp
sub rsp, 16
mov rax, 8
mov qword [rbp-16], rax
mov rax, [rbp-16]
mov rbx, 3
add rax, rbx
mov rdi, fmt
mov rsi, rax
call printf
mov rdi, [rbp-16]
call exit
section .data
fmt: db "%i", 10, 0
