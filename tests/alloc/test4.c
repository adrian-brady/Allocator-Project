// Test: Allocation is too big to fit in the heap
#include "heap.h"
#include <assert.h>
#include <stdlib.h>

int main() {
  assert(init_heap(PAGE_SIZE) == 0);
  assert(alloc(1) != NULL);
  assert(alloc(PAGE_SIZE - 1) == NULL);
  exit(0);
}
