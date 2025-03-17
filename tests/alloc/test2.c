// Example: Allocations in multiples of 4 bytes using a custom heap
#include "heap.h"
#include <assert.h>
#include <stdlib.h>

int main() {
  assert(init_heap(PAGE_SIZE) == 0);

  assert(alloc(4) != NULL);  // Allocate 4 bytes
  assert(alloc(8) != NULL);  // Allocate 8 bytes
  assert(alloc(16) != NULL); // Allocate 16 bytes
  assert(alloc(24) != NULL); // Allocate 24 bytes

  exit(0);
}
