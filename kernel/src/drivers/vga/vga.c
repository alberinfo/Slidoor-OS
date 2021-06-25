#include "vga.h"

uint8 PAL16[48]=
{
0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x00,
0x80,0x00,0x80,0x80,0x80,0x00,0xc0,0xc0,0xc0,0x80,0x80,0x80,0x00,0x00,0xff,
0x00,0xff,0x00,0x00,0xff,0xff,0xff,0x00,0x00,0xff,0x00,0xff,0xff,0xff,0x00,
0xff,0xff,0xff
};

uint8 PAL256[768]=
{
00, 00, 00, 00, 10, 41, 12, 28, 18, 02, 43, 22, 35,
19, 9,  58, 00, 00, 57, 35, 12, 43, 43, 47, 24, 24,
28, 20, 24, 60, 10, 60, 15, 31, 47, 63, 62, 56, 20,
60, 56, 22, 63, 61, 36, 63, 63, 63, 00, 00, 00, 05,
05, 05, 8,  8,  8,  11, 11, 11, 14, 14, 14, 17, 17,
17, 20, 20, 20, 24, 24, 24, 28, 28, 28, 32, 32, 32,
36, 36, 36, 40, 40, 40, 45, 45, 45, 50, 50, 50, 56,
56, 56, 63, 63, 63, 13, 12, 15, 15, 16, 22, 17, 20,
29, 19, 24, 36, 21, 28, 43, 23, 31, 50, 25, 34, 57,
26, 42, 63, 00, 15, 02, 01, 22, 04, 02, 29, 06, 03,
36, 8,  04, 43, 10, 05, 50, 12, 06, 57, 14, 20, 63,
40, 18, 06, 07, 25, 12, 11, 33, 17, 14, 40, 23, 18,
48, 28, 21, 55, 34, 25, 62, 39, 27, 63, 48, 36, 15,
03, 02, 22, 06, 04, 29, 9,  06, 36, 12, 8,  43, 15,
10, 50, 18, 12, 57, 21, 14, 63, 28, 20, 15, 00, 00,
22, 07, 00, 29, 15, 00, 36, 23, 00, 43, 31, 00, 50,
39, 00, 57, 47, 00, 63, 55, 00, 15, 05, 03, 22, 11,
07, 29, 17, 11, 36, 23, 15, 43, 29, 19, 50, 35, 23,
57, 41, 27, 63, 53, 34, 28, 14, 12, 33, 20, 14, 38,
26, 16, 43, 32, 18, 48, 38, 20, 53, 44, 22, 58, 50,
24, 63, 56, 30, 05, 05, 06, 10, 10, 13, 15, 15, 20,
20, 20, 27, 25, 25, 34, 30, 30, 41, 35, 35, 48, 44,
44, 63, 03, 06, 05, 05, 11, 9,  07, 16, 13, 9,  21,
17, 11, 26, 21, 13, 31, 25, 15, 36, 29, 20, 48, 38,
06, 06, 07, 13, 13, 15, 20, 20, 23, 27, 27, 31, 34,
34, 39, 41, 41, 47, 48, 48, 55, 57, 57, 63, 06, 15,
04, 12, 22, 8,  18, 29, 12, 24, 36, 16, 30, 43, 20,
36, 50, 24, 42, 57, 28, 54, 63, 35, 15, 10, 10, 22,
16, 16, 29, 21, 21, 36, 27, 27, 43, 32, 32, 50, 38,
38, 57, 43, 43, 63, 54, 54, 15, 15, 06, 22, 22, 12,
29, 29, 18, 36, 36, 24, 43, 43, 30, 50, 50, 36, 57,
57, 42, 63, 63, 54, 02, 04, 14, 06, 12, 21, 10, 20,
28, 14, 28, 35, 18, 36, 42, 22, 44, 49, 26, 52, 56,
36, 63, 63, 18, 04, 14, 24, 8,  21, 31, 12, 28, 37,
16, 35, 44, 20, 42, 50, 24, 49, 57, 28, 56, 63, 38,
63, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 53, 44, 22, 9, 
8,  12, 16, 14, 16, 22, 21, 20, 29, 27, 24, 35, 34,
28, 42, 40, 32, 48, 47, 36, 57, 56, 43, 8,  12, 16,
14, 16, 22, 21, 20, 29, 27, 24, 35, 34, 28, 42, 40,
32, 48, 47, 36, 57, 56, 43, 63, 13, 9,  11, 21, 16,
15, 27, 22, 18, 36, 29, 22, 42, 35, 25, 51, 42, 29,
57, 48, 32, 63, 56, 39, 06, 14, 9,  12, 21, 14, 18,
27, 22, 24, 33, 28, 30, 39, 36, 36, 46, 42, 42, 52,
47, 50, 59, 53, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
00
};

//tables for horizontal configurations
//SEQ_CLK,SEQ_MEM,CRT_HTO,CRT_HDE,CRT_HBS,CRT_HBE,CRT_HRS,CRT_HRE,CRT_OFF,GCT_GMO,GCT_MIS,ACT_ATB
uint8 tbl_hor_txt40[12]={0x8, 0x00,0x2d,0x27,0x28,0x10,0x2b,0xa0,0x14,0x10,0x0e,0x00};
uint8 tbl_hor_txt80[12]={0x00,0x00,0x5f,0x4f,0x50,0x02,0x55,0x81,0x28,0x10,0x0e,0x00};
uint8 tbl_hor_txt90[12]={0x00,0x00,0x6b,0x59,0x5a,0x0e,0x5f,0xac,0x2d,0x10,0x0e,0x00};
                                                    //0x5e,0xaa
uint8 tbl_hor_gra640[12]={0x01,0x04,0x5f,0x4f,0x50,0x02,0x54,0x80,0x28,0x00,0x05,0x01};
                                                     //0x55,0x81
uint8 tbl_hor_gra720[12]={0x01,0x04,0x6b,0x59,0x5a,0x0e,0x5e,0xaa,0x2d,0x00,0x05,0x01};
                                                     //0x5f,0xac
uint8 tbl_hor_gra320[12]={0x01,0x04,0x5f,0x4f,0x50,0x02,0x54,0x80,0x28,0x40,0x05,0x41};
                                                     //0x55,0x81,uint8 tbl_hor_gra360[12]={0x01,0x04,0x6b,0x59,0x5a,0x0e,0x5e,0xaa,0x2d,0x40,0x05,0x41};
                                                     //0x5f,0xac

//tables for vertical configurations
//GEN_MIS,CRT_VTO,CRT_MSB,CRT_MSL,CRT_VRS,CRT_VRE,CRT_VDE,CRT_VBS,CRT_VBE
uint8 tbl_ver_txt20_12[9]={0xc0,0x0b,0x3e,0xcb,0xea,0x0c,0xdf,0xe7,0x04};
uint8 tbl_ver_txt25_8[9]={0x40,0xbf,0x1f,0xc7,0x9c,0x2e,0x8f,0x96,0xb9};
uint8 tbl_ver_txt25_14[9]={0x80,0xbf,0x1f,0x4d,0x83,0x35,0x5d,0x63,0xba};
uint8 tbl_ver_txt25_16[9]={0x40,0xbf,0x1f,0x4f,0x9c,0x2e,0x8f,0x96,0xb9};
uint8 tbl_ver_txt30_8[9]={0xc0,0x0b,0x3e,0xc7,0xea,0x0c,0xdf,0xe7,0x04};
uint8 tbl_ver_txt30_16[9]={0xc0,0x0b,0x3e,0x4f,0xea,0x0c,0xdf,0xe7,0x04};
uint8 tbl_ver_txt40_12[9]={0xc0,0x0b,0x3e,0x4b,0xea,0x0c,0xdf,0xe7,0x04};
uint8 tbl_ver_txt50_8[9]={0x40,0xbf,0x1f,0x47,0x9c,0x2e,0x8f,0x96,0xb9};
uint8 tbl_ver_txt60_8[9]={0xc0,0x0b,0x3e,0x47,0xea,0x0c,0xdf,0xe7,0x04};
uint8 tbl_ver_gra200[9]={0x40,0xbf,0x1f,0x41,0x9c,0x2e,0x8f,0x96,0xb9};
uint8 tbl_ver_gra240[9]={0xc0,0x0b,0x3e,0x41,0xea,0x0c,0xdf,0xe7,0x04};
uint8 tbl_ver_gra350[9]={0x80,0xbf,0x1f,0x40,0x83,0x35,0x5d,0x63,0xba};
uint8 tbl_ver_gra400[9]={0x40,0xbf,0x1f,0x40,0x9c,0x2e,0x8f,0x96,0xb9};
uint8 tbl_ver_gra480[9]={0xc0,0x0b,0x3e,0x40,0xea,0x0c,0xdf,0xe7,0x04};

//tables for video modes
//SEQ_CLK,ACT_OFF,CRT_MOD
uint8 tbl_mod_txt8p[3]={0x01,0x00,0x00};
uint8 tbl_mod_txt9p[3]={0x00,0x8, 0x00};
uint8 tbl_mod_gra16c[3]={0x01,0x00,0x40};
uint8 tbl_mod_gra256c[3]={0x01,0x00,0x40};

void VGAWriteReg(uint8 set,uint8 index,uint8 value)
{
   switch(set)
   {
      case VGA_CRT:
         if(index<=24)
         {
            outportb(VGA__CRT_ADDR,index);
            outportb(VGA__CRT_DATA,value);
         }
         break;
      case VGA_ACT:
         if(index<=20)
         {
            inportb(VGA__GEN_STATUS1);
            index=(inportb(VGA__ACT_ADDA)&0x20)|index;
            inportb(VGA__GEN_STATUS1);
            outportb(VGA__ACT_ADDA,index);
            outportb(VGA__ACT_ADDA,value);
         }
         break;
      case VGA_GEN:
         if(index==0)
         {
            outportb(VGA__GEN_MISC_W,value);
         }
         break;
      case VGA_SEQ:
         if(index<=4)
         {
            outportb(VGA__SEQ_ADDR,index);
            outportb(VGA__SEQ_DATA,value);
         }
         break;
      case VGA_GCT:
         if(index<=8)
         {
            outportb(VGA__GCT_ADDR,index);
            outportb(VGA__GCT_DATA,value);
         }
         break;
      case VGA_OLD:
         if(index==0)
         {
            value=value?0x20:0;
            inportb(VGA__GEN_STATUS1);
            outportb(VGA__ACT_ADDA,value);
         }
         break;
   }
}

//reads a value from a VGA register
//set is 0 for CRT controller,0x1 for attribute controller,0x2 for
//generals,0x3 for sequencer,0x4 for graphics controller,0x5 for
//old pallete enable
uint8 VGAReadReg(uint8 set,uint8 index)
{
   uint8 r=0;
   switch(set)
   {
   case VGA_CRT:
      if(index<=24)
      {
         outportb(VGA__CRT_ADDR,index);
         r=inportb(VGA__CRT_DATA);
      }
      break;
   case VGA_ACT:
      if(index<=20)
      {
         inportb(VGA__GEN_STATUS1);
         index=(inportb(VGA__ACT_ADDA)&0x20)|index;
         inportb(VGA__GEN_STATUS1);
         outportb(VGA__ACT_ADDA,index);
         r=inportb(VGA__ACT_READ);
      }
      break;
   case VGA_GEN:
      if(index==VGA__GEN__MIS)
      {
         r=inportb(VGA__GEN_MISC_R);
      }
      if(index==VGA__GEN__ST1)
      {
         r=inportb(VGA__GEN_STATUS1);
      }
      break;
   case VGA_SEQ:
      if(index<=4)
      {
         outportb(VGA__SEQ_ADDR,index);
         r=inportb(VGA__SEQ_DATA);
      }
      break;
   case VGA_GCT:
      if(index<=8)
      {
         outportb(VGA__GCT_ADDR,index);
         r=inportb(VGA__GCT_DATA);
      }
      break;
   case VGA_OLD:
      if(index==0)
      {
         inportb(VGA__GEN_STATUS1);
         r=(inportb(VGA__ACT_ADDA)>>5)&1;
      }
      break;
   }
return(r);
}

//resets the registers in a VGA register structure
void resetregs(vgaregs_t*regs)
{
   uint32 i;
   uint8*p=(uint8*)regs;
   for(i=0;i<sizeof(vgaregs_t);i++)
   {
      *p++=0;
   }
   regs->gen_mis=0x23;//enable video memory,0xnormal mode,0xupper 64KB page
   regs->seq[VGA__SEQ__CLK]=0x02;//set bit to 1,   regs->seq[VGA__SEQ__MAP]=0x0f;//select the 4 planes
   regs->seq[VGA__SEQ__MEM]=0x02;//enable 256KB
   regs->crt[VGA__CRT__HBE]=0x80;//set bit to 1,   regs->crt[VGA__CRT__VRE]=0x30;//disable IRQs
   regs->crt[VGA__CRT__ULL]=31;//underline location
   regs->crt[VGA__CRT__MSB]=0x10;//split screen
   regs->crt[VGA__CRT__MSL]=0x40;
   regs->crt[VGA__CRT__SSL]=0xff;
   regs->crt[VGA__CRT__MOD]=0xa3;//normal mode
   regs->gct[VGA__GCT__BIT]=0xff;//bit mask
   regs->act[VGA__ACT__ATB-16]=0x04;//enable line characters
   regs->act[VGA__ACT__PEN-16]=0x0f;//enable the 4 planes
}

//changes the video mode by writing in all the VGA registers
void vgachangemode(vgaregs_t *regs)
{
   uint16 i;
   //unlock some CRTC registrrs
   VGAWriteReg(VGA_CRT,VGA__CRT__VRE,VGAReadReg(VGA_CRT,VGA__CRT__VRE)&0x7f);
   //enable pallete
   outportb(VGA__DAC_MASK,0xff);
   //wait until display-enable start
   //while(!(VGAReadReg(VGA_GEN,VGA__GEN__ST1)&0x08));
   //while(VGAReadReg(VGA_GEN,VGA__GEN__ST1)&0x08);
   //stop sequencer
   VGAWriteReg(VGA_SEQ,VGA__SEQ__RST,0x01);
   //write in the registers
   VGAWriteReg(VGA_GEN,VGA__GEN__MIS,regs->gen_mis);
   for(i=1;i<5;i++)
      VGAWriteReg(VGA_SEQ,i,regs->seq[i]);
   for(i=0;i<25;i++)
      VGAWriteReg(VGA_CRT,i,regs->crt[i]);
   for(i=0;i<9;i++)
      VGAWriteReg(VGA_GCT,i,regs->gct[i]);
   for(i=0;i<5;i++)
      VGAWriteReg(VGA_ACT,i+16,regs->act[i]);
   //reset old pallete
   VGAWriteReg(VGA_OLD,VGA__OLD__ENA,0);
   for(i=0;i<16;i++)
      VGAWriteReg(VGA_ACT,i,i);
   VGAWriteReg(VGA_OLD,VGA__OLD__ENA,1);
   //resume sequencer
   VGAWriteReg(VGA_SEQ,VGA__SEQ__RST,0x03);
}

//selects the text plane
void settextplane(void)
{
   VGAWriteReg(VGA_GCT,VGA__GCT__GMO,0x10);
   VGAWriteReg(VGA_GCT,VGA__GCT__MIS,(VGAReadReg(VGA_GCT,VGA__GCT__MIS)&0x0c)|2);
   VGAWriteReg(VGA_SEQ,VGA__SEQ__MAP,0x03);
   VGAWriteReg(VGA_GCT,VGA__GCT__RDM,1);
   VGAWriteReg(VGA_SEQ,VGA__SEQ__MEM,0x02);
}

//selects the font plane
void setfontplane(void)
{
   VGAWriteReg(VGA_GCT,VGA__GCT__GMO,0x00);
   VGAWriteReg(VGA_GCT,VGA__GCT__MIS,VGAReadReg(VGA_GCT,VGA__GCT__MIS)&0x0c);
   VGAWriteReg(VGA_SEQ,VGA__SEQ__MAP,0x04);
   VGAWriteReg(VGA_GCT,VGA__GCT__RDM,2);
   VGAWriteReg(VGA_SEQ,VGA__SEQ__MEM,0x06);
}

//modifies the VGA pallete
//pal=pointer to the first pallete color to be used
//first=first color to modify
//num=number of colors to modify
void VGASetPal(uint8*pal,uint8 first,uint16 num)
{
   if((num+first)>256)num=256-first;
   if(!num)return;
   num*=3;
   outportb(VGA__DAC_ADDR_W,first);
   while(num--)
   {
      outportb(VGA__DAC_DATA,(*pal)>>2);
      pal++;
   }
}

//obtains the VGA pallete
//pal=pointer to the first pallete color to be overwritten
//first=first color to read
//num=number of colors to read
void VGAGetPal(uint8*pal,uint8 first,uint16 num)
{
   if((num+first)>256)num=256-first;
   if(!num)return;
   num*=3;
   outportb(VGA__DAC_ADDR_R,first);
   while(num--)
   {
      *pal=inportb(VGA__DAC_DATA)<<2;
      pal++;
   }
}

//puts the text cursor in the x,y coordinates
//w is the visual screen width in characters
void VGAGotoXY(uint8 x,uint8 y,uint8 w)
{
   uint16 c;
   c=y;c*=w;
   c+=x;
   VGAWriteReg(VGA_CRT,VGA__CRT__CLH,c>>8);
   VGAWriteReg(VGA_CRT,VGA__CRT__CLL,c);
}

//gets the cursor coordinates and returns them in x,y
//w is the visual screen width in characters
void VGAWhereXY(uint8*x,uint8*y,uint8 w)
{
   uint16 c;
   c=VGAReadReg(VGA_CRT,VGA__CRT__CLH);
   c<<=8;
   c|=VGAReadReg(VGA_CRT,VGA__CRT__CLL);
   *x=c%w;
   *y=c/w;
}

//changes the text cursor appearence
//y=first line
//h=block height
void VGASetCursor(uint8 y,uint8 h)
{
   VGAWriteReg(VGA_CRT,VGA__CRT__CSL,y&31);
   VGAWriteReg(VGA_CRT,VGA__CRT__CEL,(y+h-1)&31);
}

//gets the text cursor appearence
//y=first line
//h=block height
void VGAGetCursor(uint8*y,uint8*h)
{
   *y=VGAReadReg(VGA_CRT,VGA__CRT__CSL)&31;
   *h=VGAReadReg(VGA_CRT,VGA__CRT__CEL)&31;
   *h-=*y;
   (*h)++;
}

//enables or disables the text cursor
void VGACursor(uint8 e)
{
   e=e?0:0x20;
   VGAWriteReg(VGA_CRT,VGA__CRT__CSL,(VGAReadReg(VGA_CRT,VGA__CRT__CSL)&31)|e);
}/*end function*/

//modifies the text font
//fnt=pointer to the first font character to be used
//ch=character height in the font
//first=first character in the VGA font to modify
//num=number of characters to modify
void VGASetFont(uint8*fnt,uint8 ch,uint16 first,uint16 num)
{
   uint8*v=(uint8*)0xb8000;
   uint16 i,j;
   if((num+first)>512)num=512-first;
   if(!num)return;
   v+=first*32;
   setfontplane();
   for(i=0;i<num;i++)
   {
      for(j=0;j<ch;j++)
      {
         v[j]=fnt[j];
      }
      for(j=ch;j<32;j++)
      {
         v[j]=0;
      }
      fnt+=ch;
      v+=32;
   }
   settextplane();
}

//obtains the text font
//fnt=pointer to the first font character to be overwritten
//ch=character height in the font
//first=first character in the VGA font to read
//num=number of characters to read
void VGAGetFont(uint8*fnt,uint8 ch,uint16 first,uint16 num)
{
   uint8*v=(uint8*)0xb8000;
   uint16 i,j;
   if((num+first)>512)num=512-first;
   if(!num)return;
   v+=first*32;
   setfontplane();
   for(i=0;i<num;i++)
   {
      for(j=0;j<ch;j++)
      {
         fnt[j]=v[j];
      }
      fnt+=ch;
      v+=32;
   }
   settextplane();
}

//waits until a vertical retrace period starts
void VGAWaitVBL(void)
{
   while(VGAReadReg(VGA_GEN,VGA__GEN__ST1)&8);
   while(!(VGAReadReg(VGA_GEN,VGA__GEN__ST1)&8));
}/*end function*/

//sets a VGA video mode
//returns 1 if the mode is valid,0x0 if not
//m=mode
//  0=text (8-pixels-wide characters)
//  1=text (9-pixels-wide characters)
//  2=graphics 16 colors
//  3=graphics 256 colors
//w=width (in characters or in pixels)
//h=height (in characters or in pixels)
//o=option
//  text modes:
//    8=8-pixels-high characters
//    12=12-pixels-high characters
//    14=14-pixels-high characters
//    16=16-pixels-high characters
//  graphic modes:
//    0=normal
//    1=chained mode
//----------------------------------------------------------------
//text mode widths (8p): 40,0x80,0x90,//text mode widths (9p): 40,0x80,//text mode heights (8-pix-h): 25,0x30,0x50,0x60,//text mode heights (12-pix-h): 20,0x40,//text mode heights (14-pix-h): 25,//text mode heights (16-pix-h): 25,0x30,//graphic mode widths (16c): 640,0x720,//graphic mode widths (256c): 320,0x360,//graphic mode heights: 200,0x240,0x350,0x400,0x480,//chained mode only allows 320*200 at 256 colors
int width;
int height;
uint8 VGAMode(uint8 m,uint16 w,uint16 h,uint8 o)
{
   uint8*tbl_hor,*tbl_ver,*tbl_mod;
   uint8*v;
   uint32 i;
   vgaregs_t regs;
   uint8 chained=0;
   uint8 curstart=0,curheight=0;
   resetregs(&regs);
   switch(m)
   {
      case 0://txt 8p
      case 1://txt 9p
         if(m)
         {
            tbl_mod=tbl_mod_txt9p;
            regs.gen_mis|=0x04;
         }
         else
         {
            tbl_mod=tbl_mod_txt8p;
         }
         switch(w)
         {
            case 40:
               tbl_hor=tbl_hor_txt40;
               break;
            case 80:
               tbl_hor=tbl_hor_txt80;
               break;
            case 90:
               if(m==1)return(0);
               tbl_hor=tbl_hor_txt90;
               regs.gen_mis|=0x04;
               break;
            default:
               return(0);
         }
         switch(h)
         {
            case 20:
               switch(o)
               {
                  case 12:
                     tbl_ver=tbl_ver_txt20_12;
                     break;
                  default:
                     return(0);
               }
               break;
            case 25:
               switch(o)
               {
                  case 8:
                     tbl_ver=tbl_ver_txt25_8;
                     break;
                  case 14:
                     tbl_ver=tbl_ver_txt25_14;
                     break;
                  case 16:
                     tbl_ver=tbl_ver_txt25_16;
                     break;
                  default:
                     return(0);
               }
               break;
            case 30:
               switch(o)
               {
                  case 8:
                     tbl_ver=tbl_ver_txt30_8;
                     break;
                  case 16:
                     tbl_ver=tbl_ver_txt30_16;
                     break;
                  default:
                     return(0);
               }
               break;
            case 40:
               switch(o)
               {
                  case 12:
                     tbl_ver=tbl_ver_txt40_12;
                     break;
                  default:
                     return(0);
               }
               break;
            case 50:
               switch(o)
               {
                  case 8:
                     tbl_ver=tbl_ver_txt50_8;
                     break;
                  default:
                     return(0);
               }
               break;
            case 60:
               switch(o)
               {
                  case 8:
                     tbl_ver=tbl_ver_txt60_8;
                     break;
                  default:
                     return(0);
               }
               break;
            default:
               return(0);
         }
         break;
      case 2://gra 16c
         if(o)return(0);
         tbl_mod=tbl_mod_gra16c;
         switch(w)
         {
            case 640:
               width = 640;
               tbl_hor=tbl_hor_gra640;
               break;
            case 720:
                width = 720;
               regs.gen_mis|=0x04;
               tbl_hor=tbl_hor_gra720;
               break;
            default:
               return(0);
         }
         switch(h)
         {
            case 200:
               height = 200;
               tbl_ver=tbl_ver_gra200;
               break;
            case 240:
               height = 240;
               tbl_ver=tbl_ver_gra240;
               break;
            case 350:
               height = 350;
               tbl_ver=tbl_ver_gra350;
               break;
            case 400:
               height = 400;
               tbl_ver=tbl_ver_gra400;
               break;
            case 480:
               height = 480;
               tbl_ver=tbl_ver_gra480;
               break;
            default:
               return(0);
         }
         break;
      case 3://gra 256c
         tbl_mod=tbl_mod_gra256c;
         switch(w)
         {
            case 320:
               width = 320;
               tbl_hor=tbl_hor_gra320;
               break;
            case 360:
               width = 360;
               regs.gen_mis|=0x04;
               tbl_hor=tbl_hor_gra360;
               break;
            default:
               return(0);
         }
         switch(h)
         {
            case 200:
               height = 200;
               tbl_ver=tbl_ver_gra200;
               break;
            case 240:
               height = 240;
               tbl_ver=tbl_ver_gra240;
               break;
            case 350:
                height = 350;
               tbl_ver=tbl_ver_gra350;
               break;
            case 400:
               height = 400;
               tbl_ver=tbl_ver_gra400;
               break;
            case 480:
               height = 480;
               tbl_ver=tbl_ver_gra480;
               break;
            default:
               return(0);
         }
         switch(o)
         {
            case 0:
               break;
            case 1:
               chained=1;
               if((w!=320)||(h!=200))
                  return(0);
               break;
            default:
               return(0);
         }
         break;
      default:
         return(0);
   }
   regs.seq[VGA__SEQ__CLK]|=tbl_hor[0];
   regs.seq[VGA__SEQ__MEM]|=tbl_hor[1];
   regs.crt[VGA__CRT__HTO]|=tbl_hor[2];
   regs.crt[VGA__CRT__HDE]|=tbl_hor[3];
   regs.crt[VGA__CRT__HBS]|=tbl_hor[4];
   regs.crt[VGA__CRT__HBE]|=tbl_hor[5];
   regs.crt[VGA__CRT__HRS]|=tbl_hor[6];
   regs.crt[VGA__CRT__HRE]|=tbl_hor[7];
   regs.crt[VGA__CRT__OFF]|=tbl_hor[8];
   regs.gct[VGA__GCT__GMO]|=tbl_hor[9];
   regs.gct[VGA__GCT__MIS]|=tbl_hor[10];
   regs.act[VGA__ACT__ATB-16]|=tbl_hor[11];

   regs.gen_mis|=tbl_ver[0];
   regs.crt[VGA__CRT__VTO]|=tbl_ver[1];
   regs.crt[VGA__CRT__MSB]|=tbl_ver[2];
   regs.crt[VGA__CRT__MSL]|=tbl_ver[3];
   regs.crt[VGA__CRT__VRS]|=tbl_ver[4];
   regs.crt[VGA__CRT__VRE]|=tbl_ver[5];
   regs.crt[VGA__CRT__VDE]|=tbl_ver[6];
   regs.crt[VGA__CRT__VBS]|=tbl_ver[7];
   regs.crt[VGA__CRT__VBE]|=tbl_ver[8];

   regs.seq[VGA__SEQ__CLK]|=tbl_mod[0];
   regs.act[VGA__ACT__OFF-16]|=tbl_mod[1];
   regs.crt[VGA__CRT__MOD]|=tbl_mod[2];

   if(chained)
   {
      regs.seq[VGA__SEQ__MEM]|=0x08;
      regs.crt[VGA__CRT__ULL]|=0x40;
      regs.crt[VGA__CRT__MOD]&=0xbf;
   }

   vgachangemode(&regs);
   switch(m)
   {
      case 0:
      case 1:
         setfontplane();
         v=(uint8*)0xb8000;
         for(i=0;i<32768;i++)*v++=0;
         settextplane();
         v=(uint8*)0xb8000;
         for(i=0;i<32768;i++)*v++=0;
         switch(o)
         {
            case 8:
               curstart=o-2;
               curheight=2;
               break;
            case 12:
               curstart=o-4;
               curheight=2;
               break;
            case 14:
               curstart=o-4;
               curheight=2;
               break;
            case 16:
               curstart=o-6;
               curheight=2;
         }
         VGASetCursor(curstart,curheight);
         break;
      case 2:
      case 3:
         v=(uint8*)0xa0000;
         VGAWriteReg(VGA_SEQ,VGA__SEQ__MAP,15);
         for(i=0;i<65536;i++)*v++=0;
   }
   return(1);
}

void VGAPutpixel(int x,int y,int color)
{
    uint8* framebuffer = (uint8*) 0xA0000;
    unsigned short pixel_offset = y*640+ x;
    /*if(x < 1)
    {
        pixel_offset = y * width / 4 + x / 4;
    }
    else if(y < 1)
    {
        pixel_offset = y * width / 4 + (x-1) / 4;
    }
    else if(x < 1 && y < 1)
    {
        pixel_offset = y * width / 4 + x / 4;
    }
    else
    {
        pixel_offset = (y-1) * width / 4 + (x-1) / 4;
    }*/
    framebuffer[pixel_offset] = color;
}
