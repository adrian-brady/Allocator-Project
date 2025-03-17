// Test: Write to a block of allocated memory and verify the value
#include "heap.h"
#include <assert.h>
#include <stdlib.h>

int main() {
  assert(init_heap(PAGE_SIZE) == 0);
  int *ptr = (int *)alloc(sizeof(int));
  assert(ptr != NULL);
  *ptr = 42; // Ensure the pointer is in a writable page
  assert(*ptr == 42);
  exit(0);
}
