// Test: Verify that the first pointer returned is 8-byte aligned
#include "heap.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
  assert(init_heap(PAGE_SIZE) == 0);
  int *ptr = (int *)alloc(sizeof(int));
  assert(ptr != NULL);
  assert(((uintptr_t)ptr) % 8 == 0);
  exit(0);
}
