#include<reg51.h>

sbit output=P2^7;
sbit motp=P2^0;
sbit motn=P2^1;

void msdelay(unsigned int time)  // Function for creating delay in milliseconds.

{

    unsigned i,j ;

    for(i=0;i<time;i++)    

    for(j=0;j<1275;j++);

}


void servo_delay(int times)     // Creating Delay in multilple of 50us using 8051 Timers

{

    int m;

    for(m=0;m<times;m++)

    {

        TH0=0xFF;

        TL0=0xD2;

        TR0=1;

        while(TF0==0);

        TF0=0;

        TR0=0;

    }

}

void main()

{
unsigned int i;
    int n;

    TMOD=0x01;                // Selecting Timer 0, Mode 1

    output=0;
	motp=motn=0;

    while(1)

    {

        for(n=13;n<28;n=n+2)

        {

            output=1;

            servo_delay(n);     

            output=0;

            servo_delay(260);

            msdelay(200);
					
					motp=1;
motn=0;
for (i=0; i<60000; i++);
motp=0;
motn=1;
for (i=0; i<60000; i++);
						
						
        }

    }

}