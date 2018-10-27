//low level functions for addressing the terminal

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

int offset;
int mode; //this variable stores the current display mode eg if in shell mode then mode = 0, if in a program then 1. this is yet to be implemented properly 
					//but it is for the future

void clear_line(){
  terminal_column = 0;
  terminal_writestring("                                                                               "); //writes a line of spaces
  terminal_buffer[24 * 80 + 79] = vga_entry(' ', terminal_color); 
  
  /*
  for(j = 0; j<VGA_WIDTH ;++j)
    terminal_putchar(' ');
  */

  terminal_column = 0;


}


void terminal_scroll(){
  int x;
  int y;

  for(x = 0; x<80; ++x){
    for(y = 0; y<24; ++y){
      terminal_buffer[y * 80 + x] = terminal_buffer[(y + 1) * 80 + x];

    }
  }

  terminal_row = 24;
  clear_line();
  //terminal_writestring("BasedOS:");


}



void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
  //call scroll here
  const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
	unsigned char uc = c;
	offset++;

  if (c != '\n'){ //if not a new line then print the character
    terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
  }    
  
  if (++terminal_column == VGA_WIDTH || c == '\n') {
    terminal_column = 0;
		
    if (++terminal_row == VGA_HEIGHT)
			terminal_scroll();

		if (c == '\n'){
			
			printf("BasedOS:");
			offset = 8;
		}
  }
	

  update_cursor(terminal_row, terminal_column);
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

void terminal_backspace() {
  if (offset != 8) {
       terminal_column--;
			 offset--;
  }

  terminal_putentryat(32, terminal_color, terminal_column, terminal_row);
  update_cursor(terminal_row, terminal_column);
}



