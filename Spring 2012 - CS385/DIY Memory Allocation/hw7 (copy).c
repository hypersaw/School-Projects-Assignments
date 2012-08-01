#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void* top;
void* bottom;
void* freeList;
// guaranteed to be called only once
void init_mymalloc(){
	top = sbrk(0);
	bottom = top;
	freeList = NULL;
}

void* mymalloc(int size){

	// Start by making the size even
	if((size & 1) == 1)
		size++;

	// We want size + 12 bytes (size/status and size)
	unsigned int chunksize = sizeof(int) + size + sizeof(int);

	// If size was less than 8, round up
	if(chunksize < 16)
		chunksize = 16;

	char* crntElement = freeList;
	char* prevElement = NULL;

	// If we have free chunks available
	if(freeList != NULL){
		// If we have a chunk that is small than what we need, allocate the size by setting
		// up the block manually, AS WELL as setting up the unused segment (size/status).
		// We subtract 9 to make sure we will have room for two ints and a char*
		while((crntElement + 4) != NULL){
			if(chunksize < *((int*)crntElement - 12)){
				// Set up our allocated space
				int freeBlockSize = *((int*)crntElement) - chunksize;
				*((int*)crntElement) = chunksize | 1;
				char* endOfBlock = crntElement + chunksize - 4;
				*((int*)endOfBlock) = chunksize;

				endOfBlock += 4;	// Point to our new free block
				*((int*)endOfBlock) = freeBlockSize;
				endOfBlock += (freeBlockSize - 4);
				*((int*)endOfBlock) = freeBlockSize;

				return crntElement + sizeof(int);
			}
			if(chunksize == *((int*)crntElement)){
				*((int*)crntElement) |= 1;

				// If this is the first element then
				// we want crntElement->Next to be the first
				if(prevElement == NULL)
					freeList = (crntElement + 4);
				// Otherwise set prev->Next to crnt->Next
				else{
					char* prevNext = prevElement + 4;
					prevNext = (crntElement + 4);

				return crntElement + sizeof(int);
				}
			}
			if(chunksize > *((int*)crntElement)){
				prevElement = crntElement;
				crntElement = (crntElement + 4);
			}
		}
	}
	// If the top of our used heap space plus the chunksize is beyond
	// the allowed heap space we want to call sbrk
	if(top+chunksize > sbrk(0)) {
		// Call sbrk, if fails print error
		if((int)sbrk(chunksize)==-1) {
			perror("In mymalloc(), calling sbrk.");
			return 0;
		}
	}

	char* beginningOfBlock = top;		// Keep track of pointer to beginning of block
	top += chunksize;			// Move our top pointer
	*((int*)beginningOfBlock) = chunksize | 1;	// We want to set the size/status LSB to 1 (in use)
	char * sizePtr = top - 4;		// Move ptr to last 4 bytes of block
	*((int*)sizePtr) = chunksize;			// Set the size at the end of our block

	return beginningOfBlock + sizeof(int);		// Return pointer to beginning of user space
}

// Merge our surrounding free blocks together
// Once we have one free block we will check to see if
// it is adjacent to the break.
void myfree(void* alloc){
	// Start off by finding where our break is
	char* topOfHeap = sbrk(0);

	// Set status to unused
	char* beginningOfBlock = alloc - 4;
	*((int*)beginningOfBlock) ^= 1;

	// Move to beginning of previous block
	char* previousBlock = beginningOfBlock - 4;
	if(previousBlock > (char*)bottom){
		int blockSize = *((int*)previousBlock);
		previousBlock = beginningOfBlock - blockSize;			// We are now pointing at beginning of Prev block

		// Now check block's status
		if((*((int*)previousBlock) & 1) == 0){		// Cast previousBlock as int*, then dereference it
			// Block is free, we want to combine
			int newFreeBlockSize = *((int*)beginningOfBlock);
			*((int*)previousBlock) += newFreeBlockSize;			// Prev + newBlock
			char* endOfBlock = previousBlock + *((int*)previousBlock) - 4;		// Set to end of new block (size)
			*((int*)endOfBlock) = *((int*)previousBlock);				// Update 2nd size to combined size
			beginningOfBlock = previousBlock;			// Set our beginning ptr to previous
		}
	}

	// Move to beginning of next block
	int blockSize = *((int*)beginningOfBlock);
	char* nextBlock = beginningOfBlock + blockSize;

	// Make sure we are not adjacent to the break
	int movedBreak = 0;
	if(nextBlock != topOfHeap){
		// Now check block's status
		if((*((int*)nextBlock) & 1) == 0){
			int nextBlockSize = *((int*)nextBlock);
			*beginningOfBlock += nextBlockSize;
			char* endOfBlock = beginningOfBlock + *((int*)beginningOfBlock) - 4;
			*((int*)endOfBlock) = *((int*)beginningOfBlock);
		}
	}
	else{
		movedBreak = 1;
		if((int)sbrk(-blockSize)==-1) {
			perror("In mymalloc(), calling sbrk.");
			return 0;
		}
		top = sbrk(0);	// Move break down
	}

	// Now that we have one block, we will work on our free list.
	// If we have an empty free list then set this block as the first item
	// BUT FIRST, we check to see if we moved the break. If we did, we don't care
	if(movedBreak == 0){
		if(freeList == NULL){
			freeList = beginningOfBlock;
			int* nextPtr = (int*)beginningOfBlock + 1;
			nextPtr = NULL;
		}
		// Otherwise, we want to set the Next node
		// on the last element to this new block
		// We access the last element by moving through
		// our list
		else{
			char* elementPtr = freeList;
			char* currNext = elementPtr + 4;
			while(currNext != NULL)
				elementPtr += 4;
			currNext = beginningOfBlock;
		}
	}
}
