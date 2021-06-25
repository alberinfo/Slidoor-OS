#ifndef FONTS_H
#define FONTS_H

#include "../drivers/vesa/vesa.h"
#include "../string/types.h"
#include "../grub/multiboot.h"

#define FONT_MAGIC 0x864AB572

extern char _binary_Font_psf_start;
extern char _binary_Font_psf_end;
extern char _binary_Font_psf_size;

struct Font_t
{
    uint32 magic;
    uint32 version;
    uint32 HeaderSize;
    uint32 flags;
    uint32 glyphs; //Amount of glyphs
    uint32 BytesPerGlyph;
    uint32 height;
    uint32 width;
} __attribute__((packed));

#endif