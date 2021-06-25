#!/bin/bash

GCC="../Cross-compiler/gcc/x86_64-elf-gcc-8.3.0"
LD="../Cross-compiler/ld/bin/ld"
WINIMG="../OSinWin"

# clean previous build files
rm -f kernel/obin/*.o
rm -f kernel/obin/bootloader.bin
rm -f Slidoor/boot/bootloader.bin

if [ "clean" = "$1" ]; then
  exit
fi;

# compile
nasm -f elf64 -w -all boot/bootloader.asm -o kernel/obin/bootloader.o
nasm -f elf64 -w -all boot/incapableboot.asm -o kernel/obin/incapableboot.o
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/kernel.c -o kernel/obin/kc.o -w -g #nostdlib?
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/grub/multiboot.c -o kernel/obin/multiboot.o -w -g

nasm -f elf64 -w -all kernel/src/arch/x86/isr.asm -o kernel/obin/israsm.o
nasm -f elf64 -w -all kernel/src/arch/x86/irq.asm -o kernel/obin/irqasm.o
nasm -f elf64 -w -all kernel/src/arch/x86/smp.asm -o kernel/obin/smpasm.o
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/setup/setup.c -o kernel/obin/setup.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/arch/x86/cpu.c -o kernel/obin/cpu.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/vga/vga.c -o kernel/obin/vga.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -O3 -c kernel/src/drivers/vesa/vesa.c -o kernel/obin/vesa.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -O3 -c kernel/src/console/console.c -o kernel/obin/console.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/acpi/acpi.c -o kernel/obin/acpi.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/acpi/madt.c -o kernel/obin/madt.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/acpi/fadt.c -o kernel/obin/fadt.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/acpi/dsdt.c -o kernel/obin/dsdt.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/acpi/rsdt.c -o kernel/obin/rsdt.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/acpi/rsdp.c -o kernel/obin/rsdp.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/acpi/interpreter/namespace.c -o kernel/obin/AcpiNamespace.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/acpi/interpreter/eval.c -o kernel/obin/AcpiEval.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/arch/x86/lapic.c -o kernel/obin/lapic.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/arch/x86/ioapic.c -o kernel/obin/ioapic.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/energy/energy.c -o kernel/obin/energy.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -O3 -c kernel/src/string/string.c -o kernel/obin/string.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/arch/x86/smp.c -o kernel/obin/smp.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/pci/pci.c -o kernel/obin/pci.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/pcie/pcie.c -o kernel/obin/pcie.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/kb/kb.c -o kernel/obin/kb.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/arch/x86/idt.c -o kernel/obin/idt.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/arch/x86/isr.c -o kernel/obin/isr.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/arch/x86/irq.c -o kernel/obin/irq.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/memory/paging.c -o kernel/obin/paging.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/memory/pmm.c -o kernel/obin/pmm.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/rtc/rtc.c -o kernel/obin/rtc.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/sleep/sleep.c -o kernel/obin/sleep.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/pit/pit.c -o kernel/obin/pit.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/hpet/hpet.c -o kernel/obin/hpet.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/ata/ata.c -o kernel/obin/ata.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/ata/atapi.c -o kernel/obin/atapi.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/ata/pio/ata_pio.c -o kernel/obin/ata_pio.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/ata/pio/atapi_pio.c -o kernel/obin/atapi_pio.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/ata/dma/ata_dma.c -o kernel/obin/ata_dma.o -w
"$GCC" -m64 -fno-stack-protector -mno-red-zone -msse2 -ftree-vectorize -mcmodel=large -I. -c kernel/src/drivers/ata/dma/atapi_dma.c -o kernel/obin/atapi_dma.o -w

cd kernel/src/console/

objcopy -O elf64-x86-64 -B i386 -I binary "Font.psf" ../../obin/font.o


# link
cd ../../obin/

"../../$LD" -N --output=bootloader.bin --script=../../link.ld bootloader.o incapableboot.o kc.o multiboot.o setup.o vga.o vesa.o console.o string.o smpasm.o smp.o idt.o israsm.o isr.o irqasm.o irq.o kb.o acpi.o AcpiNamespace.o AcpiEval.o madt.o fadt.o dsdt.o rsdt.o rsdp.o lapic.o ioapic.o energy.o cpu.o pci.o pcie.o rtc.o paging.o pmm.o sleep.o pit.o hpet.o ata.o atapi.o ata_pio.o atapi_pio.o ata_dma.o atapi_dma.o font.o

cp bootloader.bin ../../Slidoor/boot/
cd ../../

# build iso image
grub-mkrescue -o Slidoor.iso Slidoor/

cp Slidoor.iso "$WINIMG"

./objdump.sh
#./"iso dump.sh"

# run
read -p "Please, choose your emulator. For Bochs, press 0. For Qemu, press 1. " EMULATOR
if [ "$EMULATOR" = 0 ]; then
    rm disk.img.lock
    bochs -q -f bochsrc.bxrc
elif [ "$EMULATOR" = 1 ]; then
    qemu-system-x86_64 -cpu SandyBridge -cdrom Slidoor.iso -hda disk.img -debugcon stdio -smp 4 -m 128M #-S -s & gdb -w obin/bootloader.o \
#    -ex 'target remote localhost:1234' \
#    -ex 'return' \
#    -ex 'c' \
else
    read -n 1 -s -r -p "Option $EMULATOR is not in the emulator list. Press any key to continue."
    echo
    exit 1
fi

#./"disk dump.sh"

rm -f Slidoor.iso
rm -f disk.img.lock
rm -f kern.sym
rm -f disk.txt

cd kernel/obin/
rm *.o
rm *.bin
cd ../../
