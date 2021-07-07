#ifndef ACPI_OPCODE_H
#define ACPI_OPCODE_H

#include "../../../string/types.h"
#include "../../../string/string.h"
#include "../../../memory/pmm.h"
#include "../../../console/console.h"

#define AML_ZeroOp 0
#define AML_OneOp 1
#define AML_AliasOp 6
#define AML_NameOp 8
#define AML_BytePrefix 0xA
#define AML_WordPrefix 0xB
#define AML_DwordPrefix 0xC
#define AML_StringPrefix 0xD
#define AML_QwordPrefix 0xE
#define AML_ScopeOp 0x10
#define AML_BufferOp 0x11
#define AML_PackageOp 0x12
#define AML_VarPackageOp 0x13
#define AML_MethodOp 0x14
#define AML_DualnamePrefix 0x2E // '.'
#define AML_MultinamePrefix 0x2F // '/'
#define AML_IsDigitChar(x) (x >= 0x30 && x <= 0x39) // '0' - '9'
#define AML_IsNameChar(x) (x >= 0x41 && x <= 0x5A) // 'A' - 'Z'
#define AML_ExtOpPrefix 0x5B // '['
#define AML_DeviceOp 0x5B82
#define AML_RootChar 0x5C // '\'
#define AML_ParentPrefixChar 0x5E // '^'
#define AML_NameChar 0x5F // '_'
#define AML_Local0Op 0x60
#define AML_Local1Op 0x61
#define AML_Local2Op 0x62
#define AML_Local3Op 0x63
#define AML_Local4Op 0x64
#define AML_Local5Op 0x65
#define AML_Local6Op 0x66
#define AML_Local7Op 0x67
#define AML_Arg0Op 0x68
#define AML_Arg1Op 0x69
#define AML_Arg2Op 0x6A
#define AML_Arg3Op 0x6B
#define AML_Arg4Op 0x6C
#define AML_Arg5Op 0x6D
#define AML_Arg6Op 0x6E
#define AML_StoreOp 0x70
#define AML_RefOfOp 0x71
#define AML_AddOp 0x72
#define AML_ConcatOp 0x73
#define AML_SubstractOp 0x74
#define AML_IncrementOp 0x75
#define AML_DecrementOp 0x76
#define AML_MultiplyOp 0x77
#define AML_DivideOp 0x78
#define AML_ShiftLeftOp 0x79
#define AML_ShiftRightOp 0x7A
#define AML_AndOp 0x7B
#define AML_NandOp 0x7C
#define AML_OrOp 0x7D
#define AML_NorOp 0x7E
#define AML_XorOp 0x7F
#define AML_NotOp 0x80
#define AML_FindSetLeftBitOp 0x81
#define AML_FindSetRightBitOp 0x82
#define AML_DerefOfOp 0x83
#define AML_ConcatResOp 0x84
#define AML_ModOp 0x85
#define AML_NotifyOp 0x86
#define AML_SizeofOp 0x87
#define AML_IndexOp 0x88
#define AML_MatchOp 0x89
#define AML_CreateDwordFieldOp 0x8A
#define AML_CreateWordFieldOp 0x8B
#define AML_CreateByteFieldOp 0x8C
#define AML_CreateBitFieldOp 0x8D
#define AML_TypeOp 0x8E
#define AML_CreateQwordFieldOp 0x8F
#define AML_LandOp 0x90
#define AML_LorOp 0x91
#define AML_LnotOp 0x92
#define AML_LNotEqualOp 0x9293
#define AML_LLessEqualOp 0x9294
#define AML_LGreaterEqualOp 0x9295
#define AML_LEqeualOp 0x93
#define AML_LGreaterOp 0x94
#define AML_LLessOp 0x95
#define AML_ToBufferOp 0x96
#define AML_ToDecimalStringOp 0x97
#define AML_ToHexStringOp 0x98
#define AML_ToIntegerOp 0x99
#define AML_ToStringOp 0x9C
#define AML_CopyObjectOp 0x9D
#define AML_MidOp 0x9E
#define AML_ContinueOp 0x9F
#define AML_IfOp 0xA0
#define AML_ElseOp 0xA1
#define AML_WhileOp 0xA2
#define AML_NoopOp 0xA3
#define AML_ReturnOp 0xA4
#define AML_BreakOp 0xA5
#define AML_BreakPointOp 0xCC
#define AML_OnesOp 0xFF

static inline bool AML_CheckIsName(uint8 *x)
{
	int top = 4;
	for(int i = 0; i < top; i++) //Names are always 4 characters
    {
        if(x[i] == AML_RootChar || x[i] == AML_ParentPrefixChar || x[i] == AML_DualnamePrefix || x[i] == AML_MultinamePrefix) { top++; continue;}
        if(!(AML_IsDigitChar(x[i]) || AML_IsNameChar(x[i]) || x[i] == AML_NameChar)) return false;
    }
	return true;
}

static inline string AML_GetName(uint8 *x)
{
	string ret = kmalloc(4);
	int top = 4, retidx = 0;
	for(int i = 0; i < top; i++) //Names are always 4 characters
	{
		if(x[i] == AML_RootChar || x[i] == AML_ParentPrefixChar || x[i] == AML_DualnamePrefix || x[i] == AML_MultinamePrefix) { top++; continue;}
        if(!(AML_IsDigitChar(x[i]) || AML_IsNameChar(x[i]) || x[i] == AML_RootChar || x[i] == AML_ParentPrefixChar || x[i] == AML_NameChar)) return 0;
		ret[retidx++] = (char)x[i];
	}
	ret[retidx] = '\0';
	return ret;
}

static inline bool AML_CheckIsScope(uint8 *ptr)
{
	uint8 PkgLeadByte = (*(ptr+1) >> 6) + 1; //>> 6 to get the last 2 bits
	return *ptr == AML_ScopeOp && AML_CheckIsName(ptr+PkgLeadByte+1);
}

static inline bool AML_CheckIsDevice(uint8 *ptr)
{
	uint8 PkgLeadByte = (*(ptr+2) >> 6) + 1; //>> 6 to get the last 2 bits
	return *ptr == (AML_DeviceOp >> 8) && *(ptr+1) == (AML_DeviceOp & 0xFF) && AML_CheckIsName(ptr+PkgLeadByte+2);
}

static inline bool AML_CheckIsPackage(uint8 *ptr)
{
	return *ptr == AML_NameOp && AML_CheckIsName(ptr+1) && *(ptr+5) == AML_PackageOp;
}

static inline bool AML_CheckIsMethod(uint8 *ptr)
{
	uint8 PkgLeadByte = (*(ptr+1) >> 6) + 1; //>> 6 to get the last 2 bits
	return *ptr == AML_MethodOp && AML_CheckIsName(ptr+PkgLeadByte+1);
}

static inline int AML_GetMethodArgCount(uint8 *ptr)
{
	uint8 PkgLeadByte = (*(ptr+1) >> 6) + 1; //>> 6 to get the last 2 bits
	return (*(ptr+1+PkgLeadByte+4)) & 7; //bits 0-3 represent the amount of arguments for this function
}

#endif