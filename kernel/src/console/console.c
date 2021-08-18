#include "console.h"

bool ConsoleInitialized = false;
uint32 FontBytesPerLine;
uint16 CursorPosX, CursorPosY, ScreenWidth, ScreenHeight, ScreenBPP;
uint32 *fb_addr;
struct Font_t *font;
struct multiboot_tag_framebuffer *fb;

void ConsoleInit()
{
	fb = get_mboot_info(multiboot_tag_TYPE_FRAMEBUFFER);
	vmmap((uint64)&_binary_Font_psf_start - 0xFFFF800000000000, &_binary_Font_psf_start, &_binary_Font_psf_end - &_binary_Font_psf_start, 3);
	font = &_binary_Font_psf_start;
	FontBytesPerLine = (font->width + 7) / 8;
	CursorPosX = 0;
	CursorPosY = 0;
	ScreenWidth = fb->common.framebuffer_width;
	ScreenHeight = fb->common.framebuffer_height;
	ScreenBPP = (fb->common.framebuffer_bpp + 7) / 8;
	fb_addr = fb->common.framebuffer_addr;
	ConsoleInitialized = true;
}

void ClearLine(void)
{
	memzero(fb_addr+CursorPosY*ScreenWidth, CursorPosX);
}

void ClearScreen(void)
{
	CursorPosX = 0;
	CursorPosY = 0;
	memzero(fb_addr, ScreenWidth * ScreenHeight * ScreenBPP);
}

void NewLineCheck()
{
	if(CursorPosY >= ScreenHeight)
	{
		memcpy_fast((uint64)fb_addr, (uint64)fb_addr + ScreenWidth * font->height * ScreenBPP, ScreenWidth * (ScreenHeight-font->height) * ScreenBPP);
		memzero((uint64)fb_addr + (ScreenHeight - font->height) * ScreenWidth * ScreenBPP, font->height * ScreenWidth * ScreenBPP);
		CursorPosY = ScreenHeight - font->height;
		CursorPosX = 0;
	}
}


void printchcolor(uint8 c, uint32 fgcolor, uint32 bgcolor)
{
	if(!ConsoleInitialized) return;
	if(c == 8) //Backslash
	{
		if(CursorPosX == 0)
        {
        	CursorPosX = ScreenWidth - font->width;
        	CursorPosY -= font->height;
        } else {
			CursorPosX -= font->width;
		}
		for(int i = CursorPosY; i < CursorPosY + font->height; i++)
        {
        	VesaPutLine(CursorPosX,  i, 0, font->width);
        }
		return;
	} else if(c == '\r') {
		ClearLine(); //Clear the current line
		CursorPosX = 0;
		return;
	} else if(c == '\n') {
		CursorPosX = 0;
		CursorPosY += font->height;
		NewLineCheck();
		return;
	}
	uint8 *glyph = &_binary_Font_psf_start + font->HeaderSize + (c > 0 && c < font->glyphs ? c : 0) * font->BytesPerGlyph;
	uint32 pixel_offset = CursorPosY * ScreenWidth + CursorPosX;
	for(int height = 0; height < font->height; height++)
	{
		uint64 actual_font = 0;
		if(font->width <= 8) actual_font = *glyph;
		else if(font->width <= 16) actual_font = *(uint16*)glyph;
		else if(font->width <= 32) actual_font = *(uint32*)glyph;
		else actual_font = *(uint64*)glyph;

		uint32 mask = 1 << (font->width - 1);

		for(int width = 0; width < font->width; width++, mask >>= 1) fb_addr[pixel_offset + width] = actual_font & mask ? fgcolor : bgcolor;

		pixel_offset += ScreenWidth;
		glyph += FontBytesPerLine;
	}
	CursorPosX += font->width;
	if(CursorPosX >= ScreenWidth)
	{
		printchcolor('\n', 0, 0);
		return;
	}
	NewLineCheck();
}

void printch(uint8 c)
{
	printchcolor(c, 0xFFFFFFFF, 0); //White fg on Black bg
}

void printf(string str, ...)
{
	CPUDisableInts();
    va_list args;
    va_start(args, str);
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == '%')
        {
            i++;
            if(str[i] == 'x')
            {
                print("0x");
            	string str = base_convert(va_arg(args, uint64), 16);
                print(str);
                free(str);
            } else if(str[i] == 's') {
                print(va_arg(args, string));
            } else if(str[i] == 'c') {
                printch((char)va_arg(args, int)); //This shit ain't working\
                in the kbd driver. WTF?
            } else if(str[i] == 'i') {
            	string str = base_convert(va_arg(args, uint64), 10);
                print(str);
                free(str);
            } else if(str[i] == 'o') {
            	string str = base_convert(va_arg(args, uint64), 8);
                print(str);
                free(str);
            } else if(str[i] == 'b') {
            	string str = base_convert(va_arg(args, uint64), 2);
                print(str);
                free(str);
            }
        } else {
            printch(str[i]);
        }
    }
    va_end(args);
    CPUEnableInts();
    return;
}

void printcolor(string str, uint32 background, uint32 foreground)
{
    uint16 length = strlen(str);
    for(uint16 i = 0;i<length;i++)
    {
        printchcolor(str[i], foreground, background);
    }
}

void print(string str)
{
    printcolor(str, 0,0xFFFFFFFF);
}

void printhexcolor(uint64 hex, uint32 background, uint32 foreground)
{
    print("0x");
    if(!hex)
    {
        printchcolor('0', foreground, background);
        return;
    }
    string str = base_convert(hex, 16);
    bool started_str = false;
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] != '0' || started_str)
        {
            if(!started_str) started_str = true;
            printchcolor(str[i], background, foreground);
        }
    }
}