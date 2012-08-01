#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void* top;
void* bottom;
char* freeList;
int usedChunks;
// guaranteed to be called only once
void init_mymalloc(){
	top = sbrk(0);
	bottom = top;
	freeList = NULL;
	usedChunks = 0;
}

void* mymalloc(int size){
	++usedChunks;
	// Start by making the size even
	if((size & 1) == 1)
		size++;

	// We want size + 12 bytes (size/status and size)
	unsigned int chunksize = sizeof(int) + size + sizeof(int);

	// If size was less than 8, round up
	if(chunksize < 16)
		chunksize = 16;

	// If we have free chunks available
	if(freeList != NULL){
		char* currentElement = freeList;
		char* previousElement = NULL;
		// If we have a chunk that is small than what we need, allocate the size by setting
		// up the block manually, AS WELL as setting up the unused segment (size/status).
		// We subtract 9 to make sure we will have room for two ints and a char*
		while(currentElement != NULL){
			if(chunksize < *((int*)currentElement)){
				// Set up our allocated space
				int freeBlockSize = *((int*)currentElement) - chunksize;
				*((unsigned int*)currentElement) = chunksize | 1;
				char* sizePtr = currentElement + chunksize - 4;
				*((unsigned int*)sizePtr) = chunksize;

				char* endOfBlock = sizePtr + 4;	// Point to our new free block
				*((unsigned int*)endOfBlock) = freeBlockSize;
				sizePtr = endOfBlock + freeBlockSize - 4;
				*((unsigned int*)sizePtr) = freeBlockSize;

				// If this was our first item, this is our new first item
				if(previousElement == NULL){
					freeList = endOfBlock;
					char* nextElement = endOfBlock + 4;
					*nextElement = *(currentElement + 4);
				}
				else{
					char* previousElementPtr = previousElement + 4;
					*previousElementPtr = NULL;
				}

				return currentElement + sizeof(int);
			}
			if(chunksize == *((unsigned int*)currentElement)){
				// Set status bit
				*((unsigned int*)currentElement) |= 1;

				// If our previous was not null, we need currents
				// next to be previous's next
				if(previousElement != NULL){
					char* previousElementPtr = previousElement + 4;
					char* currentElementPtr = currentElement + 4;
					*previousElementPtr = *currentElementPtr;
				}
				else{
					char* currentElementPtr = currentElement + 4;
					freeList = *currentElementPtr;
				}

				return currentElement + sizeof(int);
			}
			if(chunksize > *((unsigned int*)currentElement)){
				char* currentElementPtr = currentElement + 4;
				previousElement = currentElement;
				currentElement = *currentElementPtr;
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
	*((unsigned int*)beginningOfBlock) = chunksize | 1;	// We want to set the size/status LSB to 1 (in use)
	char * sizePtr = top - 4;		// Move ptr to last 4 bytes of block
	*((unsigned int*)sizePtr) = chunksize;			// Set the size at the end of our block

	return beginningOfBlock + sizeof(int);		// Return pointer to beginning of user space
}

// Merge our surrounding free blocks together
// Once we have one free block we will check to see if
// it is adjacent to the break.
void myfree(void* alloc){
	--usedChunks;
	// Set status to unused
	char* beginningOfBlock = alloc - 4;
	*((int*)beginningOfBlock) ^= 1;

	// Move to beginning of previous block
	char* previousBlock = beginningOfBlock - 4;
	if(previousBlock > (char*)bottom){
		unsigned int blockSize = *((unsigned int*)previousBlock);
		previousBlock = beginningOfBlock - blockSize;			// We are now pointing at beginning of Prev block

		// Now check block's status
		if((*((int*)previousBlock) & 1) == 0){		// Cast previousBlock as int*, then dereference it
			// Block is free, we want to combine
			unsigned int newFreeBlockSize = *((unsigned int*)beginningOfBlock);
			*((unsigned int*)previousBlock) += newFreeBlockSize;			// Prev + newBlock
			char* endOfBlock = previousBlock + *((unsigned int*)previousBlock) - 4;		// Set to end of new block (size)
			*((unsigned int*)endOfBlock) = *((unsigned int*)previousBlock);				// Update 2nd size to combined size
			beginningOfBlock = previousBlock;			// Set our beginning ptr to previous
		}
	}

	// Move to beginning of next block
	unsigned int blockSize = *((unsigned int*)beginningOfBlock);
	char* nextBlock = beginningOfBlock + blockSize;

	// Make sure we are not adjacent to the break
	int movedBreak = 0;
	if(nextBlock != top){
		// Now check block's status
		if((*((unsigned int*)nextBlock) & 1) == 0){
			int nextBlockSize = *((unsigned int*)nextBlock);
			*beginningOfBlock += nextBlockSize;
			char* endOfBlock = beginningOfBlock + *((unsigned int*)beginningOfBlock) - 4;
			*((unsigned int*)endOfBlock) = *((unsigned int*)beginningOfBlock);
		}
	}
	else{
		movedBreak = 1;
		if((int)sbrk(-blockSize)==-1)
			perror("In mymalloc(), calling sbrk.");
		top = sbrk(0);	// Move break down
		if(top == bottom)
			freeList = NULL;
	}

	// Now that we have one block, we will work on our free list.
	// If we have an empty free list then set this block as the first item
	// BUT FIRST, we check to see if we moved the break. If we did, we don't care
	if(movedBreak == 0){
		if(freeList == NULL)
			freeList = beginningOfBlock;
		// Otherwise, we want to set the Next node
		// on the last element to this new block
		// We access the last element by moving through
		// our list
		else{
			char* currentElement;
			char* currentElementPtr;
			currentElement = freeList;
			currentElementPtr = *(currentElement + 4);
			while(currentElementPtr != NULL){
				currentElement = *currentElementPtr;
				currentElementPtr = *(currentElement + 4);
			}
			currentElementPtr = beginningOfBlock;
		}
	}
}

