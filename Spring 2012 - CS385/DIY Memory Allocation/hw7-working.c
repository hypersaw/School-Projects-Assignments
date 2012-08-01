#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* top;
void* bottom;
int freeChunks;
// guaranteed to be called only once
void init_mymalloc() {
	top = sbrk(0);
	//printf("top: %x\n",top);
	bottom = top;
	freeChunks = 0;
}

void* mymalloc(int size) {

	// Start by making the size even
	if((size & 1) == 1)
		++size;
	int chunksize = sizeof(int) + size + sizeof(int);
	if(chunksize < 16) chunksize = 16;

	if(top+chunksize > sbrk(0)) {
		if((int)sbrk(chunksize)==-1) {
			perror("In mymalloc(), calling sbrk.");
			return 0;
		}
	}

	char* beginningOfBlock = top;
	top += chunksize;
	*((int*)beginningOfBlock) = chunksize | 1;
	char* sizePtr = top - 4;
	*((int*)sizePtr) = chunksize;

	return beginningOfBlock + sizeof(int);
}

void myfree(void* alloc) {
	++freeChunks;
	// Set status to unused
	char* beginningOfBlock = alloc - 4;
	*((int*)beginningOfBlock) ^= 1;

	// BEGIN COALESCING
	// Move to beginning of previous block
	char* previousBlock = beginningOfBlock - 4;
	// Make sure this isn't the first allocation
	if(previousBlock > (char*)bottom){
		int blockSize = *((int*)previousBlock);
		previousBlock = beginningOfBlock - blockSize;

		// Now check block's status
		if((*((int*)previousBlock) & 1) == 0){
			// Block is free, we want to combine
			int newFreeBlockSize = *((int*)beginningOfBlock);
			*((int*)previousBlock) += newFreeBlockSize;
			char* endOfBlock = previousBlock + *((int*)previousBlock) - 4;
			*((int*)endOfBlock) = *((int*)previousBlock);
			beginningOfBlock = previousBlock;
			--freeChunks;
		}
	}

	// Move to beginning of next block
	int blockSize = *((int*)beginningOfBlock);
	char* nextBlock = beginningOfBlock + blockSize;

	int movedBreak = 0;
	if(nextBlock != top){
		// This isn't the break, so check status
		if((*((int*)nextBlock) & 1) == 0){
			int nextBlockSize = *((int*)nextBlock);
			*((int*)beginningOfBlock) += nextBlockSize;
			char* endOfBlock = beginningOfBlock + *((int*)beginningOfBlock) - 4;
			*((int*)endOfBlock) = *((int*)beginningOfBlock);
			--freeChunks;
		}
	}
	else{
		--freeChunks;
		movedBreak = 1;
		int moveHeap = 0 - blockSize;
		//printf("top is now %x\n",top);
		if((int)sbrk(-blockSize)==-1) {
			perror("In mymalloc(), calling sbrk.");
			return 0;
		}
		top = sbrk(0);
		//printf("Moved break down by %x (%x), top is now %x\n",blockSize,moveHeap,top);
	}
	// END COALESCING
}
