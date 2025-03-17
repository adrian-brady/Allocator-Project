// Test: Check for coalescing free space with adjacent blocks
#include "heap.h"
#include <assert.h>
#include <stdlib.h>

int main() {
  assert(init_heap(PAGE_SIZE) == 0);

  void *ptr[5];
  ptr[0] = alloc(500);
  assert(ptr[0] != NULL);
  ptr[1] = alloc(500);
  assert(ptr[1] != NULL);
  ptr[2] = alloc(500);
  assert(ptr[2] != NULL);
  ptr[3] = alloc(500);
  assert(ptr[3] != NULL);
  ptr[4] = alloc(500);
  assert(ptr[4] != NULL);

  while (alloc(500) != NULL)
    ;

  assert(free_block(ptr[1]) == 0);
  assert(free_block(ptr[3]) == 0);
  ptr[3] = alloc(1300);
  assert(ptr[3] == NULL); // Allocation fails (no adjacent coalescing)

  assert(free_block(ptr[2]) == 0);
  ptr[3] = alloc(1300);
  assert(ptr[3] != NULL); // Allocation succeeds (immediate coalescing)

  exit(0);
}
