#include "namespace.h"

struct AcpiNamespaceBlock_t *root;

void AcpiInitNamespace(void)
{
	root = kmalloc(sizeof(struct AcpiNamespaceBlock_t));
	memzero(root, sizeof(struct AcpiNamespaceBlock_t));
	root->name = "\\";
	root->full_name = "\\";
}

void *AcpiWalkNamespaceCustomRoot(void *CRoot, string destination)
{
	struct AcpiNamespaceBlock_t *current_node = CRoot; //Custom Root
	if(memcmp(current_node->name, destination, 4) == 0) return current_node;
	for(int i = 0; i < current_node->child_amount; i++)
	{
		struct AcpiNamespaceBlock_t *child_node = current_node->child[i];
		void *ptr = AcpiWalkNamespaceCustomRoot(child_node, destination);
		if(ptr) return ptr;
	}
	return 0; //DESTINATION DOES NOT EXIST IN THE NAMESPACE!
}

void *AcpiWalkNamespace(string destination)
{
	if(strcmp(destination, root->name) == 0) return root;
	return(AcpiWalkNamespaceCustomRoot(root, destination)); //We always start in the root
}

void AcpiCreateNamespaceBlock(string parent, struct AcpiNamespaceBlock_t *block)
{
	struct AcpiNamespaceBlock_t *current_node = AcpiWalkNamespace(parent);
	if(current_node == 0) return;
	current_node->child_amount++;
	block->full_name = kmalloc(strlen(current_node->full_name) + strlen(block->name));
	if(current_node != root) {char dot = '.'; memcpy(block->full_name, &dot, 1);}
	memcpy(block->full_name+strlen(block->full_name), current_node->full_name, strlen(current_node->full_name));
	memcpy(block->full_name+strlen(block->full_name), block->name, 4);
	if(current_node->child_amount > 1)
	{
		uint64 *new_addr = kmalloc(current_node->child_amount * 8); //8 bytes per each addr;
		memcpy_fast(new_addr, current_node->child, (current_node->child_amount-1)*8);
		free(current_node->child);
		new_addr[current_node->child_amount-1] = block;
		current_node->child = new_addr;
	} else {
		current_node->child = kmalloc(8);
		current_node->child[0] = block;
	}
	return;
}

void AcpiDeleteNamespaceBlockCustomRoot(void *CRoot)
{
	struct AcpiNamespaceBlock_t *current_node = CRoot;
	for(int i = 0; i < current_node->child_amount; i++)
	{
		AcpiDeleteNamespaceBlockCustomRoot(current_node->child[i]);
	}
	free(current_node->child);
	free(current_node->parent);
	memzero(current_node, sizeof(struct AcpiNamespaceBlock_t));
	return;
}

void AcpiDeleteNamespaceBlock(string node)
{
	struct AcpiNamespaceBlock_t *current_node = AcpiWalkNamespace(node);
	struct AcpiNamespaceBlock_t *parent_node = current_node->parent;
	for(int i = 0; i < parent_node->child_amount; i++)
	{
		if(parent_node->child[i] == node)
		{
			memcpy_fast(parent_node->child+i, parent_node->child+i+1, sizeof(struct AcpiNamespaceBlock_t) * (parent_node->child_amount-i));
			parent_node->child_amount--;
			uint64 *new_ptr = kmalloc(current_node->child_amount * sizeof(struct AcpiNamespaceBlock_t));
			memcpy_fast(new_ptr, parent_node->child, current_node->child_amount * sizeof(struct AcpiNamespaceBlock_t));
			free(parent_node->child);
			parent_node->child = new_ptr;
			break;
		}
	}

	AcpiDeleteNamespaceBlockCustomRoot(parent_node);
	return;
}

/*void Dumpthatacpi(void *root)
{
	struct AcpiNamespaceBlock_t *current_node = root;
	printf("[DUMP] %s, %x, %i\n", current_node->full_name, current_node->name, current_node->type);
	for(int i = 0; i < current_node->child_amount; i++)
	{
		Dumpthatacpi(current_node->child[i]);
	}
}

void AcpiDumpNamespace(void)
{
	while(1);
	Dumpthatacpi(root);
}*/

uint8 *AcpiGetAml(void)
{
	uint8 *buf = kmalloc(4096); int i = 0, o = 0;
	uint8 *ptr = acpi_pm_info->facp->DSDT;
	uint8* packagePtr = ((char*)ptr + 36);
    int dsdtLength = (*(uint32*)((char*)ptr + 4)) - 36;
    while(dsdtLength--) buf[i] = packagePtr[i++];
    /*dsdtLength = (dsdtLength / 2) * 2 != dsdtLength ? dsdtLength / 2 + 1 : dsdtLength / 2;
    while(dsdtLength--)
    {
    	uint16 temp = packagePtr[i++];
    	buf[o++] = temp >> 8;
    	buf[o++] = temp & 0xFF;
    }*/
    return buf;
}