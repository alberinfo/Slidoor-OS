#include "fadt.h"

bool acpiParseFacp(uint32 *ptr)
{
    bool parsed_S5 = false;
    struct FACP *facp = (struct FACP*) ((uint64)*ptr + 0xFFFF800000000000);
    acpi_pm_info->facp = kmalloc(sizeof(struct FACP));
    memcpy_fast(acpi_pm_info->facp, facp, sizeof(struct FACP));
    if(acpi_pm_info->Revision > 1) facp->DSDT = facp->X_Dsdt;
    vmmap(facp->DSDT , facp->DSDT + 0xFFFF800000000000, 8*1024, 3);
    if (acpiCheckHeader(facp->DSDT + 0xFFFF800000000000, "DSDT") == 0)
    {
        parsed_S5 = acpiParseDSDT(facp->DSDT + 0xFFFF800000000000);
    } else {
        printf("[INFO] DSDT invalid\n");
    }
    return parsed_S5;
}