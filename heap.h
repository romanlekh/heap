#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include <stddef.h>

// Get to pointers with begin and end of memory for heap.
// Be inform that some part (according to default setting 20%,
// but can increase in execution) will be reserve.
void SetMemory(void *ptr1, void *ptr2);

// Allocates a block of size bytes of memory,
// returning a pointer to the beginning of the block.
void* MemLoc(size_t mem_size);

//Deallocate memory block.
// A block of memory previously allocated by a call to MemLoc
// is deallocated, making it available again for further allocations.
void FreeMem(void *ptr);


#endif // HEAP_H_INCLUDED
