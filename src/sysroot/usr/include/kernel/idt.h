#ifndef _KERNEL_IDT_H_
#define _KERNEL_IDT_H_

#include <stdio.h>

#define IDT_NUM_ENTRIES 256

void idt_install();
void idttest();

#endif
