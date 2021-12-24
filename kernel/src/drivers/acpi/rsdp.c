#include "rsdp.h"

uint32 *acpiCheckRSDPtr(uint32 *ptr)
{
   char *sig = "RSD PTR";
   struct RSDP *rsdp = (struct RSDP*) ptr;
   volatile uint8 *bptr;
   uint8 check = 0;
   uint32 i;
   if(memcmp(sig, rsdp, 7) == 0)
   {
      // check RSPD's checksum
      bptr = (uint8*) ptr;
      for (i=0; i<sizeof(struct RSDP); i++)
      {
         check += *bptr;
         bptr++;
      }
      if(check != 0) //Acpi 1.0 checking wont work for acpi 2.0 and newer.
      {
         check = 0;
         bptr = (uint8*)ptr;
         for(i = 0; i < sizeof(struct RSDP2); i++)
         {
            check += *bptr;
            bptr++; 
         }
      }
      //found valid RSDP
      if (check == 0)
      {
          acpi_pm_info->Revision = rsdp->Revision;
          if (rsdp->Revision == 0)
          {
            return (uint32*) rsdp->RsdtAddress;
          } else {
            struct RSDP2 *rsdp2 = (struct RSDP2*) ptr;
            return (uint32*) rsdp2->XsdtAddress;
          }
      }
   }
   return NULL;
}

uint32 *acpiGetRSDPtr(void)
{
   uint32 *rsdp = NULL;
   acpi_pm_info = kmalloc(sizeof(struct acpi_pm_info_t));
   
   //Try using multiboots given rsdp
   rsdp = ((struct multiboot_tag_acpi*)get_mboot_info(multiboot_tag_TYPE_ACPI_OLD))->rsdp; //It does not really matter if we use type old or type new
   if(acpiCheckRSDPtr(rsdp) != NULL)
   {
      return acpiCheckRSDPtr(rsdp);
   }
   
   //Maybe multiboot is not good enough. Lets try to search it ourselves (and as may be usless as well, but whatever)
   for(uint8 *addr = 0xE0000 + 0xFFFF800000000000; (uint64) addr < 0x100000 + 0xFFFF800000000000; addr++)
   {
      rsdp = acpiCheckRSDPtr(addr);
      if (rsdp != NULL) return rsdp;
   }
   printf("[INFO] No RSD PTR found\n");
   return NULL;
}