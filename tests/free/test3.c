// Test: A few allocations in multiples of 4 bytes followed by frees
#include "heap.h"
#include <assert.h>
#include <stdlib.h>

int main() {
  assert(init_heap(PAGE_SIZE) == 0);

  void *ptr[8];
  ptr[0] = alloc(16);
  ptr[1] = alloc(16);
  ptr[2] = alloc(32);
  ptr[3] = alloc(32);
  ptr[4] = alloc(48);
  ptr[5] = alloc(48);
  ptr[6] = alloc(64);
  ptr[7] = alloc(64);

  assert(free_block(ptr[0]) == 0);
  assert(free_block(ptr[3]) == 0);
  assert(free_block(ptr[5]) == 0);
  assert(free_block(ptr[6]) == 0);

  ptr[3] = alloc(32);
  assert(ptr[3] < ptr[4]);

  ptr[0] = alloc(16);
  assert(ptr[0] < ptr[1]);

  exit(0);
}
