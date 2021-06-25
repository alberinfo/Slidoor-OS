#ifndef VGA_H
#define VGA_H

#include "../../arch/x86/cpu.h"

#define VGA_CRT 0              //CRT set
#define VGA_ACT 1              //attribute controller set
#define VGA_GEN 2              //general registers set
#define VGA_SEQ 3              //sequencer set
#define VGA_GCT 4              //graphics controller set
#define VGA_OLD 5              //old pallete enable

#define VGA__GEN__MIS 0        //miscellaneous in the generals set
#define VGA__GEN__ST1 1        //status 1 in the generals set, readonly
#define VGA__OLD__ENA 0        //old pallete enable index

#define VGA__GEN_MISC_R 0x3cc  //general miscellaneous, read
#define VGA__GEN_MISC_W 0x3c2  //general miscellaneous, write
#define VGA__GEN_STATUS1 0x3da //general status 1
#define VGA__SEQ_ADDR 0x3c4    //sequencer, address
#define VGA__SEQ_DATA 0x3c5    //sequencer, data
#define VGA__SEQ__RST 0        //sequencer, reset
#define VGA__SEQ__CLK 1        //sequencer, clock mode
#define VGA__SEQ__MAP 2        //sequencer, map selection
#define VGA__SEQ__FNT 3        //sequencer, font selection
#define VGA__SEQ__MEM 4        //sequencer, memory mode
#define VGA__CRT_ADDR 0x3d4    //CRT, address
#define VGA__CRT_DATA 0x3d5    //CRT, data
#define VGA__CRT__HTO 0        //CRT, horizontal total
#define VGA__CRT__HDE 1        //CRT, horizontal display-enable end
#define VGA__CRT__HBS 2        //CRT, horizontal blanking start
#define VGA__CRT__HBE 3        //CRT, horizontal blanking end
#define VGA__CRT__HRS 4        //CRT, horizontal retrace start
#define VGA__CRT__HRE 5        //CRT, horizontal retrace end
#define VGA__CRT__VTO 6        //CRT, vertical total
#define VGA__CRT__MSB 7        //CRT, most significant bits
#define VGA__CRT__PRS 8        //CRT, preset scanline
#define VGA__CRT__MSL 9        //CRT, maximum scanline
#define VGA__CRT__CSL 10       //CRT, cursor start
#define VGA__CRT__CEL 11       //CRT, cursor end
#define VGA__CRT__SAH 12       //CRT, start address (high)
#define VGA__CRT__SAL 13       //CRT, start address (low)
#define VGA__CRT__CLH 14       //CRT, cursor location (high)
#define VGA__CRT__CLL 15       //CRT, cursor location (low)
#define VGA__CRT__VRS 16       //CRT, vertical retrace start
#define VGA__CRT__VRE 17       //CRT, vertical retrace end
#define VGA__CRT__VDE 18       //CRT, vertical display-enable end
#define VGA__CRT__OFF 19       //CRT, offset (logical line width)
#define VGA__CRT__ULL 20       //CRT, underline location
#define VGA__CRT__VBS 21       //CRT, vertical blanking start
#define VGA__CRT__VBE 22       //CRT, vertical blanking end
#define VGA__CRT__MOD 23       //CRT, mode
#define VGA__CRT__SSL 24       //CRT, line compare (split screen line)
#define VGA__GCT_ADDR 0x3ce    //graphics controller, address
#define VGA__GCT_DATA 0x3cf    //graphics controller, data
#define VGA__GCT__WRV 0        //graphics controller, write value
#define VGA__GCT__WRS 1        //graphics controller, write selection
#define VGA__GCT__COC 2        //graphics controller, color compare
#define VGA__GCT__DRO 3        //graphics controller, data rotate
#define VGA__GCT__RDM 4        //graphics controller, read map
#define VGA__GCT__GMO 5        //graphics controller, graphics mode
#define VGA__GCT__MIS 6        //graphics controller, miscelaneous
#define VGA__GCT__CSE 7        //graphics controller, color selection
#define VGA__GCT__BIT 8        //graphics controller, bit mask
#define VGA__ACT_ADDA 0x3c0    //attribute controller, address and data
#define VGA__ACT_READ 0x3c1    //attribute controller, read
#define VGA__ACT__ATB 16       //attribute controller, attributes
#define VGA__ACT__BOR 17       //attribute controller, border color
#define VGA__ACT__PEN 18       //attribute controller, plane enable
#define VGA__ACT__OFF 19       //attribute controller, offset
#define VGA__ACT__CSE 20       //attribute controller, color selection
#define VGA__DAC_ADDR_R 0x3c7  //pallete, read address
#define VGA__DAC_ADDR_W 0x3c8  //pallete, write address
#define VGA__DAC_DATA 0x3c9    //pallete, data
#define VGA__DAC_MASK 0x3c6    //pallete, bit mask

uint8 PAL16[48];

uint8 PAL256[768];

//VGA register structure
typedef struct
{
uint8
gen_mis,
seq[5],
crt[25],
gct[9],
act[5];
}vgaregs_t;

//tables for horizontal configurations
//SEQ_CLK,SEQ_MEM,CRT_HTO,CRT_HDE,CRT_HBS,CRT_HBE,CRT_HRS,CRT_HRE,CRT_OFF,GCT_GMO,GCT_MIS,ACT_ATB
uint8 tbl_hor_txt40[12];
uint8 tbl_hor_txt80[12];
uint8 tbl_hor_txt90[12];
                                                    //0x5e,0xaa
uint8 tbl_hor_gra640[12];
                                                     //0x55,0x81
uint8 tbl_hor_gra720[12];
                                                     //0x5f,0xac
uint8 tbl_hor_gra320[12];
                                                     //0x55,0x81
uint8 tbl_hor_gra360[12];
                                                     //0x5f,0xac

//tables for vertical configurations
//GEN_MIS,CRT_VTO,CRT_MSB,CRT_MSL,CRT_VRS,CRT_VRE,CRT_VDE,CRT_VBS,CRT_VBE
uint8 tbl_ver_txt20_12[9];
uint8 tbl_ver_txt25_8[9];
uint8 tbl_ver_txt25_14[9];
uint8 tbl_ver_txt25_16[9];
uint8 tbl_ver_txt30_8[9];
uint8 tbl_ver_txt30_16[9];
uint8 tbl_ver_txt40_12[9];
uint8 tbl_ver_txt50_8[9];
uint8 tbl_ver_txt60_8[9];
uint8 tbl_ver_gra200[9];
uint8 tbl_ver_gra240[9];
uint8 tbl_ver_gra350[9];
uint8 tbl_ver_gra400[9];
uint8 tbl_ver_gra480[9];

//tables for video modes
//SEQ_CLK,ACT_OFF,CRT_MOD
uint8 tbl_mod_txt8p[3];
uint8 tbl_mod_txt9p[3];
uint8 tbl_mod_gra16c[3];
uint8 tbl_mod_gra256c[3];

void VGAWriteReg(uint8 set, uint8 index, uint8 value);
uint8 VGAReadReg(uint8 set, uint8 index);
void resetregs(vgaregs_t*regs);
void vgachangemode(vgaregs_t *regs);
void settextplane(void);
void setfontplane(void);
void VGASetPal(uint8*pal,uint8 first,uint16 num);
void VGAGetPal(uint8*pal,uint8 first,uint16 num);
void VGAGotoXY(uint8 x,uint8 y,uint8 w);
void VGAWhereXY(uint8*x,uint8*y,uint8 w);
void VGASetCursor(uint8 y,uint8 h);
void VGAGetCursor(uint8*y,uint8*h);
void VGACursor(uint8 e);
void VGASetFont(uint8*fnt,uint8 ch,uint16 first,uint16 num);
void VGAGetFont(uint8*fnt,uint8 ch,uint16 first,uint16 num);
void VGAWaitVBL(void);
uint8 VGAMode(uint8 m,uint16 w,uint16 h,uint8 o);
void VGAPutpixel(int x,int y, int color);

#endif
