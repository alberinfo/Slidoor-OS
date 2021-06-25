#include "vesa.h"

extern inline void VesaPutPixel(int x, int y, int color);
extern inline void VesaPutLine(int x, int y, int color, int size);

void VesaInit()
{
    fb = get_mboot_info(multiboot_tag_TYPE_FRAMEBUFFER);
    framebuffer = fb->common.framebuffer_addr;
    //asm volatile("mov %0, %%r11\nxchgw %%bx, %%bx" : : "g" (framebuffer) : "r11", "ebx");
    id_vmmap(fb->common.framebuffer_addr, fb->common.framebuffer_width*fb->common.framebuffer_height*(fb->common.framebuffer_bpp/*/8*/)/*bpp*/, 3 | (1 << 6) /*uncacheable*/);
}
