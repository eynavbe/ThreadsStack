#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <math.h>

typedef struct free_block {
    //size we need:int, char, long...
    size_t size;
    //next place
    struct free_block* next;
} free_block;

//init free block
static free_block free_block_list_head = { 0, 0 };
static const size_t overhead = sizeof(size_t);
static const size_t align_to = 16;

void* mymalloc(size_t size) {
    size = (size + sizeof(size_t) + (align_to - 1)) & ~ (align_to - 1);
    //create new free block
    free_block* block = free_block_list_head.next;
    free_block** head = &(free_block_list_head.next);
    //Assigns a memory space according to the size requested
    while (block != 0) {
        //If we have already allocated all the space requested
        if (block->size >= size) {
            *head = block->next;
            return ((char*)block) + sizeof(size_t);
        }
        head = &(block->next);
        block = block->next;
    }

    //sbrk change data segment size
    block = (free_block*)sbrk(size);
    //set block size to be "size"
    block->size = size;

    //return the last address we allocate
    return ((char*)block) + sizeof(size_t);
}
void *calloc(size_t nmemb, size_t size)
{
	char *p;

	// If either is zero just return NULL.
	if (nmemb == 0 || size == 0)
	{
		return NULL;
	}

	// Malloc the area and zero it out.
	else
	{
		p = (char*)mymalloc(nmemb * size);
		bzero(p, nmemb * size);
		return p;
	}
}
//Releases the memory we have allotted
void free(void* ptr) {
    free_block* block = (free_block*)(((char*)ptr) - sizeof(size_t));
    block->next = free_block_list_head.next;
    free_block_list_head.next = block;
}