#ifndef KB_H
#define KB_H

#include "../../console/console.h"
#include "../../arch/x86/cpu.h"
#include "../../string/types.h"

string last_str;
int end_str;

void kbd_handler();

#endif
