#include "hpet.h"

#define HpetCapabilitiesReg 0
#define HpetConfigReg 0x10
#define HpetIntStatusReg 0x20
#define HpetMainCounterReg 0xF0
#define HpetTimerConfigCapReg(n) (0x100 + 0x20 * n)
#define HpetTimerComparatorVal(n) (0x108 + 0x20 * n)
#define HpetFSBIntRouteReg(n) (0x110 + 0x20 * n)

uint64 HpetAddr = 0;
uint64 CounterClockPeriod = 0;

static inline uint64 HpetReadMMIO(uint32 offset)
{
	return *(uint64*)(HpetAddr + offset);
}

static inline void HpetWriteMMIO(uint32 offset, uint64 value)
{
	*(uint64*)(HpetAddr + offset) = value;
}

void EnableHpet()
{
	uint64 config = HpetReadMMIO(HpetConfigReg);
	config |= 1 << 0 | 1 << 1; //Overall enable and legacy replacement bit
	HpetWriteMMIO(HpetConfigReg, config);
}

void DisableHpet()
{
	uint64 config = HpetReadMMIO(HpetConfigReg);
	config &= ~(1 << 0); //Overall enable (but zeroed :/)
	HpetWriteMMIO(HpetConfigReg, config);
}

void StartHpet()
{
	pitDisable();
	HpetWriteMMIO(HpetMainCounterReg, 0); //Clear main counter
	EnableHpet();
	ChangeTimer("HPET");
}

void acpiParseHpet(uint32 *ptr)
{
	/*struct HPET *hpet = (struct HPET*)(*ptr + 0xFFFF800000000000);
	HpetAddr = hpet->Address.Address;
	uint64 *addr = HpetAddr;
	id_vmmap(addr,2048,3);
	CounterClockPeriod = HpetReadMMIO(HpetCapabilitiesReg) >> 32;
	StartHpet(); //Until here, Hpet will start working but no IRQ's will be generated\
	since no comparator has been set up*/
}

bool HpetSleeping = false;

void HpetHandler()
{
	HpetSleeping = false; //If we have an hpet int, then we finished sleeping (since we use one-shot mode)
}

void HpetSleep(uint64 time, uint8 type)
{
	uint64 actualTime = 0;
	if(type == SleepFemto)
	{
		actualTime = time;
	} else if(type == SleepNano) {
		actualTime = time * 1000000; //Nanosec to Femtosec
	} else if(type == SleepMicro) {
		actualTime = time * 1000000 * 1000; //Microsec to Nanosec to Femtosec
	} else if(type == SleepMili) {
		actualTime = time * 1000000 * 1000 * 1000; //Milisec to Microsec to Nanosec to Femtosec 
	}
	if(actualTime < CounterClockPeriod)
	{
		actualTime = CounterClockPeriod; //Bc why not
	}
	HpetWriteMMIO(HpetTimerConfigCapReg(0), (2 /*IoApic irq 2*/ << 9) | (1 << 2) /*Irq Enable interrupt*/);
	HpetWriteMMIO(HpetTimerComparatorVal(0), HpetReadMMIO(HpetMainCounterReg) + actualTime / CounterClockPeriod);
	HpetSleeping = true;
	while(HpetSleeping) asm volatile("hlt"); //Wait until next interrupt
	return;
}