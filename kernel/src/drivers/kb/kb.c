#include "kb.h"

//Now, What in the actual F***. For some reason, if i execute printf in this file, it goes
//absolutely crazy. But that does not happen if printf is called outside. H-E-L-P.

int shift = 0;
int str_buff_pos = 0;
string str_buffer = 0; //up to 100 chars.

uint8 kbd_map[0x56] = {
    0/*null*/, 27/*escape*/, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '-', '=',
    0/*backsace*/,
    0/*tab*/,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n' /*enter*/,
    0 /*LEFT CTRL*/,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', ((char)0x27)/*single quote*/, ((char)0x60)/*back tick*/,
    0 /*LEFT SHIFT*/,
    ((char)0x5C)/*inverse slash*/, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/'/*slash*/,
    0 /*RIGHT SHIFT*/,
    '*',
    0/*LEFT ALT*/,
    ' ',
    0/*CAPS LOCK*/,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0 /*F1-F10*/,
    0 /*NUMBER LOCK*/,
    0 /*SCROLL LOCK*/, //71
    //FROM HERE 'TILL THE LAST ONE, WE HAVE SOME NUMBERS FROM THE KEYOADM ABD THEN LAST 'F' KEYS
    '7', '8', '9',
    '-',
    '4', '5', '6',
    '+',
    '1', '2', '3', '0',
    '.', //84
    //NOW WE HAVE THE LAST TWO KEYS, F11 AND F12
    0, 0
};

signed char shift_kbd_map[] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
    0, 0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
    0, 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, 0, 0, ' '
};

void kbBufferInit()
{
    str_buffer = kmalloc(100);
}

void kbd_handler()
{
    unsigned char kcod;
    unsigned char status = inportb(0x64);
    if(status & 0x1)
    {
        kcod = inportb(0x60);
        if(kcod < 0x58)
        {
            if(kcod == 0x2A || kcod == 0x36)
            {
                shift = 1;
            }
            if(kbd_map[kcod] != 0)
            {
                if(!shift)
                {
                    printch(kbd_map[kcod]);
                    str_buffer[str_buff_pos++] = kbd_map[kcod];
                    if(kbd_map[kcod] == '\n')
                    {
                        last_str = str_buffer;
                        last_str[str_buff_pos-1] = '\0';
                        str_buffer = "";
                        str_buff_pos = 0;
                        end_str = 1;
                    }
                } else {
                    printch(shift_kbd_map[kcod]);
                    str_buffer[str_buff_pos++] = shift_kbd_map[kcod];
                    if(shift_kbd_map[kcod] == '\n')
                    {
                        last_str = str_buffer;
                        last_str[str_buff_pos-1] = NULL;
                        str_buffer = "";
                        str_buff_pos = 0;
                        end_str = 1;
                    }
                }
            } else if(kcod == 0xE) {
                if(str_buff_pos > 0)
                {
                    str_buff_pos--;
                    str_buffer[str_buff_pos] = NULL;
                    printch('\b');
                }
            } else if(kcod == 0xF) {
                for(int i = 0; i < 4; i++, str_buff_pos++)
                {
                    printch(' ');
                    str_buffer[str_buff_pos] = ' ';
                }
            }
        } else if(kcod == 0xAA || kcod == 0xB6) {
            shift = 0;
        }
    }
}
