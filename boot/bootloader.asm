[BITS 32]

%define STACK_SIZE 0x20000 ;This MAY be not enough. Or maybe it is. who knows (check &/ change in case of those strange unreasonable errors)

HIGHER_VMA equ 0xFFFF800000000000
high_PML4_idx equ (HIGHER_VMA >> 39) & 0x1FF
high_PDPT_idx equ (HIGHER_VMA >> 30) & 0x1FF

section .mboot
mboot_header_start:
    dd 0xe85250d6
    dd 0
    dd mboot_header_end - mboot_header_start
    dd 0x100000000 - (0xe85250d6 + 0 +(mboot_header_end - mboot_header_start))

    align 8
mboot_inforeq_start:
    dw 1
    dw 0
    dd mboot_inforeq_end - mboot_inforeq_start
    dd 2 ;Boot loader name
    dd 6 ;Memory map
    dd 7 ;Vbe info
    dd 8 ;Framebuffer info
    dd 14 ;Acpi 1.0 Rsdp info
    dd 15 ;Acpi 2.0+ Rsdp info
mboot_inforeq_end:

    align 8
mboot_framebuffer_start:
    dw 5
    dw 1
    dd mboot_framebuffer_end - mboot_framebuffer_start
    dd 800
    dd 600
    dd 32
mboot_framebuffer_end: ; in this tag we set a video mode, otherwise the gfxpayload will not work in grub.cfg (note that 800x600 wont be the used mode unless said so by the user)

    align 8
mboot_end_start:
    dw 0
    dw 0
    dd mboot_end_end - mboot_end_start
mboot_end_end:

mboot_header_end:

extern no_cpuid
extern no_lmode
extern no_higher_half

[bits 32]
section .uarch
global _start
_start:
    push ebx
    call check_cpuid
    call check_lmode
    call check_vbits
    xor ecx, ecx
    call map_PD
    call setup_paging
    call enable_paging
    pop ebx
    lgdt [lowgdt64.pointer]
    jmp lowgdt64.code:trampoline

check_cpuid:
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    push ecx
    popfd
    cmp eax, ecx
    je no_cpuid
    ret

check_lmode:
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb no_lmode
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz no_lmode
    ret

check_vbits: ;See if the amount of virtual bits is enough
    mov eax, 0x80000008
    cpuid
    shr eax, 8
    cmp eax, 0x30
    jl no_higher_half
    ret

map_PD:
    mov eax, 0x200000
    mul ecx
    or eax, 0b10000011
    mov [PD + ecx * 8], eax
    inc ecx
    cmp ecx, 512
    jne map_PD
    ret

setup_paging:
    mov eax, PD
    or eax, 0b11
    mov [PDPT], eax
    mov [PDPT+(high_PDPT_idx*8)], eax
    mov eax, PDPT
    or eax, 0b11
    mov [PML4], eax
    mov [PML4+(high_PML4_idx*8)], eax
    ret

enable_paging:
    mov eax, PML4
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
    ret

[BITS 64]

trampoline: ; we fix leave long mode, at the same time we dont get relocation error ;)
    mov ax, lowgdt64.data
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov rax, qword higher_half
    jmp rax

extern kmain

section .text
higher_half:
    mov rbp, qword (stack + 0xFFFF800000000000)
    mov rsp, qword (stack_end + 0xFFFF800000000000)
    mov rax, qword gdt64.pointer
    lgdt [rax]
    ;remove lower half
    xor rax, rax
    mov [PML4], rax
    invlpg [0]
    push rax
    push rbx
    push rcx
    push rdx
    call AVX512Enable
    pop rdx
    pop rcx
    pop rbx
    pop rax
    call kmain
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
lowgdt64: ;preliminar GDT for the lower half, linked at 1MiB
    dq 0
.code: equ $ - lowgdt64
    dw 0xFFFF
    dw 0
    dd 0x00209A00
.data: equ $ - lowgdt64
    dw 0xFFFF
    dw 0    
    dd 0x00009200
.pointer:
    dw $ - lowgdt64 - 1
    dq lowgdt64

section .rodata
gdt64: ;GDT for the higher half, linked at HIGHER_VMA
    dq 0
.code: equ $ - gdt64
    dw 0xFFFF
    dw 0
    dd 0x00209A00
.data: equ $ - gdt64
    dw 0xFFFF
    dw 0    
    dd 0x00009200
.pointer:
    dw $ - gdt64 - 1
    dq gdt64

section .prebss
align 4096
PML4 : resb 4096 ; AT 0x103000
PDPT : resb 4096 ; AT 0x104000
PD : resb 4096 ; AT 0x105000

stack:
resb STACK_SIZE
stack_end:
