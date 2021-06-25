#include "rsdt.h"

int acpiParseRSDT(uint32 *ptr)
{
   bool parsed_facp = false;
   ptr = (uint64)0xFFFF800000000000 + (uint32)ptr;
   // check if address is correct  ( if acpi is available on this pc )
   if (acpiCheckHeader(ptr, "RSDT") == 0 || acpiCheckHeader(ptr, "XSDT") == 0)
   {
      // the RSDT contains an unknown number of pointers to acpi tables
      int entrys = *(ptr + 1);
      entrys = (entrys-36) / 4;
      ptr += 9;   // skip header information
      while (0<entrys--)
      {
         if(acpiCheckHeader((uint64)*ptr + 0xFFFF800000000000, "APIC") == 0) {
            acpiParseMadt(ptr);
         } else if(acpiCheckHeader((uint64)*ptr + 0xFFFF800000000000, "HPET") == 0) {
            acpiParseHpet(ptr);
         } else if(acpiCheckHeader((uint64)*ptr + 0xFFFF800000000000, "FACP") == 0) {
            parsed_facp = acpiParseFacp(ptr);
         } else if(acpiCheckHeader((uint64)*ptr + 0xFFFF800000000000, "SSDT") == 0) {
            acpiParseDSDT((uint64)*ptr + 0xFFFF800000000000);
         } else if(acpiCheckHeader((uint64)*ptr + 0xFFFF800000000000, "MCFG") == 0) {
            acpiParsePCIe(ptr);
         }
         ptr++;
      }
      if(parsed_facp == 0) printf("[INFO] No valid FACP present\n");
   } else {
      printf("[INFO] No ACPI present\n");
   }
   return parsed_facp;
}