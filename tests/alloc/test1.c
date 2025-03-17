// Example: Simple 16-byte memory allocation using a custom heap
#include "heap.h"
#include <assert.h>
#include <stdlib.h>

int main() {
  assert(init_heap(PAGE_SIZE) == 0);
  void *ptr = alloc(16);
  assert(ptr != NULL);
  exit(0);
}
