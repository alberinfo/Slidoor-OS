#include "cpu.h"

char *Intel[96] = {
	"Brand ID Not Supported-", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Intel(R) Pentium(R) III Xeon(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) III processor-M", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Xeon(R) Processor", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) 4 processor-M", 
	"Mobile Intel(R) Pentium(R) Celeron(R) processor", 
	"Reserved", 
	"Mobile Genuine Intel(R) processor", 
	"Intel(R) Celeron(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Celeron(R) processor", 
	"Mobile Geniune Intel(R) processor", 
	"Intel(R) Pentium(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor"
};

/* This table is for those brand strings that have two values depending on the processor signature. It should have the same number of entries as the above table. */
char *Intel_Other[96] = {
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Celeron(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved"
};

void CPUDisableInts(void)
{
	asm volatile("cli");
}

void CPUEnableInts(void)
{
	asm volatile("sti");
}

uint8 inportb(uint16 _port)
{
    uint8 rv;
    asm volatile("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb(uint16 _port, uint8 _data)
{
	asm volatile("outb %1, %0" : : "dN" (_port), "a" (_data));
}

uint16 inportw(uint16 _port)
{
    uint16 rv;
    asm volatile("inw %1, %0" : "=a"(rv) : "dN" (_port));
    return rv;
}

void outportw(uint16 _port, uint16 _data)
{
    asm volatile("outw %1, %0" : : "dN" (_port), "a" (_data));
}

uint32 inportl(uint16 _port)
{
    uint32 rv;
    asm volatile("inl %1, %0" : "=a"(rv) : "dN" (_port));
    return rv;
}

void outportl(uint16 _port, uint32 _data)
{
    asm volatile("outl %1, %0" : : "dN" (_port), "a" (_data));
}

void rdmsr(uint32 msr, uint32 *low, uint32 *high)
{
    asm volatile("rdmsr" : "=a" (*low), "=d" (*high) : "c" (msr));
}

void wrmsr(uint32 msr, uint32 low, uint32 high)
{
    asm volatile("wrmsr" : : "a" (low), "d" (high), "c" (msr));
}


string cpuname2str(uint32 eax, uint32 ebx, uint32 ecx, uint32 edx) {
	string str = kmalloc(17);
	for(uint8 j = 0; j < 4; j++) {
		str[j] = eax >> (8 * j);
		str[j + 4] = ebx >> (8 * j);
		str[j + 8] = ecx >> (8 * j);
		str[j + 12] = edx >> (8 * j);
	}
    str[16] = '\0';
	return str;
}

void CpuIntel() {
    cpu_info.brand = "Intel";
	uint32 eax, ebx, ecx, edx, max_eax, signature, unused;
	volatile int model, family, type, brand, stepping, reserved;
	int extended_family = -1;
	cpuid(1, eax, ebx, unused, unused);
	model = (eax >> 4) & 0xf;
	family = (eax >> 8) & 0xf;
	type = (eax >> 12) & 0x3;
	brand = ebx & 0xff;
	stepping = eax & 0xf;
	reserved = eax >> 14;
	signature = eax;
	switch(type) {
		case 0:
        cpu_info.type = "Original OEM";
		break;
		case 1:
        cpu_info.type = "Overdrive";
		break;
		case 2:
        cpu_info.type = "Dual-capable";
		break;
		case 3:
        cpu_info.type = "Reserved";
		break;
	}
	switch(family) {
		case 3:
		cpu_info.family = "i386";
		break;
		case 4:
        cpu_info.family = "i486";
		break;
		case 5:
        cpu_info.family = "Pentium";
		break;
		case 6:
        cpu_info.family = "Pentium Pro";
		break;
		case 15:
		cpu_info.family = "Pentium 4";
        break;
	}
	if(family == 15) {
		extended_family = (eax >> 20) & 0xff;
        cpu_info.extended_family = extended_family;
    } else {
        cpu_info.extended_family = "Unknown";
    }
    switch(family) {
		case 3:
	    break;
		case 4:
		switch(model) {
			case 0:
			case 1:
			cpu_info.model = "DX";
			break;
			case 2:
			cpu_info.model = "SX";
			break;
			case 3:
			cpu_info.model = "487/DX2";
			break;
			case 4:
            cpu_info.model = "SL";
			break;
			case 5:
            cpu_info.model = "SX2";
			break;
			case 7:
			cpu_info.model = "Write-back enhanced DX2";
			break;
			case 8:
            cpu_info.model = "DX4";
			break;
		}
		break;
		case 5:
		switch(model) {
			case 1:
			cpu_info.model = "60/66";
			break;
			case 2:
			cpu_info.model = "75/200";
			break;
			case 3:
			cpu_info.model = "for 486 system";
			break;
			case 4:
			cpu_info.model = "MMX";
			break;
		}
		break;
		case 6:
		switch(model) {
			case 1:
            cpu_info.model = "Pentium Pro";
			break;
			case 3:
			cpu_info.model = "Pentium II Model 3";
			break;
			case 5:
			cpu_info.model = "Pentium II Model 5/Xeon/Celeron";
			break;
			case 6:
			cpu_info.model = "Celeron";
			break;
			case 7:
			cpu_info.model = "Pentium III/Pentium III Xeon - external L2 cache";
			break;
			case 8:
			cpu_info.model = "Pentium III/Pentium III Xeon - internal L2 cache";
			break;
		}
		break;
		case 15:
		break;
	}
	cpuid(0x80000000, max_eax, unused, unused, unused);
	/* Quok said: If the max extended eax value is high enough to support the processor brand string
	(values 0x80000002 to 0do_intelx80000004), then we'll use that information to return the brand information. 
	Otherwise, we'll refer back to the brand tables above for backwards compatibility with older processors. 
	According to the Sept. 2006 Intel Arch Software Developer's Guide, if extended eax values are supported, 
	then all 3 values for the processor brand string are supported, but we'll test just to make sure and be safe. */
    if(brand > 0) {
		if(brand < 0x18) {
			if(signature == 0x000006B1 || signature == 0x00000F13) {
                cpu_info.name = Intel_Other[brand];
			} else {
                cpu_info.name = Intel[brand];
			}
		} else {
			cpu_info.name = "Reserved";
		}
	} else {
        cpu_info.name = "";
		for(uint32 j = 0x80000002; j <= 0x80000004; j++) {
			cpuid(j, eax, ebx, ecx, edx);
			string tmp = cpuname2str(eax, ebx, ecx, edx);
			cpu_info.name = strcat(cpu_info.name, tmp);
			free(tmp);
		}
	}
	cpu_info.stepping = stepping;
    cpu_info.reserved = reserved;
}

/* AMD-specific information */
void CpuAmd(void) {
    cpu_info.brand = "AMD";
    cpu_info.extended_family = "Unknow";
	uint32 extended, eax, ebx, ecx, edx, unused;
	int family, model, stepping, reserved;
	cpuid(1, eax, unused, unused, unused);
	model = (eax >> 4) & 0xf;
	family = (eax >> 8) & 0xf;
	stepping = eax & 0xf;
	reserved = eax >> 12;
	switch(family) {
		case 4:
        cpu_info.family = "486 Model " + model;
		break;
		case 5:
		switch(model) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 6:
			case 7:
            cpu_info.model = "K6 Model " + model;
			break;
			case 8:
			cpu_info.model = "K6-2 Model 8";
			break;
			case 9:
			cpu_info.model = "K6-III Model 9";
			break;
			default:
			cpu_info.model = "K5/K6 Model " + model;
			break;
		}
		break;
		case 6:
		switch(model) {
			case 1:
			case 2:
			case 4:
            cpu_info.model = "Athlon Model " + model;
			break;
			case 3:
			cpu_info.model = "Duron Model 3";
			break;
			case 6:
			cpu_info.model = "Athlon MP/Mobile Athlon Model 6";
			break;
			case 7:
			cpu_info.model = "Mobile Duron Model 7";
			break;
			default:
			cpu_info.model = "Duron/Athlon Model " + model;
			break;
		}
		break;
        default:
        cpu_info.model = "Unknow";
        break;
	}
	cpuid(0x80000000, extended, unused, unused, unused);
	if(extended == 0) {
		return;
	}
    cpu_info.name = "";
	if(extended >= 0x80000002) {
		for(uint32 j = 0x80000002; j <= 0x80000004; j++) {
			cpuid(j, eax, ebx, ecx, edx);
			string tmp = cpuname2str(eax, ebx, ecx, edx);
			cpu_info.name = strcat(cpu_info.name, tmp);
			free(tmp);
		}
	}
	/*if(extended >= 0x80000007) {
		cpuid(0x80000007, unused, unused, unused, edx);
		if(edx & 1) {
			print("Temperature Sensing Diode Detected!");
		}
	}*/
    cpu_info.stepping = stepping;
    cpu_info.reserved = reserved;
}

/* Simply call this function detect_cpu(); */
void detectCpu() { /* or main() if your trying to port this as an independant application */
	uint32 ebx, unused;
	cpuid(0, unused, ebx, unused, unused);
	switch(ebx) {
		case 0x756e6547: /* Intel Magic Code */
        CpuIntel();
		break;
		case 0x68747541: /* AMD Magic Code */
		CpuAmd();
		break;
		default: ;
		cpu_info.brand = "Unknown";
        cpu_info.type = "Unknown";
        cpu_info.family = "Unknown";
        cpu_info.extended_family = "Unknown";
        cpu_info.model = "Unknown";
        cpu_info.stepping = 0;
        cpu_info.reserved = 0;
		break;
	}
	//Check AVX Support (technically its already enabled, but we did not pass that info to the kern so...)
	uint32 eax = 0, ecx = 0;
	cpuid(7, eax, ebx, ecx, unused);
	ebx &= (1 << 16); //AVX512F
	if(ebx)
	{
		cpu_info.AVX = 3;
		return;
	}
	eax ^= eax; ebx ^= ebx; ecx ^= ecx;
	cpuid(7, eax, ebx, ecx, unused);
	ebx &= (1 << 5); //AVX2
	if(ebx)
	{
		cpu_info.AVX = 2;
		return;
	}
	eax ^= eax; ebx ^= ebx; ecx ^= ecx;
	cpuid(1, eax, ebx, ecx, unused);
	ecx &= (1 << 28); //AVX
	if(ecx)
	{
		cpu_info.AVX = 1;
		return;
	}
	cpu_info.AVX = 0; //SSE Only
	return;
}
