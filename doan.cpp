#include <reg51.h>
#include <math.h>

sbit IN3 = P2^2;
sbit IN4 = P2^3;
sbit BUTTON_RIGHT_PIN = P3^2;
sbit BUTTON_LEFT_PIN = P3^7;
sbit SENSOR_PIN = P2^4;
sbit SERVO_PIN = P2^7;
#define F_CPU = 12000000L
unsigned int steering_angle;
void msdelay(unsigned int time)  // Function for creating delay in milliseconds.

{

    unsigned i,j ;

    for(i=0;i<time;i++)    

    for(j=0;j<1275;j++);

}


void servo_delay(unsigned int times)     // Creating Delay in multilple of 50us using 8051 Timers

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

void set_servo_angle(unsigned int angle) {
    unsigned int pulse_width = (angle * 10) + 1000; // 1ms = 0 degrees, 2ms = 180 degrees (adjust if needed)
    unsigned int reload_value = (65536 - pulse_width * (12000000 / 12000000)); // Calculate timer reload value 
	SERVO_PIN = 0;
   servo_delay(reload_value);
	SERVO_PIN = 1;
}


void delay_ms(unsigned int ms);

//Handle go forward
void go_forward()
{
     IN3 = 1;
     IN4 = 0;
     
}

//Handle go backward
void go_backward()
{	
     IN3 = 0;
     IN4 = 1;
     msdelay(500);
     IN3 = 1;
     IN4 = 0;
}

//Handle turn left
void turn_left(int angle)
{

    steering_angle -= angle;
     if (steering_angle <-90) {	
	 steering_angle = -90;
     }
    set_servo_angle(steering_angle);
}

//Handle turn right
void turn_right(int angle)
{
     steering_angle += angle;
     if (steering_angle > 90) {
	 steering_angle = 90;
     }
     set_servo_angle(steering_angle);
}

//Handle button signal 
void button_steering() {
    if (BUTTON_LEFT_PIN == 0 ) {
	    turn_left(30);
	 }
	 if (BUTTON_RIGHT_PIN == 0) {
	    turn_right(30);
	 } 
}

//Init port
void init() {
    P1 = 0xFF; // Initialize Port 1 
    P2 = 0x00; // Initialize Port 2
    P3 = 0xFF; // Initialize Port 3 

}

void main() {
  // init();
//   P2.F0 = 0;

    //P1
	TMOD=0x01;                // Selecting Timer 0, Mode 1

   // output=0;
   SENSOR_PIN =0;
   while (1) {
   
    go_forward();
		 msdelay(500);
		 go_backward();
     if (SENSOR_PIN == 1) {
	 go_backward();
				msdelay(500);
	 turn_right(30);
				msdelay(500);
	 go_forward();
      } else {
	 button_steering();
	 go_forward();
				msdelay(500);
      }
   }
	
}

