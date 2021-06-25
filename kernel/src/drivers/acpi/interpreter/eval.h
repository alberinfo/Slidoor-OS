#ifndef ACPI_EVAL_H
#define ACPI_EVAL_H

#include "../acpi.h"
#include "opcode.h"
#include "namespace.h"

void AcpiEvalAML(uint8 *ptr, uint32 size);

#endif