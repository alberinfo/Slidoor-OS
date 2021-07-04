#include "sleep.h"

string TimerUsed = ""; //None....

string getUsedTimer()
{
    return TimerUsed;
}

void ChangeTimer(string timer)
{
	if(TimerUsed == "") TimerUsed = kmalloc(16); 
	memset(TimerUsed, 0, 16);
    memcpy(TimerUsed, timer, strlen(timer));
}

void sleep(uint64 time, uint8 type)
{
    if(memcmp(TimerUsed, "APIC",4) == 0)
    {
        lapicTimerSleep(time, type);
    } else if(memcmp(TimerUsed, "PIT",3) == 0){
        pitSleep(time, type);
    } else if(memcmp(TimerUsed, "HPET",4) == 0) {
    	HpetSleep(time, type);
    	//Do what i gotta do
    }
}
