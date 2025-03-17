// The goal of this project is to implement an allocator with the following
// specifications. The allocator will utilize an implicit header list to manage
// allocations. The allocation policy will be best-fit.
//
// First, search the whole heap to see if there is a free block with the same
// size as the padded requested block size.
//
// Next, search the whole heap to see if there is a large enough block which
// can fit the requested block size.
//
// Split the free block into two portions. The first portion will be the
//   allocated part, and the second portion will be the free part.
//
// All free blocks will have a footer which is made of a "header" to allow the
// next block to know its size.
//
// A block's header contains the size of the block and the two least significant
// bits of the size are used to indicate the allocation status of the current
// and previous block.

#include "heap.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * The header for each block.
 * Also used as the footer for free blocks.
 */
typedef struct Header {

  /*
   * Requirements
   *
   * The size of each block must be a multiple of 8
   * Blocks contain headers that contain size and status information
   * Free blocks contain a footer which contains the size of the block
   */

  /*
   * Status Information
   *
   * Bit 0 -> least significnt bit/last bit
   * 0: free
   * 1: allocated
   *
   * Bit 1 -> second to last bit
   * 0: previous free
   * 1: previous allocated
   */

  /*
   * Example
   *
   * A block with requested size of 18:
   *  - size would be 24 (padding)
   *  - if allocated -> size would read 25 (24 + 1)
   *  - if previous allocated -> size would read 26 (24 + 2)
   *  - if previous allocated and allocated -> size would read 27 (24 + 2 + 1)
   */

  int size;

} header;

/*
 * You may add global variables as you wish, though this can be implemented
 * without adding more.
 */

/*
 * Gloal variable which holds the address of the starting header of the heap.
 */
header *heap_start = NULL;

/*
 * Size of requested heap allocation size, padded.
 */
int alloc_size;

/*
 * alloc allocates `size` bytes of heap memory.
 *
 * This function will fail on the following cases:
 * - size < 1
 * - unable to find a free block which can fit the requested size.
 *
 * param: size -> requested size for the payload
 * returns:
 * 	- address of payload on success.
 * 	- NULL on failure.
 */
void *alloc(int size) {
  /*
   * Requirements
   *
   * Must determine the size of the block, padded
   * Use best-fit placement policy
   */

  return 0;
}

/*
 * free_block frees a previously allocated block.
 *
 * This function will fail on the following cases:
 * - `ptr` is NULL.
 * - `ptr` is not aligned.
 * - `ptr` is outside of the heap.
 * - `ptr` is already free.
 *
 * param: ptr -> address of the block to be freed.
 * returns:
 *  -  0 -> on success.
 *  - -1 -> on failure.
 */
int free_block(void *ptr) { return 0; }

/*
 * init_heap initializes the memory allocator.
 * Called only once by any program.
 *
 * param: size -> size to be allocated
 * returns:
 *  -  0 -> on success.
 *  - -1 -> on failure.
 */
int init_heap(int size) {

  static int allocated = 0; // prevent multiple myInit calls

  // page size
  int page_size;

  // size of padding when heap size is not a multiple of page
  int padded_size;

  // pointer to memory mapped area
  void *mmap_ptr;

  header *end_marker;

  if (0 != allocated) {
    fprintf(stderr,
            "Error:heap.c: init_heap allocated space in a previous call\n");
    return -1;
  }

  if (size <= 0) {
    fprintf(stderr,
            "Error:heap.c: init_heap Requested block size is not positive\n");
    return -1;
  }

  // Get the pagesize from O.S.
  page_size = getpagesize();

  // Calculate paded_size, as padding is required to round up size to be managed
  // to a multiple of pagesize
  padded_size = size % page_size;
  padded_size = (page_size - padded_size) % page_size;

  alloc_size = size + padded_size;

  // Using mmap to allocate memory
  mmap_ptr = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE,
                  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (MAP_FAILED == mmap_ptr) {
    fprintf(stderr, "Error:heap.c: mmap cannot allocate space\n");
    allocated = 0;
    return -1;
  }

  allocated = 1;

  // reduce size for padding and to add space for the endmarker
  alloc_size -= ALIGNMENT;

  // skip first 4 bytes for alignment
  heap_start = (header *)mmap_ptr + 1;

  end_marker = (header *)((void *)heap_start + alloc_size);
  end_marker->size = 1;

  // Set size in header
  heap_start->size = alloc_size;

  // Set p-bit as allocated in header
  heap_start->size += 2;

  // Set the footer of the free block
  header *footer = (header *)((void *)heap_start + alloc_size - 4);
  footer->size = alloc_size;

  return 0;
}

/* You may change this function.
 *
 * print_heap prints the heap's current status
 *
 * Helps visualize the heap's current structure.
 *
 * Prints a list of all blocks with the following information:
 * - number
 * - status (a -> allocated, f -> free)
 * - previous status (a -> allocated, f -> free)
 * - header address
 * - payload address
 * - footer address (if applicable)
 * - end address
 * - size of the block
 * - footer's reported size
 */
void print_heap() {
  char status[2];
  char p_status[2];
  char *h_address = NULL;
  char *payload_address = NULL;
  char *footer_address = NULL;
  char *end_address = NULL;
  int h_size;
  int f_size;

  header *block = heap_start;
  int counter = 1;

  int used_total = 0;
  int free_total = 0;

  fprintf(stdout, "=========================================== Heap Display "
                  "=============================================\n");
  fprintf(stdout, "No.\tS\tP\th_addr\t\tpld_addr\te_addr\t\th_size\tf_"
                  "addr\t\tf_size\n");
  fprintf(stdout, "------------------------------------------------------------"
                  "--------------------\n");

  while (block->size != 1) { // Ensure block is valid
    h_address = (char *)block;
    payload_address = NULL;
    footer_address = NULL;
    end_address = NULL;
    f_size = 0;
    h_size = block->size & ~3; // Mask out the flags (LSB and 2nd LSB)

    // Determine block status (used or free)
    if (block->size & 1) { // LSB = 1 => used block
      strcpy(status, "A");
      used_total += h_size;
    } else {
      strcpy(status, "F");
      footer_address = h_address + h_size - sizeof(header); // Footer at the end
      free_total += h_size;
    }

    // Determine previous block status
    if (block->size & 2) { // 2nd LSB = 2 => previous block used
      strcpy(p_status, "A");
    } else {
      strcpy(p_status, "F");
    }

    payload_address = h_address + sizeof(header); // Payload starts after header

    end_address = h_address + h_size - 1;
    fprintf(stdout,
            "%d\t%s\t%s\t0x%09lx\t0x%09lx\t0x%09lx\t%4i\t0x%09lx\t%4i\n",
            counter, status, p_status, (unsigned long int)h_address,
            (unsigned long int)payload_address, (unsigned long int)end_address,
            h_size, (unsigned long int)footer_address, f_size);

    // Move to the next block
    block = (header *)((char *)block + h_size);
    counter++;
    if (counter > 5) {
      break;
    }
  }

  fprintf(stdout, "------------------------------------------------------------"
                  "------------------------------------------\n");
  fprintf(stdout, "============================================================"
                  "==========================================\n");
  fprintf(stdout, "Total used = %4d\n", used_total);
  fprintf(stdout, "Total free = %4d\n", free_total);
  fprintf(stdout, "Total size = %4d\n", used_total + free_total);
  fprintf(stdout, "============================================================"
                  "==========================================\n");
  fflush(stdout);

  return;
}
