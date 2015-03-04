// This program will receive single character, 
// display it on the on-board 8 LEDs, and repeat forever.
// Set the baud rate to be 19200, 8-bit data, and 1 stop

#include <reg51.h>

void main(void)
{
  unsigned char mybyte;

  TMOD = 0x20;
  TH1=0xFD;
  SCON=0x50;
  TR1=1;
  while (1)
  {
    while (RI==0);
    mybyte=SBUF;
    P1=mybyte;
    RI=0;
  }
}
