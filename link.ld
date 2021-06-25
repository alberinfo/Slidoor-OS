ENTRY(_start);
OUTPUT_FORMAT(elf64-x86-64)

kern_lma = 0x100000;
kern_vma = 0xFFFF800000000000;

SECTIONS
{
  . = kern_lma;
  .boot : { *(*.mboot*) }
  .usslessarch ALIGN(4K) : { *(*.uarch*) } /*This is for the lmode_start func, have to put it in the 1M mark*/
  .preliminargdt ALIGN(4K) : { *(*.pregdt*) } /*This is for the gdt64, instead of using rodata and being linked on higher half*/
  .preliminarbss ALIGN(4K) : { *(*.prebss*) }
  . += kern_vma;
  .text ALIGN(4K) : AT(ADDR(.text) - kern_vma) { *(*.text*) }
  .data ALIGN(4K) : AT(ADDR(.data) - kern_vma) { *(*.data*) }
  .rodata ALIGN(4K) : AT(ADDR(.rodata) - kern_vma) { *(*.rodata*) }
  .bss ALIGN(4K) : AT(ADDR(.bss) - kern_vma) { *(*.bss*) *(COMMON) }
  .heap ALIGN(4K) : AT(ADDR(.heap) - kern_vma) { *(*.heap*) }
   kernel_end = .;
  /DISCARD/ ALIGN(4K) : AT(ADDR(.rodata) - kern_vma) { *(*.comment*) /**(*.eh_frame*)*/ }
}
