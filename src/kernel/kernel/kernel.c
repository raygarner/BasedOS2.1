#include<stdio.h>
#include<kernel/tty.h>
#include<kernel/io.h>
#include<stdint.h>
#include<kernel/gdt.h>
#include<kernel/idt.h>



void kernel_early()
{
  terminal_initialize();
  gdt_install();
}

void kernel_main()
{
  printf("BasedOS:-$");
  //idttest();
}

