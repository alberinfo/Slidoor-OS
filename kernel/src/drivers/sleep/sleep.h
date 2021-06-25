#ifndef SLEEP_H
#define SLEEP_H

#define SleepFemto 0 //Smallest
#define SleepNano 1
#define SleepMicro 2
#define SleepMili 3

#include "../../string/types.h"
#include "../pit/pit.h"
#include "../../arch/x86/lapic.h"

void ChangeTimer(string val);
string getUsedTimer();
void sleep(uint64 time, uint8 type);

#endif
