#include "dsdt.h"

/*                          */
/*------- DEPRECATED -------*/
/*                          */

/*bool acpiParseSx(char *ptr, struct ACPI_Sx_t *Sx)
{
    // check for valid AML structure
    if((*(ptr-1) == 0x08 || (*(ptr-2) == 0x08 && *(ptr-1) == '\\')) && *(ptr+4) == 0x12 )
    {
        ptr += 5;
        ptr += ((*ptr &0xC0)>>6) +2;   // calculate PkgLength size
        if (*ptr == 0x0A) ptr++;   // skip byteprefix
        Sx->SLPYPa = *(ptr)<<10;
        ptr++;
        if (*ptr == 0x0A) ptr++;   // skip byteprefix
        Sx->SLPYPb = *(ptr)<<10;
        return true; //Sx has been parsed correctly
    }
    return false; //Sx hasn't been parsed correctly
}*/

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