#include "string.h"

//#include <stddef.h>

char *base_convert(uint64 number, int base)
{
    static char letters[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char *ptr = kmalloc(64);
    ptr += 63;
    *ptr = '\0';
    do
    {
        *--ptr = letters[number % base];
        number /= base;
    } while(number);
    return ptr;
}

int memcmp(const void *_s1, const void *_s2, uint32 _n)
{
	const unsigned char *us1 = (const unsigned char *)_s1;
	const unsigned char *us2 = (const unsigned char *)_s2;
	while(_n-- != 0) {
		if(*us1 != *us2){
			return (*us1 < *us2) ? -1 : +1;
		}
		us1++;
		us2++;
	}
	return 0;
}

void *memcpy(void * _dest, void *_src, uint32 _n)
{
    volatile uint8 *sp = (volatile uint8*) _src;
    volatile uint8 *dp = (volatile uint8*) _dest;
    for(; _n != 0; _n--) {
		*(volatile uint8*)dp++ = *(volatile uint8*)sp++;
	}
	return _dest;
}

void* memmove(void* dstptr, const void* srcptr, uint32 size)
{
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	if ( dst < src )
		for ( uint32 i = 0; i < size; i++ )
			dst[i] = src[i];
	else
		for ( uint32 i = size; i != 0; i-- )
			dst[i-1] = src[i-1];
	return dstptr;
}


void *memset(void *_s, int _c, uint32 _n)
{
    volatile char *temp = (volatile char*) _s;
    for ( ; _n != 0; _n--) {
		*temp++ = _c;
	}
    return _s;
}

int memcmp_fast(const void *_s1, const void *_s2, uint32 _n)
{
	const uint32 *us1 = (const uint32 *)_s1;
	const uint32 *us2 = (const uint32 *)_s2;
	_n /= sizeof(uint32);
	while(_n-- != 0) {
		if(*us1 != *us2) return (*us1 < *us2) ? -1 : +1;
    	us1++;
		us2++;
	}
	return 0;
}

void *memcpy_fast(volatile void * _dest, volatile void *_src, uint32 _n)
{
	while(_n)
	{
		if(_n >= 1024 && cpu_info.AVX > 2)
		{
			asm("mov %0, %%rsi\n" //Start moving data around
				"mov %1, %%rdi\n"
				"vmovdqu64 (%%rsi), %%zmm0\n"
				"vmovdqu64 64(%%rsi), %%zmm1\n"
				"vmovdqu64 128(%%rsi), %%zmm2\n"
				"vmovdqu64 192(%%rsi), %%zmm3\n"
				"vmovdqu64 256(%%rsi), %%zmm4\n"
				"vmovdqu64 320(%%rsi), %%zmm5\n"
				"vmovdqu64 384(%%rsi), %%zmm6\n"
				"vmovdqu64 448(%%rsi), %%zmm7\n"
				"vmovdqu64 512(%%rsi), %%zmm8\n"
				"vmovdqu64 576(%%rsi), %%zmm9\n"
				"vmovdqu64 640(%%rsi), %%zmm10\n"
				"vmovdqu64 704(%%rsi), %%zmm11\n"
				"vmovdqu64 768(%%rsi), %%zmm12\n"
				"vmovdqu64 832(%%rsi), %%zmm13\n"
				"vmovdqu64 896(%%rsi), %%zmm14\n"
				"vmovdqu64 960(%%rsi), %%zmm15\n"
				"vmovdqu64 %%zmm0, (%%rdi)\n"
				"vmovdqu64 %%zmm1, 64(%%rdi)\n"
				"vmovdqu64 %%zmm2, 128(%%rdi)\n"
				"vmovdqu64 %%zmm3, 192(%%rdi)\n"
				"vmovdqu64 %%zmm4, 256(%%rdi)\n"
				"vmovdqu64 %%zmm5, 320(%%rdi)\n"
				"vmovdqu64 %%zmm6, 384(%%rdi)\n"
				"vmovdqu64 %%zmm7, 448(%%rdi)\n"
				"vmovdqu64 %%zmm8, 512(%%rdi)\n"
				"vmovdqu64 %%zmm9, 576(%%rdi)\n"
				"vmovdqu64 %%zmm10, 640(%%rdi)\n"
				"vmovdqu64 %%zmm11, 704(%%rdi)\n"
				"vmovdqu64 %%zmm12, 768(%%rdi)\n"
				"vmovdqu64 %%zmm13, 832(%%rdi)\n"
				"vmovdqu64 %%zmm14, 896(%%rdi)\n"
				"vmovdqu64 %%zmm15, 960(%%rdi)" : : "g" (_src), "g" (_dest));
			_dest += 1024;
			_src += 1024;
			_n -= 1024;
		} else if(_n >= 512 && cpu_info.AVX > 1) {
			if(cpu_info.AVX == 1 || cpu_info.AVX == 2)
			{
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"vmovdqu (%%rsi), %%ymm0\n"
					"vmovdqu 32(%%rsi), %%ymm1\n"
					"vmovdqu 64(%%rsi), %%ymm2\n"
					"vmovdqu 96(%%rsi), %%ymm3\n"
					"vmovdqu 128(%%rsi), %%ymm4\n"
					"vmovdqu 160(%%rsi), %%ymm5\n"
					"vmovdqu 192(%%rsi), %%ymm6\n"
					"vmovdqu 224(%%rsi), %%ymm7\n"
					"vmovdqu 256(%%rsi), %%ymm8\n"
					"vmovdqu 288(%%rsi), %%ymm9\n"
					"vmovdqu 320(%%rsi), %%ymm10\n"
					"vmovdqu 352(%%rsi), %%ymm11\n"
					"vmovdqu 384(%%rsi), %%ymm12\n"
					"vmovdqu 416(%%rsi), %%ymm13\n"
					"vmovdqu 448(%%rsi), %%ymm14\n"
					"vmovdqu 480(%%rsi), %%ymm15\n"
					"vmovdqu %%ymm0, (%%rdi)\n"
					"vmovdqu %%ymm1, 32(%%rdi)\n"
					"vmovdqu %%ymm2, 64(%%rdi)\n"
					"vmovdqu %%ymm3, 96(%%rdi)\n"
					"vmovdqu %%ymm4, 128(%%rdi)\n"
					"vmovdqu %%ymm5, 160(%%rdi)\n"
					"vmovdqu %%ymm6, 192(%%rdi)\n"
					"vmovdqu %%ymm7, 224(%%rdi)\n"
					"vmovdqu %%ymm8, 256(%%rdi)\n"
					"vmovdqu %%ymm9, 288(%%rdi)\n"
					"vmovdqu %%ymm10, 320(%%rdi)\n"
					"vmovdqu %%ymm11, 352(%%rdi)\n"
					"vmovdqu %%ymm12, 384(%%rdi)\n"
					"vmovdqu %%ymm13, 416(%%rdi)\n"
					"vmovdqu %%ymm14, 448(%%rdi)\n"
					"vmovdqu %%ymm15, 480(%%rdi)" : : "g" (_src), "g" (_dest));
			} else {
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"vmovdqu64 (%%rsi), %%zmm0\n"
					"vmovdqu64 64(%%rsi), %%zmm1\n"
					"vmovdqu64 128(%%rsi), %%zmm2\n"
					"vmovdqu64 192(%%rsi), %%zmm3\n"
					"vmovdqu64 256(%%rsi), %%zmm4\n"
					"vmovdqu64 320(%%rsi), %%zmm5\n"
					"vmovdqu64 384(%%rsi), %%zmm6\n"
					"vmovdqu64 448(%%rsi), %%zmm7\n"
					"vmovdqu64 %%zmm0, (%%rdi)\n"
					"vmovdqu64 %%zmm1, 64(%%rdi)\n"
					"vmovdqu64 %%zmm2, 128(%%rdi)\n"
					"vmovdqu64 %%zmm3, 192(%%rdi)\n"
					"vmovdqu64 %%zmm4, 256(%%rdi)\n"
					"vmovdqu64 %%zmm5, 320(%%rdi)\n"
					"vmovdqu64 %%zmm6, 384(%%rdi)\n"
					"vmovdqu64 %%zmm7, 448(%%rdi)" : : "g" (_src), "g" (_dest));
			}
			_dest += 512;
			_src += 512;
			_n -= 512;
		} else if(_n >= 256) {
			if(cpu_info.AVX == 0)
			{
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"movdqu (%%rsi), %%xmm0\n"
					"movdqu 16(%%rsi), %%xmm1\n"
					"movdqu 32(%%rsi), %%xmm2\n"
					"movdqu 48(%%rsi), %%xmm3\n"
					"movdqu 64(%%rsi), %%xmm4\n"
					"movdqu 80(%%rsi), %%xmm5\n"
					"movdqu 96(%%rsi), %%xmm6\n"
					"movdqu 112(%%rsi), %%xmm7\n"
					"movdqu 128(%%rsi), %%xmm8\n"
					"movdqu 144(%%rsi), %%xmm9\n"
					"movdqu 160(%%rsi), %%xmm10\n"
					"movdqu 176(%%rsi), %%xmm11\n"
					"movdqu 192(%%rsi), %%xmm12\n"
					"movdqu 208(%%rsi), %%xmm13\n"
					"movdqu 224(%%rsi), %%xmm14\n"
					"movdqu 240(%%rsi), %%xmm15\n"
					"movdqu %%xmm0, (%%rdi)\n"
					"movdqu %%xmm1, 16(%%rdi)\n"
					"movdqu %%xmm2, 32(%%rdi)\n"
					"movdqu %%xmm3, 48(%%rdi)\n"
					"movdqu %%xmm4, 64(%%rdi)\n"
					"movdqu %%xmm5, 80(%%rdi)\n"
					"movdqu %%xmm6, 96(%%rdi)\n"
					"movdqu %%xmm7, 112(%%rdi)\n"
					"movdqu %%xmm8, 128(%%rdi)\n"
					"movdqu %%xmm9, 144(%%rdi)\n"
					"movdqu %%xmm10, 160(%%rdi)\n"
					"movdqu %%xmm11, 176(%%rdi)\n"
					"movdqu %%xmm12, 192(%%rdi)\n"
					"movdqu %%xmm13, 208(%%rdi)\n"
					"movdqu %%xmm14, 224(%%rdi)\n"
					"movdqu %%xmm15, 240(%%rdi)" : : "g" (_src), "g" (_dest));
			} else if(cpu_info.AVX == 1 || cpu_info.AVX == 2) {
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"vmovdqu (%%rsi), %%ymm0\n"
					"vmovdqu 32(%%rsi), %%ymm1\n"
					"vmovdqu 64(%%rsi), %%ymm2\n"
					"vmovdqu 96(%%rsi), %%ymm3\n"
					"vmovdqu 128(%%rsi), %%ymm4\n"
					"vmovdqu 160(%%rsi), %%ymm5\n"
					"vmovdqu 192(%%rsi), %%ymm6\n"
					"vmovdqu 224(%%rsi), %%ymm7\n"
					"vmovdqu %%ymm0, (%%rdi)\n"
					"vmovdqu %%ymm1, 32(%%rdi)\n"
					"vmovdqu %%ymm2, 64(%%rdi)\n"
					"vmovdqu %%ymm3, 96(%%rdi)\n"
					"vmovdqu %%ymm4, 128(%%rdi)\n"
					"vmovdqu %%ymm5, 160(%%rdi)\n"
					"vmovdqu %%ymm6, 192(%%rdi)\n"
					"vmovdqu %%ymm7, 224(%%rdi)" : : "g" (_src), "g" (_dest));
			} else {

				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"vmovdqu64 (%%rsi), %%zmm0\n"
					"vmovdqu64 64(%%rsi), %%zmm1\n"
					"vmovdqu64 128(%%rsi), %%zmm2\n"
					"vmovdqu64 192(%%rsi), %%zmm3\n"
					"vmovdqu64 %%zmm0, (%%rdi)\n"
					"vmovdqu64 %%zmm1, 64(%%rdi)\n"
					"vmovdqu64 %%zmm2, 128(%%rdi)\n"
					"vmovdqu64 %%zmm3, 192(%%rdi)" : : "g" (_src), "g" (_dest));
			}
			_dest += 256;
			_src += 256;
			_n -= 256;
		} else if(_n >= 128) {
			if(cpu_info.AVX == 0)
			{
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"movdqu (%%rsi), %%xmm0\n"
					"movdqu 16(%%rsi), %%xmm1\n"
					"movdqu 32(%%rsi), %%xmm2\n"
					"movdqu 48(%%rsi), %%xmm3\n"
					"movdqu 64(%%rsi), %%xmm4\n"
					"movdqu 80(%%rsi), %%xmm5\n"
					"movdqu 96(%%rsi), %%xmm6\n"
					"movdqu 112(%%rsi), %%xmm7\n"
					"movdqu %%xmm0, (%%rdi)\n"
					"movdqu %%xmm1, 16(%%rdi)\n"
					"movdqu %%xmm2, 32(%%rdi)\n"
					"movdqu %%xmm3, 48(%%rdi)\n"
					"movdqu %%xmm4, 64(%%rdi)\n"
					"movdqu %%xmm5, 80(%%rdi)\n"
					"movdqu %%xmm6, 96(%%rdi)\n"
					"movdqu %%xmm7, 112(%%rdi)" : : "g" (_src), "g" (_dest));
			} else if(cpu_info.AVX == 1 || cpu_info.AVX == 2) {
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"vmovdqu (%%rsi), %%ymm0\n"
					"vmovdqu 32(%%rsi), %%ymm1\n"
					"vmovdqu 64(%%rsi), %%ymm2\n"
					"vmovdqu 96(%%rsi), %%ymm3\n"
					"vmovdqu %%ymm0, (%%rdi)\n"
					"vmovdqu %%ymm1, 32(%%rdi)\n"
					"vmovdqu %%ymm2, 64(%%rdi)\n"
					"vmovdqu %%ymm3, 96(%%rdi)" : : "g" (_src), "g" (_dest));
			} else {
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"vmovdqu64 (%%rsi), %%zmm0\n"
					"vmovdqu64 64(%%rsi), %%zmm1\n"
					"vmovdqu64 %%zmm0, (%%rdi)\n"
					"vmovdqu64 %%zmm1, 64(%%rdi)" : : "g" (_src), "g" (_dest));
			}
			_dest += 128;
			_src += 128;
			_n -= 128;
		} else if(_n >= 64) {
			if(cpu_info.AVX == 0)
			{
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"movdqu (%%rsi), %%xmm0\n"
					"movdqu 16(%%rsi), %%xmm1\n"
					"movdqu 32(%%rsi), %%xmm2\n"
					"movdqu 48(%%rsi), %%xmm3\n"
					"movdqu %%xmm0, (%%rdi)\n"
					"movdqu %%xmm1, 16(%%rdi)\n"
					"movdqu %%xmm2, 32(%%rdi)\n"
					"movdqu %%xmm3, 48(%%rdi)" : : "g" (_src), "g" (_dest));
			} else if(cpu_info.AVX == 1 || cpu_info.AVX == 2) {
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"vmovdqu (%%rsi), %%ymm0\n"
					"vmovdqu 32(%%rsi), %%ymm1\n"
					"vmovdqu %%ymm0, (%%rdi)\n"
					"vmovdqu %%ymm1, 32(%%rdi)" : : "g" (_src), "g" (_dest));
			} else {
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"vmovdqu64 (%%rsi), %%zmm0\n"
					"vmovdqu64 %%zmm0, (%%rdi)" : : "g" (_src), "g" (_dest));
			}
			_dest += 64;
			_src += 64;
			_n -= 64;
		} else if(_n >= 32) {
			if(cpu_info.AVX == 0)
			{
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"movdqu (%%rsi), %%xmm0\n"
					"movdqu 16(%%rsi), %%xmm1\n"
					"movdqu %%xmm0, (%%rdi)\n"
					"movdqu %%xmm1, 16(%%rdi)" : : "g" (_src), "g" (_dest));
			} else {
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"vmovdqu (%%rsi), %%ymm0\n"
					"vmovdqu %%ymm0, (%%rdi)" : : "g" (_src), "g" (_dest));
			}
			_dest += 32;
			_src += 32;
			_n -= 32;
		} else if(_n >= 16) {
			if(cpu_info.AVX == 0) //Prevent switching between AVX and SSE instructions
			{
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n"
					"movdqu (%%rsi), %%xmm0\n"
					"movdqu %%xmm0, (%%rdi)" : : "g" (_src), "g" (_dest));
			} else {
				asm("mov %0, %%rsi\n" //Start moving data around
					"mov %1, %%rdi\n" 
					"vmovdqu (%%rsi), %%xmm0\n"
					"vmovdqu %%xmm0, (%%rdi)" : : "g" (_src), "g" (_dest));
			}
			_dest += 16;
			_src += 16;
			_n -= 16;
		} else if(_n >= 8) {
			*(uint64*)_dest = *(uint64*)_src;
			_dest += 8;
			_src += 8;
			_n -= 8;
		} else if(_n >= 4) {
			*(uint32*)_dest = *(uint32*)_src;
			_dest += 4;
			_src += 4;
			_n -= 4;
		} else if(_n >= 2) {
			*(uint16*)_dest = *(uint16*)_src;
			_dest += 2;
			_src += 2;
			_n -= 2;
		} else {
			*(uint8*)_dest++ = *(uint8*)_src++;
			_n--;
		}
	}
	return _dest;
}

void memzero(void *_src, uint64 _n)
{
	if(cpu_info.AVX == 0) asm("pxor %%xmm0, %%xmm0" : : :);
	else if(cpu_info.AVX == 1) asm("vpxor %%xmm0, %%xmm0, %%xmm0" : : :);
	else if(cpu_info.AVX == 2) asm("vpxor %%ymm0, %%ymm0, %%ymm0" : : :);
	else asm("vpxorq %%zmm0, %%zmm0, %%zmm0" : : :);
	while(_n)
	{
		asm("mov %0, %%rdi" : : "g" (_src));
		if(_n >= 64 && cpu_info.AVX > 2)
		{
			asm("vmovdqu64 %%zmm0, (%%rdi)" : : :);
			_src += 64;
			_n -= 64;
		} else if(_n >= 32 && cpu_info.AVX > 0) {
			asm("vmovdqu %%ymm0, (%%rdi)" : : :);
			_src += 32;
			_n -= 32;
		} else if(_n >= 16) {
			if(cpu_info.AVX) asm("vmovdqu %%xmm0, (%%rdi)" : : :);
			else asm("movdqu %%xmm0, (%%rdi)" : : :);
			_src += 16;
			_n -= 16;
		} else if (_n >= 8) {
			*(uint64*)_src ^= *(uint64*)_src;
			_src += 8;
			_n -= 8;
		} else if(_n >= 4) {
			*(uint32*)_src ^= *(uint32*)_src;
			_src += 4;
			_n -= 4;
		} else if(_n >= 2) {
			*(uint16*)_src ^= *(uint16*)_src;
			_src += 2;
			_n -= 2;
		} else {
			*(uint64*)_src ^= *(uint64*)_src;
			_src++;
			_n--;
		}
	}
	return;
}

void* memmove_fast(void* dstptr, const void* srcptr, uint32 size)
{
	uint32* dst = (uint32*) dstptr;
	const uint32* src = (const uint32*) srcptr;
	size /= sizeof(uint32);
	if ( dst < src )
		for ( uint32 i = 0; i < size; i++ )
			dst[i] = src[i];
	else
		for ( uint32 i = size; i != 0; i-- )
			dst[i-1] = src[i-1];
	return dstptr;
}

extern inline void memset_fast(void *_s, uint64 _c, uint32 _n);

uint32 strlen(const char *_s)
{
   uint32 n;
   for(n=0; _s[n] != '\0'; n++);
   return n;
}

int strcmp(const char *_s1, const char *_s2)
{
    for(; *_s1 == *_s2; ++_s1, ++_s2) {
        if(*_s1 == 0) {
            return 0;
		}
	}
    return *(unsigned char *)_s1 < *(unsigned char *)_s2 ? -1 : 1;
}

int strcmpx(const char *_s1, const char *_s2)
{
    for(; *_s1 == *_s2 || *_s1 - 32 == *_s2 || *_s1 == *_s2 - 32; ++_s1, ++_s2) {
        if(*_s1 == 0) {
            return 0;
		}
	}
    return *(unsigned char *)_s1 < *(unsigned char *)_s2 ? -1 : 1;
}

int strncmp(const char *_s1, const char *_s2, uint32 _n)
{
	unsigned char uc1, uc2;
	if (_n==0)
		return 0;
	while (_n-- > 0 && *_s1 == *_s2) {
		if (_n==0 || *_s1 == '\0' ) {
			return 0;
		}
		_s1++;
		_s2++;
	}
	uc1 = (*(unsigned char *) _s1);
	uc2 = (*(unsigned char *) _s2);
	return ((uc1 < uc2) ? -1 : (uc1 > uc2));
}

char *strcpy(char *_dest, const char *_src)
{
    do {
      *_dest++ = *_src++;
    } while (*_src != 0);
	*_dest = '\0';
	return _dest;
}

char *strncpy(char *_dest, const char *_src, int size)
{
    do {
      *_dest++ = *_src++;
    } while (--size);/*/
  for(int i = 0; i < size; i++)
  {
    *_dest++ = *_src++;
  }//*/
  *_dest = '\0';
	return _dest;
}

char *strcat(char *_dest, const char *_src)
{
   uint32 n = strlen(_dest);
   strcpy(_dest + n, _src);
   return _dest;
}

int strcmpy(const char *c1, const char *c2)
{
    uint32 buff=0;
    for(uint32 i=0;i<=strlen(c1);i++)
    {
        for(uint32 j=0;j<strlen(c2);j++)
        {
            if(c1[i+j]==c2[j])
            {
                buff+=1;
            }
        }
        if(buff==strlen(c2))
            return 0;
        else buff=0;
    }
    return 1;
}

char *strchr(const char *_s, int _c)
{
	while (*_s != (char)_c) {
		if (!*_s++) {
			return 0;
		}
	}
	return (char *)_s;
}

uint32 strspn(const char *_s, const char *_accept)
{
	uint32 ret=0;
	while(*_s && strchr(_accept,*_s++)) {
		ret++;
	}
	return ret;
}

uint32 strcspn(const char *_s, const char *_reject)
{
	uint32 ret=0;
	while(*_s) {
		if(strchr(_reject,*_s)) {
			return ret;
		} else {
			_s++,ret++;
		}
	}
	return ret;
}

char *strtok(char *_s, const char *_delim)
{
	static char* p=0;
	if(_s) {
		p=_s;
	} else if(!p) {
		return 0;
	}
	_s = p   + strspn(p,_delim);
	p  = _s  + strcspn(_s,_delim);
	if(p==_s) {
		return p=0;
	}
	p = *p ? *p=0,p+1 : 0;
	return _s;
}

char *strstr(const char *_haystack, const char *_needle)
{
	uint32 needleLen;
	if(*_needle == '\0') {
		return (char *) _haystack;
	}
	needleLen = strlen(_needle);

	for(;(_haystack = strchr(_haystack, *_needle))!= NULL;_haystack++) {
		if (strncmp(_haystack, _needle, needleLen) == 0) {
			return (char *) _haystack;
		}
	}
	return NULL;
}

uint32 stroccr(char* str, const char c)
{
	uint32 i = 0;
	for(;*str!='\0';)
	{
		if(*str == c)	i++;
		++str;
	}
	return i;
}

#include "../drivers/sleep/sleep.h"

uint8 strEql(string ch1,string ch2)                     
{
	uint8 result = 1;
    uint8 size = strlen(ch1);
    if(size != strlen(ch2)) result =0;
    else 
	{
        uint8 i = 0;
        for(i;i<=size;i++)
		{
        	if(ch1[i] != ch2[i]) result = 0;
		}
    }
	return result;
}