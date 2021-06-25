#ifndef PIT_H
#define PIT_H

#include "../../string/types.h"
#include "../../arch/x86/cpu.h"

void pitInit(uint16 div);
void pitHandler();
void pitSleep(uint64 time, uint8 type);
void pitDisable();

#endif
