#include "kernel.h"

extern uint8 kernel_end;

void kmain()
{
    uint64 mboot_addr = 0;
    asm volatile("mov %%rbx, %0" : "=b" (mboot_addr) : :);
    dosetup(mboot_addr+0xFFFF800000000000, &kernel_end);
    printf("\nBooted with %s\n>", get_mboot_info(multiboot_tag_TYPE_BOOT_LOADER_NAME));
    last_str = "";
    end_str = 0;
    while(1)
    {
        if(end_str)
        {
            end_str = 0;
            string comm = last_str;
            if(strEql(comm, "help"))
            {
                comm += 4; //info characters
                if(comm[0] == '\0') //There's nothing specific to ask
                {
                    printf("List of comands available:\n help - Shows information about one or all commands\n shutdown - Turns off the PC\n reboot - Reboots the PC\n clear - Clears the screen\n time - Show the actual time\n");
                    printf(" info - Show information about different things in the PC\n echo - Print what you write after the command\n install $a,$b - Copies the contents of drive $a into drive $b. It is assumed that drive $a contains the operating system from which the computer has booted on.\n");
                } else {
                    print("Command not recognized. Check for the syntax or if the command is available\n");
                }
            } else if(strncmp(comm, "info", 4) == 0) {
                comm += 4;
                if(comm[0] == '\0')
                {
                    printf("Use this command to show information. All the options to 'info' are:\n");
                    printf(" cpu - Show information about the cpu\n pci - Show information about pci devices & buses\n mem - Show memory map\n disks - Show general information about present ATA Devices\n disk $n - Show extended information about disk number n\n");
                } else if(strEql(comm, " cpu")) {
                    printf("Processor Brand: %s\nProcessor Name: %s\nCores: %i\nStepping: %i\n", cpu_info.brand, cpu_info.name, acpi_pm_info->cpus, cpu_info.stepping);
                } else if(strEql(comm, " pci")) {
                    for(int i = 0; i < lastPciDevice; i++)
                    {
                        printf("Device ID:%x Vendor ID:%x Class:%x SubClass:%x Prog IF:%x\n", PciDevices[i]->DeviceID, PciDevices[i]->VendorID, PciDevices[i]->Class, PciDevices[i]->SubClass, PciDevices[i]->ProgIF);
                    }
                } else if(strEql(comm, " mem")) {
                    printf("Memory Map found:\n");
                    uint64 total_mem = 0;
                    multiboot_memory_map_t *mmapp = get_mboot_info(multiboot_tag_TYPE_MMAP);
                    for(uint64 i = 0; i < (uint64)get_mboot_info(23); i++) //Number of maps are returned as the pointer to the variable that contains the amount of maps
                    {
                        multiboot_memory_map_t *mmap = &mmapp[i];
                        printf("Address: %x Length: %iKB  Type: ", mmap->addr, mmap->len / 1024);
                        if(mmap->type == MEMORY_AVAILABLE)
                        {
                            printcolor("Free", 0, 0x1FFC00);
                            total_mem += mmap->len;
                        } else if(mmap->type == MEMORY_RESERVED) {
                            printcolor("Reserved", 0, 0xFFFFFC00);
                        } else if(mmap->type == MEMORY_ACPI_RECLAIMABLE) {
                            printcolor("ACPI Claimed", 0, 0xFFFFFC00);
                        } else if(mmap->type == MEMORY_NVS) {
                            printcolor("NVS", 0, 0xFFFFFC00);
                        } else {
                            printcolor("Corrupted", 0, 0xFFE00000);
                        }
                        printf("\n");
                    }
                    printf("Usable Memory: %iMB\n", total_mem / (1024 * 1024));
                } else if(strEql(comm, " disks")) { //All disks present
                    if(ata_devices.dev_amount == 0)
                    {
                        printf("No ATA Devices present!\n");
                    } else {
                        for(int i = 0; i < ata_devices.dev_amount; i++)
                        {
                            printf("%iMB %s %s device on ATA Bus %i\n", ata_devices.devices[i].size, ata_devices.devices[i].type, ata_devices.devices[i].slave == false ? "Master" : "Slave", ata_devices.devices[i].channel);
                        }
                    }
                } else if(strncmp(comm, " disk ", 6) == 0) { //Disk number x
                    comm += 6;
                    int number = 0;
                    for(int i = 0; comm[i]; i++)
                    {
                        number *= 10;
                        number += comm[i]-48; //Conversion to int
                    }
                    if(number >= ata_devices.dev_amount)
                    {
                        printf("The ATA device number %i does not exist.\n", number);
                    } else {
                        printf("%s %s device on bus %i\n", ata_devices.devices[number].type, ata_devices.devices[number].slave ? "Slave" : "Master", ata_devices.devices[number].channel);
                        printf("Size:%iMB\n", ata_devices.devices[number].size);
                        if(strEql(ata_devices.devices[number].type, "PATA") || strEql(ata_devices.devices[number].type, "SATA"))
                        {
                            struct ata_identify_t *info = ata_devices.devices[number].IDENTIFY_addr;
                            printf("Serial number: %s\nModel number: %s\nFirmware revision: %s\n", info->SerNum, info->ModNum, info->FirmRev);
                        } else if(strEql(ata_devices.devices[number].type, "Unknown") || strEql(ata_devices.devices[number].type, "PATAPI") || strEql(ata_devices.devices[number].type, "SATAPI")) {
                            struct ata_identify_packet_t *info = ata_devices.devices[number].IDENTIFY_addr;
                            printf("Serial number: %s\nModel number: %s\nFirmware revision: %s\n", info->SerNum, info->ModNum, info->FirmRev);
                        }
                    }
                } else {
                    printf("Command not recognized. Check for the syntax or if the command is available\n");
                }
            } else if(strncmp(comm, "echo", 4) == 0) {
                comm += 4;
                if(comm[0] != ' ')
                {
                    printf("Command not recognized. Check for the syntax or if the command is available\n");
                } else if(comm[0] == ' ' && comm[1] == '\0') {
                    printf("\n");
                } else {
                    printf("%s\n", comm+1);
                }
            } else if(strncmp(comm, "install ", 8) == 0) {
                comm += 8;
                int SourceDrive = 0, offset = 0;
                for(int i = 0; comm[i] && comm[i] != ','; i++, offset++)
                {
                    SourceDrive *= 10;
                    SourceDrive += comm[i]-48; //Conversion to int
                }

                comm += offset+1;
                int DestDrive = 0; offset = 0;
                for(int i = 0; comm[i]; i++, offset++)
                {
                    DestDrive *= 10;
                    DestDrive += comm[i]-48; //Conversion to int
                }
                comm += offset + 1;
                printf("SourceDrive: %i, DestDrive: %i\n", SourceDrive, DestDrive);
                if(strlen(comm)) printf("ERROR: Command not recognized\n");
                else if(SourceDrive > ata_devices.dev_amount || DestDrive > ata_devices.dev_amount) {
                    printf("ERROR: Disk number cannot be higher than the amount of ata drives detected by the system\n");
                } else if(SourceDrive == 0 || DestDrive == 0) {
                    printf("ERROR: Disk number cannot be lower than 1\n");
                } else {
                    uint16 *readbuf = kmalloc(1024 * 2); //1024 Words.
                    uint8 *completion = kmalloc(8);
                    uint32 install_size = ((uint64)&kernel_end - 0xFFFF800000000000) / 512;
                    for(int i = 0; i < install_size; i++)
                    {
                        ata_read(&ata_devices.devices[SourceDrive-1], i, 1, readbuf, completion);
                        while(*completion == 0);
                        *completion = 0;

                        ata_write(&ata_devices.devices[DestDrive-1], i*4, 4, readbuf, completion);
                        while(*completion == 0);
                        *completion = 0;

                        printf("\r");
                        printf("%i sectors of %i written.", i*4, install_size*4);
                    }
                    printf("\n");
                    free(readbuf);
                    free(completion);
                }
            } else if(strEql(comm, "shutdown")) {
                shutdown();
            } else if(strEql(comm, "reboot")) {
                reboot();
            } else if(strEql(comm, "clear")) {
                ClearScreen();
            } else if(strEql(comm, "time")) {
                for(int i = 2; i > 0; i--)
                {
                    printf("%i:", getRtc(i));
                }
                printf("%i  %i/%i/%i\n", getRtc(0), getRtc(3), getRtc(4), getRtc(5));
            } else if(strlen(comm)) {
                printf("ERROR: Command not recognized\n");
            }
            comm = "";
            last_str = "";
            printf("\n>");
        }
    }
}