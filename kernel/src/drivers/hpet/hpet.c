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

void HpetEnableComparator(uint32 ComparatorNum, bool fsb, bool Enable32Bits, bool periodic, bool LevelTriggered)
{
	uint32 CompOffset = HpetTimerConfigCapReg(ComparatorNum); //Get the comparator's offset

	if(fsb && HpetReadMMIO(CompOffset) & (1 << 15)) HpetWriteMMIO(CompOffset, HpetReadMMIO(CompOffset) | (1 << 14)); //If FSB can be used (bit 15), and we want to use FSB Mapping, then enable FSB (set bit 14)
	else HpetWriteMMIO(CompOffset, HpetReadMMIO(CompOffset) & ~(1 << 14)); //Otherwise, set it off. This should be the default, but just in case.

	if(Enable32Bits && HpetReadMMIO(CompOffset) & (1 << 5)) HpetWriteMMIO(CompOffset, HpetReadMMIO(CompOffset) | (1 << 8)); //Enable 32 bit mode if we want it and the comparator supports it

	if(periodic && HpetReadMMIO(CompOffset) & (1 << 4)) HpetWriteMMIO(CompOffset, HpetReadMMIO(CompOffset) | (1 << 6)); //Enable periodic mode if we want it and the comparator supports its
	else HpetWriteMMIO(CompOffset, HpetReadMMIO(CompOffset) & ~(1 << 6)); //Otherwise make sure to leave it disabled (its not specified whether its defaulted to false or not)

	if(LevelTriggered) HpetWriteMMIO(CompOffset, HpetReadMMIO(CompOffset) | 1);
	else HpetWriteMMIO(CompOffset, HpetReadMMIO(CompOffset) & ~1);

	HpetWriteMMIO(CompOffset, HpetReadMMIO(CompOffset) | (1 << 2)); //Enable interrupt triggering
}

void StartHpet()
{
	pitDisable();
	HpetEnableComparator(0, false, false, false, false); //We will, for now, only enable the first comparator without fsb mapping, with 64-bit counter, without periodic accumulator, and edge triggered.
	EnableHpet();
	ChangeTimer("HPET");
}

void acpiParseHpet(uint32 *ptr)
{
	struct HPET *hpet = (struct HPET*)(*ptr + 0xFFFF800000000000);
	HpetAddr = hpet->Address.Address;
	uint64 *addr = HpetAddr;
	id_vmmap(addr,2048,3);
	CounterClockPeriod = HpetReadMMIO(HpetCapabilitiesReg) >> 32;
	StartHpet(); //Until here, Hpet will start working but no IRQ's will be generated\
	since no comparator has been set up
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
	} else if(type == SleepPico) {
		actualTime = time * 1000; //Picosec to Femtosec (multiply time by 1000)
	} else if(type == SleepNano) {
		actualTime = time * 1000000; //Nanosec to Femtosec (multiply nanosecs 1e6)
	} else if(type == SleepMicro) {
		actualTime = time * 1000000000; //Microsec Femtosec (multiply microsecs by 1e9)
	} else if(type == SleepMili) {
		actualTime = time * 1000000000000; //Milisec to Femtosec (multiply milisecs by 1e12) 
	}
	if(actualTime < CounterClockPeriod)
	{
		actualTime = CounterClockPeriod; //Bc why not
	}
	HpetWriteMMIO(HpetTimerConfigCapReg(0), (2 /*IoApic irq 2*/ << 9) | (1 << 2) /*Irq Enable interrupt*/);
	HpetWriteMMIO(HpetTimerComparatorVal(0), (uint64)HpetReadMMIO(HpetMainCounterReg) + (actualTime / CounterClockPeriod));
	HpetSleeping = true;
	while(HpetSleeping) asm volatile("hlt"); //Wait until next interrupt
	return;
}