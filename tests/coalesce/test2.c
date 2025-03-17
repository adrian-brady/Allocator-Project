// Test: Check for coalescing free space with larger allocations
#include "heap.h"
#include <assert.h>
#include <stdlib.h>

int main() {
  assert(init_heap(PAGE_SIZE) == 0);

  void *ptr[4];
  ptr[0] = alloc(1600);
  assert(ptr[0] != NULL);
  ptr[1] = alloc(1600);
  assert(ptr[1] != NULL);
  ptr[2] = alloc(1600);
  assert(ptr[2] != NULL);
  ptr[3] = alloc(1600);
  assert(ptr[3] != NULL);

  while (alloc(1600) != NULL)
    ;

  assert(free_block(ptr[2]) == 0);
  ptr[2] = alloc(4800);
  assert(ptr[2] == NULL); // Allocation fails

  assert(free_block(ptr[1]) == 0);
  ptr[2] = alloc(4800);
  assert(ptr[2] == NULL); // Allocation fails

  ptr[2] = alloc(1600);
  assert(ptr[2] != NULL); // Allocation succeeds

  assert(free_block(ptr[2]) == 0);
  assert(free_block(ptr[3]) == 0);
  ptr[2] = alloc(2400);
  assert(ptr[2] != NULL); // Allocation succeeds

  exit(0);
}
