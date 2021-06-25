#ifndef BCD__H
#define BCD__H

#include "../../arch/x86/cpu.h"

void setRTCenturyReg(uint8 value);
uint8 get_RTC_val(uint8 param);
void set_RTC_val(uint8 setVal);
int getRtc(int option);

#endif
