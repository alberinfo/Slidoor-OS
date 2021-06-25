#include "pcie.h"

void acpiParsePCIe(uint32 *ptr)
{
	struct MCFG *mcfg = (struct MCFG*) ((uint64)*ptr + 0xFFFF800000000000);
	int entries = (mcfg->h.length - 44) / 16; //The first entry is 44 byte from the start of\
	the table, and each entry is 16 bytes long
	for(int i = 0; i < entries; i++)
	{
		struct ENCHANCED_CONFIG_BAR_t *config_bar = ((uint8*)mcfg) + 44 + 16*i;
		for(int bus = config_bar->StartPCIBusNum; bus < config_bar->EndPCIBusNum; bus++)
		{
			for(int device = 0; device < 32; device++)
			{
				uint64 *MMIOAddr = config_bar->BAR + ((bus - config_bar->StartPCIBusNum) << 20 | device << 15);
				struct PciDevice_t PciDevice;
				vmmap(MMIOAddr, (uint64)MMIOAddr + 0xFFFF800000000000, 4096, 3); //One extended configuration address space is now 4K
				MMIOAddr = (uint64)MMIOAddr + 0xFFFF800000000000;
				memcpy_fast(((uint64)&PciDevice) + 8, MMIOAddr, 16); //The size of the dev info is 16 bytes
				if(PciDevice.VendorID != 0xFFFF && PciDevice.VendorID)
				{
					for(int i = 0; i < lastPciDevice; i++)
					{
						if(PciDevices[i]->Bus == bus && PciDevices[i]->Device == device && PciDevices[i]->Function == 0)
						{
							PciDevices[i]->MMIO = true;
							PciDevices[i]->Address = MMIOAddr;
							break;
						}
					}
				}
				//Mem Addr = ECAM BAR + Bus num * 0x100000 + Dev num * 0x8000 + Func num * 0x1000 + Reg offset
				//For more information, look at http://www.csit-sun.pub.ro/~cpop/Documentatie_SMP/Intel_Microprocessor_Systems/Intel_ProcessorNew/Intel%20White%20Paper/Accessing%20PCI%20Express%20Configuration%20Registers%20Using%20Intel%20Chipsets.pdf
			}
		}
	}
}