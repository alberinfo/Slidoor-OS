#ifndef SETUP_H
#define SETUP_H

#include "../arch/x86/idt.h"
#include "../memory/pmm.h"
#include "../drivers/vga/vga.h"
#include "../drivers/vesa/vesa.h"
#include "../arch/x86/cpu.h"
#include "../string/types.h"
#include "../drivers/kb/kb.h"
#include "../grub/multiboot.h"
#include "../console/fonts.h"
#include "../drivers/energy/energy.h"
#include "../arch/x86/isr.h"
#include "../memory/paging.h"
#include "../drivers/sleep/sleep.h"
#include "../drivers/pit/pit.h"
#include "../drivers/rtc/rtc.h"
#include "../grub/multiboot.h"
#include "../drivers/pci/pci.h"
#include "../drivers/pit/pit.h"
#include "../drivers/ata/ata.h"
#include "../drivers/ata/atapi.h"
#include "../console/console.h"

void dosetup(uint64 mboot_addr, uint64 kernel_end);

#endif
