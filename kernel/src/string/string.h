#ifndef STRING_H
#define STRING_H

#include "types.h"
#include "../arch/x86/cpu.h"

#define get_str(x) #x
#define get_get_str(x) get_str(x)
#define get_simd_mov_instruction_vex(ptr, avx) avx ? (ptr % 16 == 0 ? ("vmovdqa") : ("vmovdqu")) : (ptr % 16 == 0 ? ("movdqa") : ("movdqu"))

char *base_convert(uint64 number, int base);
void *faster_memcpy(void * _dest, const void *_src, uint32 _n);
void faster_memset(void *_s, uint32 _c, uint32 _n);
int memcmp(const void *_s1, const void *_s2, uint32 _n);
void *memcpy(void * _dest, void *_src, uint32 _n);
void* memmove(void* dstptr, const void* srcptr, uint32 uint32);
void *memset(void *_s, int _c, uint32 _n);
int memcmp_fast(const void *_s1, const void *_s2, uint32 _n);
void *memcpy_fast(volatile void *_dest, volatile void *_src, uint32 _n);
void memzero(void *_src, uint64 _n);

inline void memset_fast(void *_s, uint64 _c, uint32 _n)
{
    while(_n)
    {

		if(_n >= 8) {
    		*(uint64*)_s = _c;
    		_s += 8;
    		_n -= 8;
    	} else if(_n >= 8) {
    		*(uint32*)_s = _c;
    		_s += 4;
    		_n -= 4;
    	} else if(_n >= 2) {
    		*(uint16*)_s = _c;
    		_s += 2;
    		_n -= 2;
    	} else {
    		*(uint8*)_s++ = _c;
    		_n--;
    	}
    }
}

void* memmove_fast(void* dstptr, const void* srcptr, uint32 uint32);
uint32 strlen(const char *_s);
int strcmp(const char *_s1, const char *_s2);
int strcmpx(const char *_s1, const char *_s2);
int strncmp(const char *_s1, const char *_s2, uint32 _n);
char *strcpy(char *_dest, const char *_src);
char *strncpy(char *_dest, const char *_src, int uint32);
char *strcat(char *_dest, const char *_src);
int strcmpy(const char *c1, const char *c2);
char *strchr(const char *_s, int _c);
uint32 strspn(const char *_s, const char *_accept);
uint32 strcspn(const char *_s, const char *_reject);
char *strtok(char *_s, const char *_delim);
char *strstr(const char *_haystack, const char *_needle);
uint32 stroccr(char* str, const char c);
uint16 strlength(string ch);
uint8 strEql(string ch1,string ch2);

#endif
