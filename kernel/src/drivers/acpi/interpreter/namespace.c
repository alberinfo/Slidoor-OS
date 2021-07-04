#include "namespace.h"

struct AcpiNamespaceBlock_t *root;

void AcpiInitNamespace(void)
{
	root = kmalloc(sizeof(struct AcpiNamespaceBlock_t));
	memzero(root, sizeof(struct AcpiNamespaceBlock_t));
	root->name = kmalloc(2);
	strncpy(root->name, "\\\0", 2);
	root->full_name = kmalloc(2);
	strncpy(root->full_name, "\\\0", 2);
}

void *AcpiWalkNamespaceCustomRoot(void *CRoot, string destination)
{
	struct AcpiNamespaceBlock_t *current_node = CRoot; //Custom Root
	if(strEql(current_node->full_name, destination)) return current_node;
	struct AcpiNamespaceBlockChildList_t *current_childs = current_node->childs;
	
	for(int i = 0; i < current_node->child_amount; i++, current_childs = current_childs->next)
	{
		void *ptr = AcpiWalkNamespaceCustomRoot(current_childs->child_ptr, destination);
		if(ptr) return ptr;
	}
	return 0; //DESTINATION DOES NOT EXIST IN THE NAMESPACE!
}

void *AcpiWalkNamespace(string destination)
{
	return AcpiWalkNamespaceCustomRoot(root, destination); //We always start in the root
}

void AcpiCreateNamespaceBlock(struct AcpiNamespaceBlock_t *parent, struct AcpiNamespaceBlock_t *block)
{
	struct AcpiNamespaceBlock_t *current_node = parent;
	current_node->child_amount++;

	uint32 n = strlen(current_node->full_name);
	block->full_name = kmalloc(strlen(current_node->full_name) + strlen(block->name));

	memcpy_fast(block->full_name, current_node->full_name, n);
	if(current_node != root) {char dot = '.'; strncpy(block->full_name+n, &dot, 1);n++;}
	memcpy_fast(block->full_name+n, block->name, 4);
	block->full_name[n+4] = '\0';
	block->parent = current_node;

	struct AcpiNamespaceBlockChildList_t *current_childs;
	if(current_node->child_amount > 1)
	{
		current_childs = current_node->last_child;
		current_childs->next = kmalloc(8);
		current_node->last_child = current_childs = current_childs->next;
	} else {
		current_node->childs = kmalloc(8);
		current_node->last_child = current_node->childs;
		current_childs = current_node->childs;
	}
	current_childs->child_ptr = block;

	return;
}

void AcpiDeleteNamespaceBlockCustomRoot(void *CRoot)
{
	struct AcpiNamespaceBlock_t *current_node = CRoot;
	struct AcpiNamespaceBlockChildList_t *current_childs = current_node->childs;
	for(int i = 0; i < current_node->child_amount; i++, current_childs = current_childs->next)
	{
		AcpiDeleteNamespaceBlockCustomRoot(current_childs->child_ptr);
	}
	free(current_childs);
	free(current_node->parent);
	memzero(current_node, sizeof(struct AcpiNamespaceBlock_t));
	return;
}

void AcpiDeleteNamespaceBlock(string node)
{
	struct AcpiNamespaceBlock_t *current_node = AcpiWalkNamespace(node);
	struct AcpiNamespaceBlock_t *parent_node = current_node->parent;
	struct AcpiNamespaceBlockChildList_t *current_childs = current_node->childs, *prev_child = 0;
	
	for(int i = 0; i < parent_node->child_amount; i++, current_childs = current_childs->next)
	{
		if(current_childs->child_ptr == node)
		{
			AcpiDeleteNamespaceBlockCustomRoot(current_childs->child_ptr);
			if(prev_child == 0)
			{
				if(i < current_node->child_amount) current_node->childs = current_childs->next;
				else {current_node->childs = 0; current_node->last_child = 0;}
			} else {
				if(i < current_node->child_amount) prev_child->next = current_childs->next;
				else {prev_child->next = 0; current_node->last_child = prev_child;}
			}
			parent_node->child_amount--;
			memzero(current_childs->child_ptr, sizeof(struct AcpiNamespaceBlock_t));
			break;
		}
	}

	return;
}

void Dumpthatacpi(void *root)
{
	struct AcpiNamespaceBlock_t *current_node = root;
	printf("[DUMP] %s, %s, %x\n", current_node->full_name, current_node->name, current_node->type);
	struct AcpiNamespaceBlockChildList_t *current_childs = current_node->childs;
	for(int i = 0; i < current_node->child_amount; i++, current_childs = current_childs->next)
	{
		Dumpthatacpi(current_childs->child_ptr);
	}
}

void AcpiDumpNamespace(void)
{
	Dumpthatacpi(root);
}