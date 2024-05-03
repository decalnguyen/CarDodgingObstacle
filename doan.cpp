#include <reg51.h>
#include <math.h>

sbit SENSOR_PIN = P2^4;
sbit IN3 = P2^2;
sbit IN4 = P2^3;
sbit BUTTON_RIGHT_PIN = P3^2;
sbit BUTTON_LEFT_PIN = P3^7;


//Handle get distance 
unsigned int get_distance()
{

    unsigned int adc_value;
    float voltage;
    float distance; 

    // ADC Initialization (Replace with AT89C51-specific code)
    ADC_CONTR = 0x80;   // Enable ADC (example)
    ADC_CONTR |= 0x04;  // Select ADC Channel 0 (example)

    // Start Conversion (Replace with AT89C51-specific code)
    ADC_CONTR |= 0x10;  // Start conversion (example)

    // Wait for Complete (Replace with AT89C51-specific code)
    while (!(ADC_CONTR & 0x20)); // Wait for conversion flag (example)

    // Read ADC Value (Replace with AT89C51-specific code)
    adc_value = ADC;    // Read ADC data register (example)

    // Calculate Voltage 
    voltage = (adc_value * 5.0) / 1023.0;  // Assuming 5V reference, 10-bit ADC

    // Calculate Distance (From Your GP2D12 Datasheet Formula)
    distance = (2914 / (voltage + 5)) - 1; // Example formula - Adjust as needed 
   
}


void delay_ms(unsigned int ms);

//Handle go forward
void go_forward(int centimeters)
{
     IN3 = 1;
     IN4 = 0;
     
}

//Handle go backward
void go_backward(int centimeters)
{
     IN3 = 0;
     IN4 = 1;
}

//Handle turn left
void turn_left(int angle)
{
     steering_angle -= angle;
     if (steering_angle <-90) {	
	 steering_angle = -90;
     }
}

//Handle turn right
void turn_right(int angle)
{
     steering_angle += 30;
     if (steering_angle > 90) {
	 steeing_angle = 90;
     }
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
   init();
   unsigned int distance;
   int steering_angle = 0 ;
   //P1
   
   while (true) {
   
      distance = get_distance();   
      
      // Handle sensor value 
      if (distance < 25) {
	 go_backward((20);
	 turn_right(30);
	 go_forward(20);
      } else {
	 button_steering();
	 go_forward(20);
      }
   }
}

