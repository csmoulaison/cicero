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
begin:
mov rdi, fmt
mov rsi, [rbp-16]
call printf
mov rax, [rbp-16]
mov rbx, 1
add rax, rbx
mov rax, rax
mov qword [rbp-16], rax
JMP begin
end:
mov rdi, 0
call exit
section .data
fmt: db "%i", 10, 0
