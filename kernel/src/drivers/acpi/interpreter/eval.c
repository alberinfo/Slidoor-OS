#include "eval.h"

/*
For reference on AML Encodings, look at uefi.org/sites/default/files/resources/ACPI_6_3_final_Jan30.pdf at section 20
*/

int fucker = 0;

void /*for now void, may be an int*/ AcpiEvalAMLCustomRoot(void *CRoot, uint8 *ptr, uint32 size)
{
	struct AcpiNamespaceBlock_t *current_node = CRoot;
    for(int i = 0; i < size; i++, ptr++)
	{
        if(AML_CheckIsScope(ptr))
        {
            struct AcpiNamespaceBlock_t *block = kmalloc(sizeof(struct AcpiNamespaceBlock_t));
            memzero(block, sizeof(struct AcpiNamespaceBlock_t));

        	uint8 PkgLeadByte = (*(ptr+1) >> 6) + 1; ////This is just the amount of extra pkgSize, actually. >> 6 to get the last 2 bits

            string name = AML_GetName(ptr+PkgLeadByte+1);
            block->name = name;

            block->type = AML_ScopeOp;
            block->size = *(ptr+1)-1;
            block->addr = ptr+PkgLeadByte+4+1; //Lets point directly to the data. might change.

            AcpiCreateNamespaceBlock(current_node, block);
            AcpiEvalAMLCustomRoot(block, block->addr, block->size);

            ptr += block->size+1;
            i += block->size+1;
        } else if(AML_CheckIsDevice(ptr)) {
            struct AcpiNamespaceBlock_t *block = kmalloc(sizeof(struct AcpiNamespaceBlock_t));
            memzero(block, sizeof(struct AcpiNamespaceBlock_t));

            uint8 PkgLeadByte = (*(ptr+2) >> 6) + 1;

            string name = AML_GetName(ptr+PkgLeadByte+2);
            block->name = name;

            block->type = AML_DeviceOp;
            block->size = *(ptr+2)-1;
            block->addr = ptr+PkgLeadByte+4+2; //Lets point directly to the data. might change.
            
            AcpiCreateNamespaceBlock(current_node, block);
            AcpiEvalAMLCustomRoot(block, block->addr, block->size);
            
            ptr += block->size+2;//two bytes for the type
            i += block->size+2;
        } else if(AML_CheckIsPackage(ptr)) { //This might be the declaration of either a variable or a package (or something else im maybe missing out lol)
        	struct AcpiNamespaceBlock_t *block = kmalloc(sizeof(struct AcpiNamespaceBlock_t));
        	memzero(block, sizeof(struct AcpiNamespaceBlock_t));

            uint8 PkgLeadByte = (*(ptr+6) >> 6) + 1;

            string name = AML_GetName(ptr+1);
            block->name = name;

            block->type = AML_PackageOp;
        	block->size = *(ptr+6)-1;
        	block->addr = ptr+6+PkgLeadByte; //We first point to the amount of values in the package.
        	AcpiCreateNamespaceBlock(current_node, block);
            ptr += block->size+6;//The size of the NameOp
        	i += block->size+6;
    	}
	}
}

void AcpiEvalAML(uint8 *ptr, uint32 size)
{
	void *root = AcpiWalkNamespace("\\");
	AcpiEvalAMLCustomRoot(root, ptr, size);
}