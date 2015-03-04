// This program interface 8051 with a 16x2 line LCD. 
// This program will display a message from the right 
// end of the first display line, then display scrolls 
// to the left until the whole message is displayed 
// and repeat the display again.
#include <reg51.h>

#define ldata P2
#define COMMAND 0
#define LCD_DATA 1

sbit rs = P3^6;
sbit rw = P3^5;
sbit en = P3^7;
sbit busy = P2^7;

void init_lcd();
void write_to_lcd(unsigned char value, bit mode);
void MSDelay(unsigned int itime);
void lcdready(void);

void main(void)
{
  unsigned char code msg[]="Hi, Kasey! You are great!";
  unsigned char i;

  init_lcd();

  while (1) {
    // position cursor to the right end of line 1, address 0F                                                                     // set cursor position command is 80H, address is 0FH
    // 80H+0FH=8F               
    write_to_lcd(0x8F,COMMAND); 
    i=0;
    while (msg[i]!='\0') 
      write_to_lcd(msg[i++],LCD_DATA);

    write_to_lcd(0x01,COMMAND); // Clear LCD 	   
  }
}

// setup LCD for the required display pattern
void init_lcd()
{
  // Function set format: 001 DL N F  * *
  // Function set value: 00111000
  // DL=1, use 8-bit data bus, N=0,1/16 duty(1 lines),
  // F=0,5x7 dot character font, we can make the font 
  // larger when displaying only one line.
  write_to_lcd(0x30,COMMAND); 
                              
  // Display On/Off Control format: 00001 D C B
  // Display On/Off Control value: 00001100
  // D=1, display o; C=0, cursor off; B=0, cursor blink off
  write_to_lcd(0x0C,COMMAND);

  // Entry mode set format: 000001 I/D S
  // Entry mode set value: 00000111
  // I/D=1, Increment cursor position; S=1, display shift
  write_to_lcd(0x07,COMMAND);   

  // Cursor/display shift format: 0001 S/C R/L * *
  // Entry mode set value: 00011000
  // S/C=1, shift display; R/L=0, shift left
  write_to_lcd(0x18,COMMAND);

  // Clear display and returns cursor to the home position(address 0) 
  write_to_lcd(0x01,COMMAND);
}

// write a command or a character to the LCD
void write_to_lcd(unsigned char value, bit mode)
{
  lcdready();
  ldata = value; 
  rs = mode; // set for data, reset for command
  rw = 0;
  en = 1;
  MSDelay(1);
  en = 0;

  // the following code is removed due to some students observation
  // of their LCD malfunction
//  if (mode == LCD_DATA) 
//    MSDelay(100);
}

void MSDelay(unsigned int itime)
{
   unsigned int i, j;
   for (i=0;i<itime;i++)
     for (j=0;j<1275;j++);
}


// wait for the LCD to become ready
void lcdready(void)
{
  busy = 1;
  en = 1;
  rs = 0; // It's a command
  rw = 1; // It's a read command
  while (busy) {
    en = 0;
    MSDelay(1);
    en = 1;
  }
  en=0;
  rw=0;
}

// 0x08: clear the message, 0x06, 0xA0, 0x0C, 0x0A, 0x8F
// 0x38: two lines display
// 0x8F: set DD RAM address to 0001111=0F
// 0x80: blinking text
// 0x93,data,0x18: scrolling message to the left
