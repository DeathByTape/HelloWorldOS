/**
 * kernel/kernel.c
 *
 * C implementation of kernel methods
 *
 * Author: Dennis J. McWherter, Jr.
 * MIT Lincoln Laboratory
 */

#include "kernel.h"
#include "mem/gdt.h"
#include "mem/idt.h"

// lib
#include "lib/k_stdio.h"

// Drivers
#include "drivers/video.h"

static int init_drivers();

int kernel_init(int magic, multiboot_info_t* info)
{
  // TODO: Fix this later
/*  if(magic != MULTIBOOT_COMPLIANT) {
    k_panic("GRUB failed to load properly");
    return -1;
  } */

  if(init_drivers() != 0) {
    k_panic("Could not initialize drivers");
    return -1; // Failed to initialize our drivers
  }

  if(!gdt_init()) {
    k_panic("Could not initialize gdt");
    return -1;
  }

  if(!idt_init()) {
    k_panic("Could not initialize idt");
    return -1;
  }

  return 0;
}

void kernel_main()
{
  k_printf("Sample: %d, %d, 0x%x, 0x%x, 0x%x, %d, %d", 10, 111, 10, 0x1337, 0, 0, -50042);
}

int init_drivers()
{
  return (video_init());
}

