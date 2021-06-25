#ifndef TYPES_H
#define TYPES_H

#include <stdarg.h>

typedef signed char int8;
typedef unsigned char uint8;

typedef signed short int16;
typedef unsigned short uint16;

typedef signed int int32;
typedef unsigned int uint32;

typedef signed long long int64;
typedef unsigned long long uint64;

typedef char* string;

typedef _Bool bool;

typedef __gnuc_va_list va_list;

#define true 1
#define false 0
#define NULL 0

//va_start, va_arg, va_end and va_copy are already defined in stdarg.h

#endif
