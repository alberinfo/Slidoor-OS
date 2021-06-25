[bits 16]
section .uarch
global _ap_entry
_ap_entry:
    mov BYTE [0x500], 1
    cli
    lgdt [0x1000]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp 0x8:0x2000

[bits 32]
global _ap_pmode_trampoline ;It is in the lower mem, lets use this for jumping to 1Meg
_ap_pmode_trampoline:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    lea eax, [_ap_pmode] ; If we don't do this, then the address will be a lil' greater than _ap_pmode_trampoline (and thus, stays around address 0x2000)
    jmp eax

_ap_pmode:
    mov eax, 0x103000
    mov cr3, eax
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax
    lgdt [_ap_low_GDT64.pointer]
    jmp 0x8:_ap_lmode_trampoline

[bits 64]
_ap_lmode_trampoline:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov rax, qword _ap_lmode
    jmp rax

extern _ap_main

section .text
extern kmalloc
_ap_lmode:
    mov rax, qword [0x4000]
    mov rbp, rax
    add rax, 0x1000
    mov rsp, rax
    push rax
    push rbx
    push rcx
    push rdx
    call AVX512Enable
    pop rdx
    pop rcx
    pop rbx
    pop rax
    call _ap_main
    cli
    hlt

AVX512Enable:
    mov rax, cr4
    or rax, 1 << 9  ;enable fxsave fxstor
    or rax, 1 << 10 ;enable unmasked SIMD floating point exceptions
    mov cr4, rax

    mov rax, 7
    xor rcx, rcx
    xor rbx, rbx
    cpuid
    and rbx, 1 << 16
    cmp rbx, 1 << 16
    je .enable
    jne AVXEnable
    ret

.enable:
    mov rax, cr4
    or rax, 1 << 18
    mov cr4, rax

    xor rcx, rcx
    xor rax, rax
    xgetbv
    or rax, 7
    or rax, 7 << 5
    xsetbv 
    ret

AVXEnable:
    mov rax, 7
    xor rcx, rcx
    xor rbx, rbx
    cpuid
    and rbx, 1 << 5
    cmp rbx, 1 << 5
    je .enable

    mov rax, 1
    xor rcx, rcx
    cpuid
    and rcx, 1 << 28
    cmp rcx, 1 << 28
    je .enable
    jne SSE_Enable
    ret

.enable:
    mov rax, cr4
    or eax, 0x40000
    or eax, 1 << 9  ;enable fxsave fxstor
    or eax, 1 << 10 ;enable unmasked SIMD floating point exceptions
    mov cr4, rax

    xor rcx, rcx
    xor rax, rax
    xgetbv
    or rax, 7
    xsetbv
    ret

SSE_Enable:
    mov rax, cr0
    and rax, ~(1 << 2) ; clear Emulation bit
    or rax, 1 << 1  ;enable Monitor co-processor
    mov cr0, rax
    ret

section .pregdt
global _ap_GDT32
_ap_GDT32:
    dq 0
.code:
    dw 0xFFFF
    dw 0
    dd 0x00CF9A00
.data:
    dw 0xFFFF
    dw 0
    dd 0x00CF9200
.end:

global _ap_GDT32Pointer
_ap_GDT32Pointer:
    dw _ap_GDT32.end - _ap_GDT32 - 1
    dd _ap_GDT32

_ap_low_GDT64:
    dq 0
.code: equ $ - _ap_low_GDT64
    dw 0xFFFF
    dw 0
    dd 0x00209A00
.data: equ $ - _ap_low_GDT64
    dw 0xFFFF
    dw 0    
    dd 0x00009200
.pointer:
    dw $ - _ap_low_GDT64 - 1
    dq _ap_low_GDT64

section .rodata
_ap_GDT64:
    dq 0
.code: equ $ - _ap_GDT64
    dw 0xFFFF
    dw 0
    dd 0x00209A00
.data: equ $ - _ap_GDT64
    dw 0xFFFF
    dw 0    
    dd 0x00009200
.pointer:
    dw $ - _ap_GDT64 - 1
    dq _ap_GDT64

;Continue on lmode set up
