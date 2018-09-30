#include<stdio.h>
#include<kernel/tty.h>
#include<kernel/io.h>
#include<stdint.h>
#include<kernel/gdt.h>
#include<kernel/idt.h>
#include<kernel/interrupts.h>
#include<kernel/kb.h>



void kernel_early()
{
  terminal_initialize();
  gdt_install();
}

void kernel_main()
{
  idt_install();
  keyboard_install();
  

  printf("BasedOS:-$");
  
}

