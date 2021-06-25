#ifndef VESA_H
#define VESA_H

#include "../../grub/multiboot.h"
#include "../../memory/paging.h"

//static inline void VesaPutPixel(int x, int y, int color);
//static inline void VesaPutLine(int x, int y, int color, int size);

struct multiboot_tag_framebuffer *fb;
uint32 *framebuffer;

inline void VesaPutPixel(int x, int y, int color)
{
    uint32 pixel_offset = y * fb->common.framebuffer_width + x;
    framebuffer[pixel_offset] = color;
}

inline void VesaPutLine(int x, int y, int color, int size)
{
	uint32 pixel_offset = y * fb->common.framebuffer_width + x;
	while(size--) framebuffer[pixel_offset++] = color;
}

#endif
