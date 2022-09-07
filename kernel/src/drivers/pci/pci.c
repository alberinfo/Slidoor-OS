#include "pci.h"

#define CONFIG_ADDR 0xCF8
#define CONFIG_DATA 0xCFC

uint32 pciRead32(uint32 addr);
uint16 pciRead16(uint32 addr);
uint8 pciRead8(uint32 addr);
void pciWrite32(uint32 addr, uint32 value);
void pciWrite16(uint32 addr, uint16 value);
void pciWrite8(uint32 addr, uint8 value);
void ReadConfigData(struct PciDevice_t *PciDevice, uint32 address);
void CheckDevice(uint8 bus, uint8 device);
void CheckFunction(uint8 bus, uint8 device, uint8 function);
void CheckBus(uint8 bus);

uint32 pciRead32(uint32 addr)
{
    outportl(CONFIG_ADDR, addr);
    uint32 data = inportl(CONFIG_DATA);
    return data;
}

uint16 pciRead16(uint32 addr)
{
    outportl(CONFIG_ADDR, addr);
    uint32 data = inportl(CONFIG_DATA);
    return data & ((1 << 16)-1);
}

uint8 pciRead8(uint32 addr)
{
    outportl(CONFIG_ADDR, addr);
    uint32 data = inportl(CONFIG_DATA);
    return data & ((1 << 8) - 1);
}

void pciWrite32(uint32 addr, uint32 value)
{
    outportl(CONFIG_ADDR, addr);
    outportl(CONFIG_DATA, value);
}

void pciWrite16(uint32 addr, uint16 value)
{
    outportl(CONFIG_ADDR, addr);
    outportw(CONFIG_DATA, value);
}

void pciWrite8(uint32 addr, uint8 value)
{
    outportl(CONFIG_ADDR, addr);
    outportb(CONFIG_DATA, value);
}

void ReadConfigData(struct PciDevice_t *PciDevice, uint32 address)
{
    address &= ~(0xFF);
    int offset = 0;
    uint32 tmp = pciRead32(address | offset); //(31:16) Device ID, (15:0) Vendor ID
    offset += 4;
    PciDevice->VendorID = (uint16)tmp; //Lower 16Bits
    PciDevice->DeviceID = (uint16)(tmp >> 16); //Higher 16Bits
    tmp = pciRead32(address | offset); //(31:16) Status, (15:0) Command
    offset += 4;
    PciDevice->Command = (uint16)tmp; //Lower 16Bits
    PciDevice->Status = (uint16)(tmp >> 16); //Higher 16Bits
    tmp = pciRead32(address | offset); //(31:24) Class, (23:16) SubClass, (15:8) Prog IF, (7:0) Rev ID
    offset += 4;
    PciDevice->RevisionID = (uint8)tmp; //First byte
    PciDevice->ProgIF = (uint8)(tmp >> 8); //Second byte
    PciDevice->SubClass = (uint8)(tmp >> 16); //Third byte
    PciDevice->Class = (uint8)(tmp >> 24); //Fourth byte
    tmp = pciRead32(address | offset); //(31:24) BIST, (23:16) Header Type, (15:8) Latency timer, (7:0)Cache line size
    offset += 4;
    PciDevice->CacheLineSize = (uint8)tmp; //First byte
    PciDevice->LatencyTimer = (uint8)(tmp >> 8); //Second byte
    PciDevice->HeaderType = (uint8)(tmp >> 16); //Third byte
    PciDevice->BIST = (uint8)(tmp >> 24); //Fourth byte

    if((PciDevice->HeaderType & ~(0b01111111)) /*mask bit 7 (device is multifunc)*/ == 0)
    {
        for(int i = 0; i < 6; i++) //BARs
        {
            PciDevice->PciDefaultHeader.BAR[i] = pciRead32(address + offset);
            offset += 4;
        }
        PciDevice->PciDefaultHeader.CardbusCISPointer = pciRead32(address | offset); //Offset was already incremented in BAR parsing
        offset += 4;
        tmp = pciRead32(address | offset);
        offset += 4;
        PciDevice->PciDefaultHeader.SubsystemID = (uint16)(tmp >> 16); //Higher 16Bits
        PciDevice->PciDefaultHeader.SubsystemVendorID = (uint16)tmp; //Lower 16Bits
        PciDevice->PciDefaultHeader.ExpansionRomBAR = pciRead32(address | offset);
        offset += 4;
        //There should be a reserved thing, so we just aint fill it
        tmp = pciRead32(address | offset);
        offset += 8; //The next field is reserved, so we pass on to the second next one :D
        PciDevice->PciDefaultHeader.CapabilitiesPointer = (uint8)tmp;
        tmp = pciRead32(address | offset);
        PciDevice->PciDefaultHeader.MaxLatency = (uint8)(tmp >> 24);
        PciDevice->PciDefaultHeader.MinGrant = (uint8)(tmp >> 16);
        PciDevice->PciDefaultHeader.InterruptPIN = (uint8)(tmp >> 8);
        PciDevice->PciDefaultHeader.InterruptLine = (uint8)tmp;
    } else if((PciDevice->HeaderType & ~(0b01111111)) /*mask bit 7 (device is multifunc)*/ == 1) {
        for(int i = 0; i < 2; i++)
        {
            PciDevice->PCItoPCIHeader.BAR[i] = pciRead32(address | offset);
            offset += 4;
        }
        tmp = pciRead32(address | offset); //Offset was already incremented in BAR parsing
        offset += 4;
        PciDevice->PCItoPCIHeader.SecondaryLatencyTimer = (uint8)(tmp >> 24);
        PciDevice->PCItoPCIHeader.SubordinateBusNumber = (uint8)(tmp >> 16);
        PciDevice->PCItoPCIHeader.SecondaryBusNumber = (uint8)(tmp >> 8);
        PciDevice->PCItoPCIHeader.PrimaryBusNumber = (uint8)tmp;
        tmp = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoPCIHeader.SecondaryStatus = (uint16)(tmp >> 16);
        PciDevice->PCItoPCIHeader.IOLimit = (uint8)(tmp >> 8);
        PciDevice->PCItoPCIHeader.IOBase = (uint8)tmp;
        tmp = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoPCIHeader.MemoryLimit = (uint16)(tmp >> 16);
        PciDevice->PCItoPCIHeader.MemoryBase = (uint16)tmp;
        tmp = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoPCIHeader.PrefetchMemoryLimit = (uint16)(tmp >> 16);
        PciDevice->PCItoPCIHeader.PrefetchMemoryBase = (uint16)tmp;
        PciDevice->PCItoPCIHeader.PrefetchBaseUpper = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoPCIHeader.PrefetchLimitUpper = pciRead32(address | offset);
        offset += 4;
        tmp = pciRead32(address | offset);
        offset += 8; //Next entry is reserved, so we go to the second next :D
        PciDevice->PCItoPCIHeader.IOLimitUpper = (uint16)(tmp >> 16);
        PciDevice->PCItoPCIHeader.IOBaseUpper = (uint16)tmp;
        tmp = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoPCIHeader.CapabilityPointer = (uint8)tmp;
        PciDevice->PCItoPCIHeader.ExpansionRomBAR = pciRead32(address | offset);
        offset += 4;
        tmp = pciRead32(address | offset);
        PciDevice->PCItoPCIHeader.BridgeControl = (uint16)(tmp >> 16);
        PciDevice->PCItoPCIHeader.InterruptPin = (uint8)(tmp >> 8);
        PciDevice->PCItoPCIHeader.InterruptLine = (uint8)tmp;
    } else {
        PciDevice->PCItoCardbus.CardBusBAR = pciRead32(address | offset);
        offset += 4;
        tmp = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoCardbus.SecondaryStatus = (uint16)(tmp >> 16);
        PciDevice->PCItoCardbus.CapabilitesOffset = (uint8)tmp;
        tmp = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoCardbus.CardbusLatencyTimer = (uint8)(tmp >> 24);
        PciDevice->PCItoCardbus.SubordinateBusNumber = (uint8)(tmp >> 16);
        PciDevice->PCItoCardbus.CardbusBusNumber = (uint8)(tmp >> 8);
        PciDevice->PCItoCardbus.PciBusNumber = (uint8)tmp;
        PciDevice->PCItoCardbus.MemoryBase0 = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoCardbus.MemoryLimit0 = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoCardbus.MemoryBase1 = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoCardbus.MemoryLimit1 = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoCardbus.IOBar0 = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoCardbus.IOLimit0 = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoCardbus.IOBar1 = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoCardbus.IOLimit1 = pciRead32(address | offset);
        offset += 4;
        tmp = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoCardbus.BridgeControl = (uint16)(tmp >> 16);
        PciDevice->PCItoCardbus.InterruptPin = (uint8)(tmp >> 8);
        PciDevice->PCItoCardbus.InterruptLine = (uint8)tmp;
        tmp = pciRead32(address | offset);
        offset += 4;
        PciDevice->PCItoCardbus.SubsystemVendorID = (uint16)(tmp >> 16);
        PciDevice->PCItoCardbus.SubsystemDeviceID = (uint16)tmp;
        PciDevice->PCItoCardbus.LegacyBAR = pciRead32(address | offset);
    }
}

void CheckDevice(uint8 bus, uint8 device)
{
    uint8 function = 0;
    struct PciDevice_t PciDevice;
    PciDevice.VendorID = pciRead32(0x80000000 | (bus << 16) | (device << 11)) & 0xFFFF;
    if(PciDevice.VendorID == 0xFFFF) return;
    for(uint8 function = 0; function < 8 && PciDevice.VendorID != 0xFFFF; function++)
    {
        CheckFunction(bus, device, function);
    }
}

void CheckBus(uint8 bus)
{
    for(uint8 device = 0; device < 32; device++)
    {
        CheckDevice(bus, device);
    }
}

void CheckFunction(uint8 bus, uint8 device, uint8 function)
{
    PciDevices[lastPciDevice] = kmalloc(sizeof(struct PciDevice_t));

    uint32 address = 0x80000000 | (bus << 16) | ((device & 0x1F) << 11) | ((function & 7) << 8);
    ReadConfigData(PciDevices[lastPciDevice], address);

    if(PciDevices[lastPciDevice]->VendorID == 0xFFFF || PciDevices[lastPciDevice]->VendorID == 0x0000)
    {
        free(PciDevices[lastPciDevice]);
        return;
    }
    
    PciDevices[lastPciDevice]->Bus = bus;
    PciDevices[lastPciDevice]->Device = device;
    PciDevices[lastPciDevice]->Function = function;
    PciDevices[lastPciDevice]->MMIO = false; //We will say false, until MCFG says otherwise
    PciDevices[lastPciDevice]->Address = address;

    //Here we will check whatever pci device we want to check
    if(PciDevices[lastPciDevice]->Class == 1 && PciDevices[lastPciDevice]->SubClass == 1)
    {
        pciWrite16(address | 4, 5); //Enable I/O Flag & Bus master Enable flag on channel 0
        pciWrite16(address | 5, 5); //Enable I/O Flag & Bus master Enable flag on channel 5

        init_ata(PciDevices[lastPciDevice]->PciDefaultHeader.BAR[4] & 0xFFFFFFFC);//Initialize queue,etc but now we provide the busmaster information
    }

    //End of checking :)
    lastPciDevice++;
    if(PciDevices[lastPciDevice]->Class == 0x6 && PciDevices[lastPciDevice]->SubClass == 0x9) //PCI 2 PCI Bridge
    {
        CheckBus(PciDevices[lastPciDevice]->PCItoPCIHeader.SecondaryBusNumber);
    }
}

void PciInit()
{
    lastPciDevice = 0;
    PciDevices = kmalloc(32 * 8); //Up to 32 devices per bus, 8 buses in total
    struct PciDevice_t PciDevice;
    ReadConfigData(&PciDevice, 0);
    if(!(PciDevice.HeaderType & 0x80)) //Single Pci host Controller
    {
        CheckBus(0);
    } else { //Multiple Pci host controllers
        for(uint32 function = 0; function < 8; function++)
        {
            if(pciRead32(0x80000000 | (function << 8)) == 0xFFFF) break;
            CheckBus(function);
        }
    }
}
