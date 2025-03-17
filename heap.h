#include <sys/types.h>

#ifndef macos
// MacOS default page size is 16KB, on 32-bit linux this value is 4096
#define PAGE_SIZE 16384
#define ALIGNMENT 16
#endif

#ifndef heap_h
#define heap_h
#define NULL 0

int init_heap(int sizeOfRegion);
void print_heap();

void *alloc(int size);
int free_block(void *ptr);

void *malloc(size_t size) { return NULL; }

#undef NULL

#endif
