// This program is called "My Little Chasing Cat". 
// 1. Type in the program, compile and simulate it.
// 2. Observe what happens on port P0 
// 3. Answer the following question: Why do we name it 
//    "My Little Chasing Cat".
#include <reg51.h>
#define LED P1

void wait_n_msecond(unsigned char n);

void main()
{
  unsigned char delay_len = 20;

  LED=1;
  while (1) {
	wait_n_msecond(delay_len);
	LED <<= 1;
	if (LED==0) LED=1;
  }
}

void wait_n_msecond(unsigned char n)
{
  unsigned int j;
  unsigned char i;

  for (i=0;i<n;i++)
    for (j=0;j<30000;j++);
}
