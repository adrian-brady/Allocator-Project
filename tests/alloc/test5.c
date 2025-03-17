// Test: Second allocation is too big to fit in the remaining heap space
#include "heap.h"
#include <assert.h>
#include <stdlib.h>

int main() {
  assert(init_heap(PAGE_SIZE) == 0);
  assert(alloc(PAGE_SIZE / 2) != NULL);
  assert(alloc((PAGE_SIZE / 2) - 1) == NULL);
  exit(0);
}
