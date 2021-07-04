#include "dsdt.h"

//this func also supports SSDT parsing, since they're pretty much the same structure

bool acpiParseDSDT(uint32 *ptr)
{
	char* packagePtr = ((char*)ptr + 36); //The first 36 bytes are not aml encoded, but normal DSDT header info.
    int dsdtLength = (*(uint32*)((char*)ptr + 4)) - 36;
    
    AcpiEvalAML(packagePtr, dsdtLength); //Lets parse this table!

    setRTCenturyReg(acpi_pm_info->facp->Century);
    acpi_pm_info->SLP_EN = 1<<13;
    acpi_pm_info->SCI_EN = 1;
	return true; //Assuming its ok. Might want to do a check (if so, how?).
}