// Test: Allocations in multiples of 4 bytes checked for alignment
#include "heap.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
  assert(init_heap(PAGE_SIZE) == 0);
  int *ptr[4];

  ptr[0] = (int *)alloc(4);
  ptr[1] = (int *)alloc(8);
  ptr[2] = (int *)alloc(16);
  ptr[3] = (int *)alloc(24);

  for (int i = 0; i < 4; i++) {
    assert(ptr[i] != NULL);
  }

  for (int i = 0; i < 4; i++) {
    assert(((uintptr_t)ptr[i]) % 8 == 0);
  }

  exit(0);
}
