#include <reg51.h>
#include <intrins.h> // for _nop_()

#define TONE_DURATION 2 // each tone uses the same duration 

sbit Buzzer=P3^7;
volatile unsigned char th0, tl0; // hold current tone information

unsigned int code tonetab[] = {64580,64684,64777,64820,64898,64968,65030,65058};

void delay_us(unsigned char n_usec);
void delay_ms(unsigned char n_msec);	 

void main (void)
{
   unsigned char i, j;

   TMOD = 0x01; // use timer0 mode 1 to generate tone.
   IE = 0x82; // enable timer0 overflow interrupt
   while (1) 
   {
     i=0;
     for (i=0;i<8;i++) {
	   j=0;
	   th0=TH0=tonetab[i]/256;	// load the inital value for the new tone
	   tl0=TL0=tonetab[i]%256;
	   TR0 =1; // start timer 0
	   while (j++<TONE_DURATION) // sing the tone for specified duration
	     delay_ms(180);
	 }
	 
	 for (i=7;i!=255;i--) {
	   j=0;
	   th0=TH0=tonetab[i]/256;	// load the inital value for the new tone
	   tl0=TL0=tonetab[i]%256;
	   TR0=1; // start timer 0
	   while (j++<TONE_DURATION) // sing the tone for specified duration
	     delay_ms(180);
	   TR0=0;
	 }
   }
}

void delay_us(unsigned char n_usec)
{
  do {
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
  } while (--n_usec);
}
void delay_ms(unsigned char n_msec)	 
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
