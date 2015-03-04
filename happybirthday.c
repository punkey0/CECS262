// This program used timer and buzzer to play a "Happy Birthday" song
// The program use 80ms as 1/16 step and 1/16 as the minimum length unit
// in the music_type struct, 1+0, 1+7, 1+14 represent 
// Low C 1, Middle C 1, and High C 1, respectively; and
// 0x01, 0x02, 0x04 represent 1/16, 1/8, 1/4, respectively.
// A 2 second stop period is inserted after each tone to simulate real music effect.
#include <reg51.h>
#include <intrins.h> // for _nop_()

#define uchar unsigned char
#define uint unsigned int

sbit Buzzer=P3^7;
volatile uchar th0, tl0; // hold current tone information

struct music_type {
  uchar tone;
  uchar delay;
};

uchar tl0, th0; // used to hold the current timer initial value.

// Initial value table for C Scale 3 groups, each has 7 tones 
uint code tonetab_C[] = {62018,62401,62743,62903,63185,63441,63670,
                        63777,63969,64140,64216,64360,64489,64603,
					    64655,64751,64837,64876,64948,65012,65070};

struct music_type code notetab[] = {  // note table for Happy Birthday
5+7,0x02,5+7,0x02,6+7,0x04,5+7,0x04,1+14,0x04,7+7,0x04,
0,0x04,5+7,0x02,5+7,0x02,6+7,0x04,5+7,0x04,2+14,0x04,
1+14,0x08,5+7,0x02,5+7,0x02,5+14,0x04,3+14,0x04,
1+14,0x04,7+7,0x04,6+7,0x0C,0,0x04,4+14,0x02,4+14,0x02,
3+14,0x04,1+14,0x04,2+14,0x04,1+14,0x08, 1+14, 0x0
};

void delay_us(uchar n_usec);
void delay_ms(uchar n_msec);	 

void main (void)
{
   uchar i, j;
     
   TMOD = 0x01; // use timer0 mode 1 to generate tone.
   IE = 0x82; // enable timer0 overflow interrupt

   while (1) 
   {
     i=0;
	 while (notetab[i].delay) 
	 {
	   if (!notetab[i].tone) 
	     TR0 = 0; // stop tone, turn off timer0
	   else 
	   {
	     th0=TH0=tonetab_C[notetab[i].tone-1]>>8; // get higher 8-bit of the initial value
		 tl0=TL0=tonetab_C[notetab[i].tone-1]&0xFF; // get lower 8-bit of the initial value
		 TR0=1;
	   }

	   // provide duratio for each tone
	   for (j=0;j<notetab[i].delay;j++)
	     delay_ms(80); // minimum delay unit for 1/16

	   i++;
	 }
	 TR0=0;  // stop between songs for about 0.2s
	 delay_ms(200);
   }
}

void delay_us(uchar n_usec)
{
  do 
  {
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
  } while (--n_usec);
}
void delay_ms(uchar n_msec)	 
{
  do
    delay_us(131);
  while (--n_msec); 
}

void T0_ISR(void) interrupt 1  // timer0 interrupt service routine
{
  TR0=0;
  Buzzer = !Buzzer;
  TH0=th0;
  TL0=tl0;
  TR0=1;
}
