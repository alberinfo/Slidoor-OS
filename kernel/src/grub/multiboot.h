#include "../string/types.h"
#include "../memory/paging.h"
#include "../memory/pmm.h"

#ifndef HEADER
#define HEADER 1

/*  How many bytes from the start of the file we search for the header. */
#define SEARCH                        32768
#define HEADER_ALIGN                  8

/*  The magic field should contain this. */
#define MULTIBOOT2_HEADER_MAGIC                 0xe85250d6

/*  This should be in %eax. */
#define MULTIBOOT2_BOOTLOADER_MAGIC             0x36d76289

/*  Alignment of multiboot modules. */
#define MOD_ALIGN                     0x00001000

/*  Alignment of the multiboot info structure. */
#define INFO_ALIGN                    0x00000008

/*  Flags set in the ’flags’ member of the multiboot header. */

#define multiboot_tag_ALIGN                  8
#define multiboot_tag_TYPE_END               0
#define multiboot_tag_TYPE_CMDLINE           1
#define multiboot_tag_TYPE_BOOT_LOADER_NAME  2
#define multiboot_tag_TYPE_MODULE            3
#define multiboot_tag_TYPE_BASIC_MEMINFO     4
#define multiboot_tag_TYPE_BOOTDEV           5
#define multiboot_tag_TYPE_MMAP              6
#define multiboot_tag_TYPE_VBE               7
#define multiboot_tag_TYPE_FRAMEBUFFER       8
#define multiboot_tag_TYPE_FRAMEBUFFER_ADDR  22
#define multiboot_tag_TYPE_ELF_SECTIONS      9
#define multiboot_tag_TYPE_APM               10
#define multiboot_tag_TYPE_EFI32             11
#define multiboot_tag_TYPE_EFI64             12
#define multiboot_tag_TYPE_SMBIOS            13
#define multiboot_tag_TYPE_ACPI_OLD          14
#define multiboot_tag_TYPE_ACPI_NEW          15
#define multiboot_tag_TYPE_NETWORK           16
#define multiboot_tag_TYPE_EFI_MMAP          17
#define multiboot_tag_TYPE_EFI_BS            18
#define multiboot_tag_TYPE_EFI32_IH          19
#define multiboot_tag_TYPE_EFI64_IH          20
#define multiboot_tag_TYPE_LOAD_BASE_ADDR    21

#define HEADER_TAG_END  0
#define HEADER_TAG_INFORMATION_REQUEST  1
#define HEADER_TAG_ADDRESS  2
#define HEADER_TAG_ENTRY_ADDRESS  3
#define HEADER_TAG_CONSOLE_FLAGS  4
#define HEADER_TAG_FRAMEBUFFER  5
#define HEADER_TAG_MODULE_ALIGN  6
#define HEADER_TAG_EFI_BS        7
#define HEADER_TAG_ENTRY_ADDRESS_EFI32  8
#define HEADER_TAG_ENTRY_ADDRESS_EFI64  9
#define HEADER_TAG_RELOCATABLE  10

#define ARCHITECTURE_I386  0
#define ARCHITECTURE_MIPS32  4
#define HEADER_TAG_OPTIONAL 1

#define LOAD_PREFERENCE_NONE 0
#define LOAD_PREFERENCE_LOW 1
#define LOAD_PREFERENCE_HIGH 2

#define CONSOLE_FLAGS_CONSOLE_REQUIRED 1
#define CONSOLE_FLAGS_EGA_TEXT_SUPPORTED 2

int parseMultiboot(uint64 addr, uint64 kernel_end);

#ifndef ASM_FILE

struct multiboot_header
{
  /*  Must be MAGIC - see above. */
  uint32 magic;

  /*  ISA */
  uint32 architecture;

  /*  Total header length. */
  uint32 header_length;

  /*  The above fields plus this one must equal 0 mod 2^32. */
  uint32 checksum;
};

struct multiboot_header_tag
{
  uint16 type;
  uint16 flags;
  uint32 size;
};

struct multiboot_header_tag_information_request
{
  uint16 type;
  uint16 flags;
  uint32 size;
  uint32 requests[0];
};

struct multiboot_header_tag_address
{
  uint16 type;
  uint16 flags;
  uint32 size;
  uint32 header_addr;
  uint32 load_addr;
  uint32 load_end_addr;
  uint32 bss_end_addr;
};

struct multiboot_header_tag_entry_address
{
  uint16 type;
  uint16 flags;
  uint32 size;
  uint32 entry_addr;
};

struct multiboot_header_tag_console_flags
{
  uint16 type;
  uint16 flags;
  uint32 size;
  uint32 console_flags;
};

struct multiboot_header_tag_framebuffer
{
  uint16 type;
  uint16 flags;
  uint32 size;
  uint32 width;
  uint32 height;
  uint32 depth;
};

struct multiboot_header_tag_module_align
{
  uint16 type;
  uint16 flags;
  uint32 size;
};

struct multiboot_header_tag_relocatable
{
  uint16 type;
  uint16 flags;
  uint32 size;
  uint32 min_addr;
  uint32 max_addr;
  uint32 align;
  uint32 preference;
};

struct color
{
  uint8 red;
  uint8 green;
  uint8 blue;
};

struct mmap_entry
{
  uint64 addr;
  uint64 len;
#define MEMORY_AVAILABLE              1
#define MEMORY_RESERVED               2
#define MEMORY_ACPI_RECLAIMABLE       3
#define MEMORY_NVS                    4
#define MEMORY_BADRAM                 5
  uint32 type;
  uint32 zero;
};

typedef struct mmap_entry multiboot_memory_map_t;

struct multiboot_tag
{
  uint32 type;
  uint32 size;
};

struct multiboot_tag_string
{
  uint32 type;
  uint32 size;
  char string[0];
};

struct multiboot_tag_module
{
  uint32 type;
  uint32 size;
  uint32 mod_start;
  uint32 mod_end;
  char cmdline[0];
};

struct multiboot_tag_basic_meminfo
{
  uint32 type;
  uint32 size;
  uint32 mem_lower;
  uint32 mem_upper;
};

struct multiboot_tag_bootdev
{
  uint32 type;
  uint32 size;
  uint32 biosdev;
  uint32 slice;
  uint32 part;
};

struct multiboot_tag_mmap
{
  uint32 type;
  uint32 size;
  uint32 entry_size;
  uint32 entry_version;
  struct mmap_entry entries[0];  
};

struct vbe_info_block
{
  uint8 external_specification[512];
};

struct vbe_mode_info_block
{
  uint8 external_specification[256];
};

struct multiboot_tag_vbe
{
  uint32 type;
  uint32 size;

  uint16 vbe_mode;
  uint16 vbe_interface_seg;
  uint16 vbe_interface_off;
  uint16 vbe_interface_len;

  struct vbe_info_block vbe_control_info;
  struct vbe_mode_info_block vbe_mode_info;
};

struct multiboot_tag_framebuffer_common
{
  uint32 type;
  uint32 size;

  uint64 framebuffer_addr;
  uint32 framebuffer_pitch;
  uint32 framebuffer_width;
  uint32 framebuffer_height;
  uint8 framebuffer_bpp;
#define FRAMEBUFFER_TYPE_INDEXED 0
#define FRAMEBUFFER_TYPE_RGB     1
#define FRAMEBUFFER_TYPE_EGA_TEXT     2
  uint8 framebuffer_type;
  uint16 reserved;
};

struct multiboot_tag_framebuffer
{
  struct multiboot_tag_framebuffer_common common;

  union
  {
    struct
    {
      uint16 framebuffer_palette_num_colors;
      struct color framebuffer_palette[0];
    };
    struct
    {
      uint8 framebuffer_red_field_position;
      uint8 framebuffer_red_mask_size;
      uint8 framebuffer_green_field_position;
      uint8 framebuffer_green_mask_size;
      uint8 framebuffer_blue_field_position;
      uint8 framebuffer_blue_mask_size;
    };
  };
};

struct multiboot_tag_elf_sections
{
  uint32 type;
  uint32 size;
  uint32 num;
  uint32 entsize;
  uint32 shndx;
  char sections[0];
};

struct multiboot_tag_apm
{
  uint32 type;
  uint32 size;
  uint16 version;
  uint16 cseg;
  uint32 offset;
  uint16 cseg_16;
  uint16 dseg;
  uint16 flags;
  uint16 cseg_len;
  uint16 cseg_16_len;
  uint16 dseg_len;
};

struct multiboot_tag_efi32
{
  uint32 type;
  uint32 size;
  uint32 pointer;
};

struct multiboot_tag_efi64
{
  uint32 type;
  uint32 size;
  uint64 pointer;
};

struct multiboot_tag_smbios
{
  uint32 type;
  uint32 size;
  uint8 major;
  uint8 minor;
  uint8 reserved[6];
  uint8 tables[0];
};

struct multiboot_tag_acpi
{
  uint32 type;
  uint32 size;
  uint8 rsdp[0];
};

struct multiboot_tag_network
{
  uint32 type;
  uint32 size;
  uint8 dhcpack[0];
};

struct multiboot_tag_efi_mmap
{
  uint32 type;
  uint32 size;
  uint32 descr_size;
  uint32 descr_vers;
  uint8 efi_mmap[0];
}; 

struct multiboot_tag_efi32_ih
{
  uint32 type;
  uint32 size;
  uint32 pointer;
};

struct multiboot_tag_efi64_ih
{
  uint32 type;
  uint32 size;
  uint64 pointer;
};

struct multiboot_tag_load_base_addr
{
  uint32 type;
  uint32 size;
  uint32 load_base_addr;
};

struct mboot_info_t
{
    uint32 name;
    uint32 maps;
    struct multiboot_tag_framebuffer *mboot_fb;
    struct multiboot_tag_acpi *mboot_acpi;
    multiboot_memory_map_t *mboot_mmap;
}__attribute__((packed));

void *get_mboot_info(uint8 type);

#endif /*  ! ASM_FILE */
     
#endif /*  ! HEADER */
