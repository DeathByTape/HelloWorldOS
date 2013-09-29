/**
 * kernel/mem/paging.c
 *
 * Setup our paging structures, etc.
 *
 * Author: Dennis J. McWherter, Jr.
 * MIT Lincoln Laboratory
 */

#include "paging.h"

extern unsigned KERNEL_VIRT_BASE;
#define KERNEL_PDE_INDEX (KERNEL_VIRT_BASE >> 22)

// Look at figures 4-5 and 4-6 in Intel Manual
// as well as the text in section 4.2
// for more information on how I came up with this
static unsigned __attribute__((__packed__)) __attribute__((aligned(0x1000))) page_directory[1024];
static unsigned __attribute__((__packed__)) __attribute__((aligned(0x1000))) page_tables[1024][1024];

int pging_init()
{
  int i = 0, j = 0;
  unsigned* pd = (unsigned*)(page_directory - KERNEL_VIRT_BASE);
  unsigned** pt = (unsigned**)(page_tables - KERNEL_VIRT_BASE);

  // Clear our entire page table structure
  for(i = 0 ; i < 1024 ; ++i) {
    pd[i] = 0;
    for(j = 0 ; j < 1024 ; ++j) {
      pt[i][j] = 0;
    }
  }

  // Now setup a direct mapping
  pd[0] = ((unsigned)*pt) | 0x03; // Physical address of page table followed by control bits
  pd[KERNEL_PDE_INDEX] = ((unsigned)*pt) | 0x03; // Map for 0xc0000000

  // Page table 0 is a direct map to memory
  for(i = 0 ; i < 1024 ; ++i) {
    // Direct map to phys memory
    pt[0][i] = ((i & 0x3ff) << 12) | 0x03; 
  }

  return 1;
}

