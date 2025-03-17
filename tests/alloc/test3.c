// Example: Multiple odd-sized memory allocations using a custom heap
#include "heap.h"
#include <assert.h>
#include <stdlib.h>

int main() {
  assert(init_heap(PAGE_SIZE) == 0);

  assert(alloc(1) != NULL);  // Allocate 1 byte
  assert(alloc(5) != NULL);  // Allocate 5 bytes
  assert(alloc(14) != NULL); // Allocate 14 bytes
  assert(alloc(8) != NULL);  // Allocate 8 bytes
  assert(alloc(1) != NULL);  // Allocate 1 byte
  assert(alloc(4) != NULL);  // Allocate 4 bytes
  assert(alloc(55) != NULL); // Allocate 55 bytes
  assert(alloc(9) != NULL);  // Allocate 9 bytes
  assert(alloc(33) != NULL); // Allocate 33 bytes

  exit(0);
}
