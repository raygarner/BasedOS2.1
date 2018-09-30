#include <kernel/idt.h>
#include <kernel/interrupts.h>
#include <kernel/io.h>
#include <stdbool.h> //provided by compiler
#include <stdint.h> //provided by compiler
#include <stdio.h>
#include <string.h>

static interrupt_handler_t interrupt_handlers[IDT_NUM_ENTRIES]; //256 element array

bool register_interrupt_handler(
    uint32_t idt_index, interrupt_handler_t handler) {

  //printf("register interrupt handler called\n");
  
  if (idt_index >= IDT_NUM_ENTRIES){ //if index not in table
    printf("index not in table");
    return false;
  }
  
  if (interrupt_handlers[idt_index] != NULL) { 
    printf("index not null");
    return false;
  }

  interrupt_handlers[idt_index] = handler; //puts the address of the routine in corresponding idt segment
  return true;
}

void fault_handler(/*struct regs *r*/) {
  printf("System Exception. System Halted!\n");
  for (;;);
}

void irq_handler(struct regs *r) {
  // Blank function pointer
  void (*handler)(struct regs * r);

  // If there's a custom handler to handle the IRQ, handle it
  handler = interrupt_handlers[r->idt_index];
  if (handler) {
    handler(r);
  }

  // If the IDT entry that was invoked was greater than 40, sends an EOI
  // to the slave controller
  if (r->idt_index >= 40) {
    outb(0xA0, 0x20);
  }

  // Sends an EOI to the master interrupt controller
  outb(0x20, 0x20);
}

//this function is called from interrupts_asm.S
void run_interrupt_handler(struct regs* r) { //currently this function is not getting called
  //printf("run interrupt handler called\n");
  size_t idt_index = r->idt_index;
  if (idt_index < 32) {
    fault_handler(r);
    return;
  }

  if (idt_index >= 32 && idt_index <= 47) {
    irq_handler(r);
    return;
  }

  if (interrupt_handlers[r->idt_index] != NULL) {
    interrupt_handlers[r->idt_index](r);
  }
}
