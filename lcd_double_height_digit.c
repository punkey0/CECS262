// This program interface 8051 with a 16x2 line LCD.
// The purpose of this program is to practice user-defined symbols. 
// It displays 10 double height digits in order. We use the index 
// in CGRAM as the value of the user-defined symbols when writing 
// them to the DDRAM.
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
void Define_Doubles();
void Put_Upper(unsigned char num); 
void Put_Lower(unsigned char num);
void Put_Double(unsigned char num, unsigned char col);

void main(void)
{
  unsigned char i=0;
  
  init_lcd();

  Define_Doubles(); // definition at startup

  // Clear display and returns cursor to the home position(address 0) 
  write_to_lcd(0x01,COMMAND);

//  Put_Double(0,0);

  for (i = 0; i <= 9; i++)
    Put_Double(i,i);
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
// Here is the steps:
// 1. set the starting address for CGRAM
// 2. write the bitmap of the symbol to CGRAM row by row, 
//    the address of the CGRAM will be incremented automatically 
//    after each write.
void Define_Doubles(void) 
{ 
  // save current address in DDRAM
  // Set CGRAM address to zero'th character
  // (automatically incremented after write)
  write_to_lcd(Set_CGRAM_Address+0,COMMAND);     

                                 //        BitPattern   DataByte     
    // Character 0  //                 ==========   ========

    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001

    // Character 1

    write_to_lcd(0x1F,LCD_DATA); //   x x x * * * * *   00011111
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001

    // Character 2

    write_to_lcd(0x1F,LCD_DATA); //   x x x * * * * *   00011111
    write_to_lcd(0x10,LCD_DATA); //   x x x * . . . .   00010000
    write_to_lcd(0x10,LCD_DATA); //   x x x * . . . .   00010000
    write_to_lcd(0x10,LCD_DATA); //   x x x * . . . .   00010000
    write_to_lcd(0x10,LCD_DATA); //   x x x * . . . .   00010000
    write_to_lcd(0x10,LCD_DATA); //   x x x * . . . .   00010000
    write_to_lcd(0x10,LCD_DATA); //   x x x * . . . .   00010000
    write_to_lcd(0x1F,LCD_DATA); //   x x x * * * * *   00011111

    // Character 3

    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x1F,LCD_DATA); //   x x x * * * * *   00011111

    // Character 4

    write_to_lcd(0x1F,LCD_DATA); //   x x x * * * * *   00011111
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x1F,LCD_DATA); //   x x x * * * * *   00011111

    // Character 5

    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x11,LCD_DATA); //   x x x * . . . *   00010001
    write_to_lcd(0x1F,LCD_DATA); //   x x x * * * * *   00011111

    // Character 6

    write_to_lcd(0x1F,LCD_DATA); //   x x x * * * * *   00011111
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x1F,LCD_DATA); //   x x x * * * * *   00011111

    // Character 7

    write_to_lcd(0x1F,LCD_DATA); //   x x x * * * * *   00011111
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001
    write_to_lcd(0x01,LCD_DATA); //   x x x . . . . *   00000001

    // Sure I could have used loops to cut down the code,
    // but would it have been as clear?

    // restore current address in DDRAM
}

// Display upper Half of Double-Height Digit Character
void Put_Upper(unsigned char num) 
{ 
    switch (num) {
        case  0: write_to_lcd(1,LCD_DATA);
            break;
        case  1: write_to_lcd(0,LCD_DATA);
            break;
        case  2: write_to_lcd(7,LCD_DATA);
            break;
        case  3: write_to_lcd(6,LCD_DATA);
            break;
        case  4: write_to_lcd(5,LCD_DATA);
            break;
        case  5: write_to_lcd(2,LCD_DATA);
            break;
        case  6: write_to_lcd(2,LCD_DATA);
            break;
        case  7: write_to_lcd(7,LCD_DATA);
            break;
        case  8: write_to_lcd(4,LCD_DATA);
            break;
        case  9: write_to_lcd(4,LCD_DATA);
            break;
        default: break; // something goes wrong!
    }
}
// Lower Half of Double-Height Digit Character
void Put_Lower(unsigned char num) 
{ 
    switch (num) {
        case  0: write_to_lcd(5,LCD_DATA);
            break;
        case  1: write_to_lcd(0,LCD_DATA);
            break;
        case  2: write_to_lcd(2,LCD_DATA);
            break;
        case  3: write_to_lcd(3,LCD_DATA);
            break;
        case  4: write_to_lcd(0,LCD_DATA);
            break;
        case  5: write_to_lcd(3,LCD_DATA);
            break;
        case  6: write_to_lcd(5,LCD_DATA);
            break;
        case  7: write_to_lcd(0,LCD_DATA);
            break;
        case  8: write_to_lcd(5,LCD_DATA);
            break;
        case  9: write_to_lcd(3,LCD_DATA);
            break;
        default: break; // something goes wrong!
    }
}

// 16 character x 2 line display
void Put_Double(unsigned char num, unsigned char col) 
{ 
  // set DDRAM address to upper line of column
  write_to_lcd(Set_DDRAM_Address + col,COMMAND); 
  Put_Upper(num);

  // set DDRAM address to lower line of column
  write_to_lcd(Set_DDRAM_Address + col + Line2_Offset,COMMAND);
  Put_Lower(num);
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
