//low level functions for addressing the terminal

#ifndef _KERNEL_TTY_H //this prevents the contents of this header file being included twice
#define _KERNEL_TTY_H

#include <stddef.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void t_backspace(void);

#endif
