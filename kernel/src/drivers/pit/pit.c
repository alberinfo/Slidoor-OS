#include "pit.h"

bool pit_sleeping = false;
uint32 pit_countdown = 0;

void pitInit(uint16 freq)
{
    outportb(0x43, 0x34); //Mode 4, lobyte/hibyte, channel 0
    uint16 div = (1193181 /*standard pit freq*/ / freq);
    outportb(0x40, div & 0xFF);
    outportb(0x40, div >> 8);
    ChangeTimer("PIT");
}

void pitDisable()
{
    outportb(0x43, 0b11000); //Irq in terminal count, lobyte/hibyte, channel 0
    uint16 div = 0xFFFF;
    outportb(0x40, div & 0xFF);
    outportb(0x40, div >> 8);
    pitSleep(1, 3); //Wait until next pit interrupt
}

void pitHandler()
{
    if(pit_sleeping)
    {
        if(pit_countdown)
        {
            pit_countdown--; //We've passed ~1 milisecs
        } else {
            pit_sleeping = false;
        }
    }
    return;
}

void pitSleep(uint64 time, uint8 type)
{
    if(type < 3) return; //With pit we can only sleep in miliseconds, sadly.... (i mean, we can do more, but not for the freq we have set up)
    pit_countdown = time;
    if(pit_countdown > 0)
    {
        pit_sleeping = true;
        while(pit_sleeping && pit_countdown) asm volatile("hlt"); //Halt CPU until next interrupt arrives
    }
    return;
}
