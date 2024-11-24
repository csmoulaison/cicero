section .text
extern printf
extern exit
global main
main:
push rbp
mov rbp, rsp
sub rsp, 16
mov rax, 0
mov qword [rbp-16], rax
loop:
mov rdi, fmt
mov rsi, [rbp-16]
call printf
mov rax, [rbp-16]
mov rbx, 1
add rax, rbx
mov rax, rax
mov qword [rbp-16], rax
mov rax, [rbp-16]
mov rbx, 10
cmp rax, rbx
JG CICERO_IF_LABEL0
JMP loop
CICERO_IF_LABEL0:
mov rdi, 0
call exit
section .data
fmt: db "%i", 10, 0
