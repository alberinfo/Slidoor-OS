#ifndef SMP_H
#define SMP_H

#include "../../string/types.h"
#include "../../console/console.h"
#include "cpu.h"
#include "idt.h"
#include "lapic.h"

void _ap_main();

#endif
