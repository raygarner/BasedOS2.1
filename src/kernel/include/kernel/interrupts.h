#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include <stdbool.h> //provided by compiler
#include <stdint.h>

#define KEYBOARD_IDT_INDEX 33
#define SYSCALL_IDT_INDEX 128

// stores the values in the registers at the time of the interrupt
struct regs {
  uint32_t gs, fs, es, ds;                          // pushed the segs last
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  // pushed by pusha
  uint32_t idt_index, err_code;                     // manually pushed
  uint32_t eip, cs, eflags, useresp, ss;            // pushed automatically
};


typedef void (*interrupt_handler_t)(struct regs* r);

bool register_interrupt_handler(uint32_t idt_index,
	                            interrupt_handler_t handler);

void run_interrupt_handler(struct regs* r);

#endif //_INTERRUPT_H_