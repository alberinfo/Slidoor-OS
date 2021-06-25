[BITS 64]

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

extern isr0_handler
extern isr1_handler
extern isr2_handler
extern isr3_handler
extern isr4_handler
extern isr5_handler
extern isr6_handler
extern isr7_handler
extern isr8_handler
extern isr9_handler
extern isr10_handler
extern isr11_handler
extern isr12_handler
extern isr13_handler
extern isr14_handler
extern isr15_handler
extern isr16_handler
extern isr17_handler
extern isr18_handler
extern isr19_handler
extern isr20_handler
extern isr21_handler
extern isr22_handler
extern isr23_handler
extern isr24_handler
extern isr25_handler
extern isr26_handler
extern isr27_handler
extern isr28_handler
extern isr29_handler
extern isr30_handler
extern isr31_handler

;Divide By Zero Exception
isr0:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr0_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Debug Exception
isr1:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr1_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Non Maskable Interrupt Exception
isr2:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr2_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Breakpoint Exception
isr3:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr3_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Overflow Exception
isr4:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr4_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Out of Bounds Exception
isr5:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr5_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Invalid Opcode Exeption
isr6:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr6_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Device Not Available Exception
isr7:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr7_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Double Fault Exception (ERR)
isr8:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr8_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq
    
;Coprocessor Segment Overrun Exception
isr9:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr9_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Bad TSS (ERR)
isr10:
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr10_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Segment Not Present Exception (ERR)
isr11:
    ;ERROR CODE ALREADY PUSHED!
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr11_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Stack Segment Fault Exception (ERR)
isr12:
    ;ERROR CODE ALREADY PUSHED!
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr12_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;General Protection Fault Exception (ERR)
isr13:
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr13_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Page Fault Exception (ERR)
isr14:
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr14_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Reserved Exception
isr15:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr15_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;x87 FPU Exception
isr16:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr16_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Alignment Check Exception
isr17:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr17_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Machine Check Exception
isr18:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr18_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rax
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;SIMD FPU Exception
isr19:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr19_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Virtualization Exception
isr20:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr20_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Reserved
isr21:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr21_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Reserved
isr22:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr22_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Reserved
isr23:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr23_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Reserved
isr24:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr24_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Reserved
isr25:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr25_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Reserved
isr26:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr26_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Reserved
isr27:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr27_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Reserved
isr28:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr28_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Reserved
isr29:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr29_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Security Exception
isr30:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr30_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq

;Reserved
isr31:
    push qword 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push gs
    push fs
    xor rax, rax
    mov ax, es
    push rax
    xor rax, rax
    mov ax, ds
    push rax
    call isr31_handler
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    pop fs
    pop fs
    pop gs
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop qword r8
    iretq
