// This program interface 8051 with a 16x2 line LCD.
// The purpose of this program is to test the basic operations
// for creating and writing a user_defined symbol to the LCD.
// This program will define two symbols and displays them
// on the first two position of the first line.
#include <reg51.h>

#define ldata P2
#define COMMAND 0
#define LCD_DATA 1
#define Set_CGRAM_Address  0x40 // 0  1  A  A  A  A  A  A
#define Set_DDRAM_Address  0x80 // 1  A  A  A  A  A  A  A
#define Line2_Offset  0x40

sbit rs = P3^6;
sbit rw = P3^5;
sbit en = P3^7;
sbit busy = P2^7;

void init_lcd();
void write_to_lcd(unsigned char value, bit mode);
void MSDelay(unsigned int itime);
void lcdready(void);
void Define_Symbols();

void main(void)
{
  init_lcd();

  Define_Symbols(); // definition at startup

  // Clear display and returns cursor to the home position(address 0) 
  write_to_lcd(0x01,COMMAND);

  write_to_lcd(0, LCD_DATA);
  write_to_lcd(1, LCD_DATA);

  while (1);
}

// setup LCD for the required display 
void init_lcd()
{
  // Function set format: 001 DL N F  * *
  // Function set value: 00111000
  // DL=1, use 8-bit data bus; N=1,1/16 duty(2 lines),
  // F=0, 5x7 dot character font 
  write_to_lcd(0x38,COMMAND); 
                              
  // Display On/Off Control format: 00001 D C B
  // Display On/Off Control value: 00001110
  // D=1, display on; C=1, cursor on; B=0, cursor blink off
  write_to_lcd(0x0E,COMMAND);

  // Entry mode set format: 000001 I/D S
  // Entry mode set value: 00000110
  // I/D=1, Increment cursor position; S=0, no display shift
  write_to_lcd(0x06,COMMAND);

  // Clear display and returns cursor to the home position(address 0) 
  write_to_lcd(0x01,COMMAND);
}

// uses all 8 user-defined characters in CGRAM
void Define_Symbols(void) 
{ 
  // Set CGRAM address to zero'th character
  write_to_lcd(Set_CGRAM_Address+0,COMMAND);     

                                  //        BitPattern   DataByte     
  // Symbol 0: :<
  write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
  write_to_lcd(0x12,LCD_DATA); //   x x x * . . * .   00010010
  write_to_lcd(0x04,LCD_DATA); //   x x x . . * . .   00000100
  write_to_lcd(0x08,LCD_DATA); //   x x x . * . . .   00001000
  write_to_lcd(0x04,LCD_DATA); //   x x x . * . . .   00001000
  write_to_lcd(0x12,LCD_DATA); //   x x x . . * . .   00000100
  write_to_lcd(0x11,LCD_DATA); //   x x x * . . * .   00010010
  write_to_lcd(0x00,LCD_DATA); //   x x x * . . . *   00010001
  
  // Symbol 1: 
  write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
  write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
  write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
  write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
  write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
  write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
  write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
  write_to_lcd(0x1F,LCD_DATA); //   x x x * * * * *   00011111
}



void write_to_lcd(unsigned char value, bit mode)
{
  lcdready();
  ldata = value; 
  rs = mode; // set for data, reset for command
  rw = 0;
  en = 1;
  MSDelay(1);
  en = 0;
  if (mode == LCD_DATA) 
    MSDelay(100);
}

void MSDelay(unsigned int itime)
{
   unsigned int i, j;
   for (i=0;i<itime;i++)
     for (j=0;j<1275;j++);
}

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
