#ifndef RSDT_H
#define RSDT_H

#include "acpi.h"

struct RSDT
{
  struct ACPI_SDTHeader_t h;
  uint32 *PointerToOtherSDT;//[(h.Length - sizeof(h)) / 4];
} __attribute__((packed));

int acpiParseRSDT(uint32 *ptr);

#endif