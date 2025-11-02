#include<reg51.h>
sbit led= P2^0;
void delay(unsigned int ms)
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
	{
		for(j=0;j<1275;j++);
	}
}
void main()
{
	while(1)
	{
		led=0;
		delay(500);
		led=1;
		delay(500);
	}
}