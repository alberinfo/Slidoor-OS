#include "acpi.h"

// checks for a given header and validates checksum
int acpiCheckHeader(uint32 *ptr, char *sig)
{
    if(memcmp(ptr, sig, 4) == 0)
        return 0;
    return -1;
}

int acpiEnable(void)
{
    // check if acpi can be enabled
    if (acpi_pm_info->facp->SMI_CommandPort != 0 && acpi_pm_info->facp->AcpiEnable != 0)
    {
        outportb((uint32) acpi_pm_info->facp->SMI_CommandPort, acpi_pm_info->facp->AcpiEnable); // send acpi enable command
        // give 3 seconds time to enable acpi
        uint16 i = 0;
        for (; i<300; i++ )
        {
            if ( (inportw((uint32) acpi_pm_info->facp->PM1aControlBlock) & acpi_pm_info->SCI_EN) & 1 ) break;
            if(acpi_pm_info->facp->PM1bControlBlock != 0)
            {
                if ( (inportw((uint32) acpi_pm_info->facp->PM1bControlBlock) & acpi_pm_info->SCI_EN) & 1 ) break;
            }
            sleep(10, SleepMili); //10 Miliseconds per each try
        }
        if (i<300)
        {
            AcpiEnablePWR_SLPBTN();
            return 0;
        } else {
            printf("[INFO] Couldn't enable ACPI\n");
            return -1;
        }
    } else {
         printf("[INFO] No known way to enable ACPI.\n");
         return -1;
    }
    return 0;
}

void AcpiEnablePWR_SLPBTN() /*Acpi enable power and/or sleep button*/
{
    if((acpi_pm_info->facp->Flags & 1 << 4) /*PWRBTN*/ == 0)
    {
        //Enable
        outportw(acpi_pm_info->facp->PM1aEventBlock + acpi_pm_info->facp->PM1EventLength / 2, inportw(acpi_pm_info->facp->PM1aEventBlock + acpi_pm_info->facp->PM1EventLength / 2) | 1 << 8 /*PWRBTN_EN*/);
        if(acpi_pm_info->facp->PM1bEventBlock)
        {
          outportw(acpi_pm_info->facp->PM1bEventBlock + acpi_pm_info->facp->PM1EventLength / 2, inportw(acpi_pm_info->facp->PM1bEventBlock + acpi_pm_info->facp->PM1EventLength / 2) | 1 << 8 /*PWRBTN_EN*/);
        }
    }
    if((acpi_pm_info->facp->Flags & 1 << 5) /*SLPBTN*/ == 0)
    {
        //Enable
        outportw(acpi_pm_info->facp->PM1aEventBlock + acpi_pm_info->facp->PM1EventLength / 2, inportw(acpi_pm_info->facp->PM1aEventBlock + acpi_pm_info->facp->PM1EventLength / 2) | 1 << 9 /*SLPBTN_EN*/);
        if(acpi_pm_info->facp->PM1bEventBlock)
        {
          outportw(acpi_pm_info->facp->PM1bEventBlock + acpi_pm_info->facp->PM1EventLength / 2, inportw(acpi_pm_info->facp->PM1bEventBlock + acpi_pm_info->facp->PM1EventLength / 2) | 1 << 9 /*SLPBTN_EN*/);
        }
    }
    return;
}

int initAcpi(void)
{
    AcpiInitNamespace();
    uint32 *rsdp = acpiGetRSDPtr();
    if(rsdp == 0) return -1;
    int stat = acpiParseRSDT(rsdp); //RSDP Contains a pointer to RSDT
    if(stat == 0) return -1;
    //AcpiDumpNamespace();
    return acpiEnable();
}

void AcpiSCIHandler(void)
{
    if(inportw(acpi_pm_info->facp->PM1aEventBlock) & 1 << 8) //Has PWRBTN been pressed?
    {
        outportw(acpi_pm_info->facp->PM1aEventBlock, inportw(acpi_pm_info->facp->PM1aEventBlock) | 1 << 8); //Acknoledge
        shutdown();
    }
}

void acpiPowerOff(void)
{
    // SCI_EN is set to 1 if acpi shutdown is possible
    if(acpi_pm_info->SCI_EN == 0) return;
    struct AcpiNamespaceBlock_t *S5_Node = AcpiWalkNamespace("\\_S5_");

    uint8 *S5_Data = S5_Node->addr+1; //Lets point directly to the info, we already know whats in the packet (hoping its a packet, i think it as School-R-Lea that said it could just as well be a method so...)
    
    uint8 *S5_SLPYP = kmalloc(2); //a,b
    if (*S5_Data == 0x0A) S5_Data++;   // skip byteprefix
    S5_SLPYP[0] = *S5_Data;
    S5_Data++;
    if (*S5_Data == 0x0A) S5_Data++;   // skip byteprefix
    S5_SLPYP[1] = *S5_Data;
    // send the shutdown command
    outportw(acpi_pm_info->facp->PM1aControlBlock, S5_SLPYP[0] << 10 | acpi_pm_info->SLP_EN);
    if(acpi_pm_info->facp->PM1bControlBlock != 0)
    {
        outportw(acpi_pm_info->facp->PM1bControlBlock, S5_SLPYP[1] << 10 | acpi_pm_info->SLP_EN);
    }
}

void acpiReboot(void)
{
    if(acpi_pm_info->Revision >= 2 && acpi_pm_info->facp->Flags & (1 << 10)/*10th bit*/)
    {
        if(acpi_pm_info->facp->ResetReg.AddressSpace == 0) //The address is part of the memory space
        {
        	uint8* resaddr = acpi_pm_info->facp->ResetReg.Address;
        	id_vmmap(resaddr, 1024, 3);
        	*resaddr = acpi_pm_info->facp->ResetValue;
        } else if(acpi_pm_info->facp->ResetReg.AddressSpace == 1) { //The address is part of the I/O space
        	outportb(acpi_pm_info->facp->ResetReg.Address, acpi_pm_info->facp->ResetValue);
        } else if(acpi_pm_info->facp->ResetReg.AddressSpace == 2) { //The address is part of the PCI config space
        	pciWrite8(acpi_pm_info->facp->ResetReg.Address, acpi_pm_info->facp->ResetValue); //NOTE:THIS IS WRONG.\
        	we should write to the bus number 0, etc etc.
        }
    }
    printf("ACPI reboot failed.\n");
    return;
}