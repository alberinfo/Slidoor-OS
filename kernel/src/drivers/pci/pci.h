#ifndef PCI_H
#define PCI_H

#include "../../arch/x86/cpu.h"
#include "../../string/types.h"
#include "../../console/console.h"

void PciInit();
/*The other functions are declared in the pci.c file, so they are private*/

int lastPciDevice;

struct PciDefaultHeader_t
{
    uint8 LatencyTimer;
    uint8 CacheLineSize;
    uint32 BAR[6];
    uint32 CardbusCISPointer;
    uint16 SubsystemID;
    uint16 SubsystemVendorID;
    uint32 ExpansionRomBAR;
    uint8 Reserved[7];
    uint8 CapabilitiesPointer;
    uint8 MaxLatency;
    uint8 MinGrant;
    uint8 InterruptPIN;
    uint8 InterruptLine;
} __attribute__((packed));

struct PCItoPCIHeader_t
{
    uint8 LatencyTimer;
    uint8 CacheLineSize;
    uint32 BAR[2];
    uint8 SecondaryLatencyTimer;
    uint8 SubordinateBusNumber;
    uint8 SecondaryBusNumber;
    uint8 PrimaryBusNumber;
    uint16 SecondaryStatus;
    uint8 IOLimit;
    uint8 IOBase;
    uint16 MemoryLimit;
    uint16 MemoryBase;
    uint16 PrefetchMemoryLimit; //Prefetchable
    uint16 PrefetchMemoryBase; //Prefetchable
    uint32 PrefetchBaseUpper;
    uint32 PrefetchLimitUpper;
    uint16 IOLimitUpper; //Upper 16Bits
    uint16 IOBaseUpper; //Upper 16Bits
    uint8 reserved[3];
    uint8 CapabilityPointer;
    uint32 ExpansionRomBAR;
    uint16 BridgeControl;
    uint8 InterruptPin;
    uint8 InterruptLine;
} __attribute__((packed));

struct PCItoCardbus_t
{
    uint8 LatencyTimer;
    uint8 CacheLineSize;
    uint32 CardBusBAR;
    uint16 SecondaryStatus;
    uint8 reserved;
    uint8 CapabilitesOffset;
    uint8 CardbusLatencyTimer;
    uint8 SubordinateBusNumber;
    uint8 CardbusBusNumber;
    uint8 PciBusNumber;
    uint32 MemoryBase0;
    uint32 MemoryLimit0;
    uint32 MemoryBase1;
    uint32 MemoryLimit1;
    uint32 IOBar0;
    uint32 IOLimit0;
    uint32 IOBar1;
    uint32 IOLimit1;
    uint16 BridgeControl;
    uint8 InterruptPin;
    uint8 InterruptLine;
    uint16 SubsystemVendorID;
    uint16 SubsystemDeviceID;
    uint32 LegacyBAR;
} __attribute__((packed));

struct PciDevice_t
{
    uint8 Bus;
    uint8 Device;
    uint8 Function;
    uint8 MMIO; //If we are/can use MMIO
    uint64 Address;
    //From here we'll have the Actual definition of the Pci fields.
    uint16 VendorID;
    uint16 DeviceID;
    uint16 Command;
    uint16 Status;
    uint8 RevisionID;
    uint8 ProgIF;
    uint8 SubClass;
    uint8 Class;
    uint8 CacheLineSize;
    uint8 LatencyTimer;
    uint8 HeaderType;
    uint8 BIST;
    struct PciDefaultHeader_t PciDefaultHeader;
    struct PCItoPCIHeader_t PCItoPCIHeader;
    struct PCItoCardbus_t PCItoCardbus; 
} __attribute__((packed));

struct PciDevice_t **PciDevices;

#endif
