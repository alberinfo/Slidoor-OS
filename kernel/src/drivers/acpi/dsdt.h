#ifndef DSDT_H
#define DSDT_H

#include "acpi.h"

bool acpiParseSx(char *ptr, struct ACPI_Sx_t *Sx);
bool acpiParseDSDT(uint32 *ptr);

#endif