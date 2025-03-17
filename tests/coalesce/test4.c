// Test: Check for coalescing free space with larger adjacent blocks
#include "heap.h"
#include <assert.h>
#include <stdlib.h>

int main() {
  assert(init_heap(PAGE_SIZE) == 0);

  void *ptr[4];
  ptr[0] = alloc(800);
  assert(ptr[0] != NULL);
  ptr[1] = alloc(800);
  assert(ptr[1] != NULL);
  ptr[2] = alloc(800);
  assert(ptr[2] != NULL);
  ptr[3] = alloc(800);
  assert(ptr[3] != NULL);

  while (alloc(800) != NULL)
    ;

  assert(free_block(ptr[0]) == 0);
  assert(free_block(ptr[1]) == 0);

  assert((ptr[1] = alloc(1600)) != NULL); // Allocation succeeds

  exit(0);
}
