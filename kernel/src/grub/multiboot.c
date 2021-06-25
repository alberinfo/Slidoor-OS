#include "multiboot.h"

struct mboot_info_t *mboot_info;

void GetUsableMem(uint64 addr, uint64 kernel_end)
{
    struct multiboot_tag *mtag = addr + 8;
    for(mtag = addr+8; mtag->type != multiboot_tag_TYPE_END; mtag = (uint8*)mtag + ((mtag->size + 7) & ~7))
    {
        if(mtag->type == multiboot_tag_TYPE_MMAP)
        {
            multiboot_memory_map_t *mmap;
            for(mmap = ((struct multiboot_tag_mmap*)mtag)->entries; (uint8*)mmap < (uint8*)mtag + mtag->size; mmap = (multiboot_memory_map_t*)((uint64)mmap + ((struct multiboot_tag_mmap*)mtag)->entry_size))
            {
                if(mmap->type != 5)
                {
                    vmmap(mmap->addr, mmap->addr + 0xFFFF800000000000, mmap->len, 3);
                    if(mmap->type == 1)
                    {
                        if(mmap->addr > kernel_end)
                        {
                            heapAddBlock((uint64)mmap->addr + 0xFFFF800000000000, mmap->len);
                        } else if(mmap->len + mmap->addr > kernel_end) {
                            heapAddBlock(kernel_end + 0xFFFF800000000000, mmap->len - kernel_end);
                        }
                    }
                }
            }
            break;
        }
    }
}

int parseMultiboot(uint64 addr, uint64 kernel_end)
{
    kernel_end -= 0xFFFF800000000000;
    GetUsableMem(addr, kernel_end);
    mboot_info = kmalloc(sizeof(struct mboot_info_t));
    struct multiboot_tag *mtag;
    for(mtag = addr+8; mtag->type != multiboot_tag_TYPE_END; mtag = (uint8*)mtag + ((mtag->size + 7) & ~7))
    {
        switch(mtag->type)
        {
            case multiboot_tag_TYPE_CMDLINE:
                /*print("Command line is ");
                print(((struct multiboot_tag_string*)mtag)->string);
                print("\n");*/
                break;
            case multiboot_tag_TYPE_BOOT_LOADER_NAME:
                mboot_info->name = ((struct multiboot_tag_string*)mtag)->string;
                break;
            case multiboot_tag_TYPE_MODULE:
                break;
            case multiboot_tag_TYPE_BASIC_MEMINFO:
                break;
            case multiboot_tag_TYPE_BOOTDEV:
                break;
            case multiboot_tag_TYPE_MMAP:
            {
                mboot_info->mboot_mmap = kmalloc(20 * sizeof(multiboot_memory_map_t)/*8*/); //Up to 20 maps (each one is a memory pointer, so only counts as 8 bytes (64bits) per address)
                multiboot_memory_map_t *mmap;
                int tmp = 0;
                for(mmap = ((struct multiboot_tag_mmap*)mtag)->entries; (uint8*)mmap < (uint8*)mtag + mtag->size; mmap = (multiboot_memory_map_t*)((uint64)mmap + ((struct multiboot_tag_mmap*)mtag)->entry_size))
                {
                    //mboot_info->mboot_mmap[tmp] = kmalloc(sizeof(multiboot_memory_map_t));
                    multiboot_memory_map_t *lel = &mboot_info->mboot_mmap[tmp];
                    lel->addr = mmap->addr;
                    lel->len = mmap->len;
                    lel->type = mmap->type;
                    tmp++;
                }
                mboot_info->maps = tmp;
                break;
            }
            case multiboot_tag_TYPE_VBE:
                break;
            case multiboot_tag_TYPE_FRAMEBUFFER: ;
                mboot_info->mboot_fb = kmalloc(sizeof(struct multiboot_tag_framebuffer));
                struct multiboot_tag_framebuffer *fbtag = (struct multiboot_tag_framebuffer*)mtag;
                *mboot_info->mboot_fb = *fbtag;
                break;
            case multiboot_tag_TYPE_ELF_SECTIONS:
                break;
            case multiboot_tag_TYPE_APM:
                break;
            case multiboot_tag_TYPE_EFI32:
                break;
            case multiboot_tag_TYPE_EFI64:
                break;
            case multiboot_tag_TYPE_SMBIOS:
                break;
            case multiboot_tag_TYPE_ACPI_OLD:
                break;
            case multiboot_tag_TYPE_ACPI_NEW:
                break;
            case multiboot_tag_TYPE_NETWORK:
                break;
            case multiboot_tag_TYPE_EFI_MMAP:
                break;
            case multiboot_tag_TYPE_EFI_BS:
                break;
            case multiboot_tag_TYPE_EFI32_IH:
                break;
            case multiboot_tag_TYPE_EFI64_IH:
                break;
            case multiboot_tag_TYPE_LOAD_BASE_ADDR:
                break;
        }
    }
}

void *get_mboot_info(uint8 type) //Get a ptr to the info
{
    if(type == multiboot_tag_TYPE_BOOT_LOADER_NAME)
    {
        return mboot_info->name;
    } else if(type == 23) {
        return (void*)mboot_info->maps;
    } else if(type == multiboot_tag_TYPE_MMAP) {
        return (void*)mboot_info->mboot_mmap;
    } else if(type == multiboot_tag_TYPE_FRAMEBUFFER) {
        return (void*)mboot_info->mboot_fb; //Its already a pointer
    }
    return 0;
}
