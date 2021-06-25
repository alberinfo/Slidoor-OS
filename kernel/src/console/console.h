#ifndef CONSOLE_H
#define CONSOLE_H

#include "../string/types.h"
#include "../string/string.h"
#include "../drivers/vesa/vesa.h" //As of now we will only use VESA modes....
#include "fonts.h"
#include <stdarg.h>

void ConsoleInit(void);
void ClearScreen(void);
void printf(string ch, ...);
void printcolor(string str, uint32 background, uint32 foreground);
void printhexcolor(uint64 hex, uint32 backgroud, uint32 foreground);

#endif