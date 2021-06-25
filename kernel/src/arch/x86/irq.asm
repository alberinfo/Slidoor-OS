global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

extern irq0_handler
extern irq1_handler
extern irq2_handler
extern irq3_handler
extern irq4_handler
extern irq5_handler
extern irq6_handler
extern irq7_handler
extern irq8_handler
extern irq9_handler
extern irq10_handler
extern irq11_handler
extern irq12_handler
extern irq13_handler
extern irq14_handler
extern irq15_handler

irq0:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq0_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq1:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq1_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq2:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq2_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq3:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq3_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq4:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq4_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq5:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq5_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq6:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq6_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq7:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq7_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq8:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq8_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq9:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq9_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq10:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq10_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq11:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq11_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq12:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq12_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq13:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq13_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq14:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq14_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq

irq15:
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsp
    push rsi
    push rdi
    call irq15_handler
    pop rdi
    pop rsi
    pop rsp
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
    iretq
