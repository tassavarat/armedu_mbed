#include "mbed.h"

#define BUTTON_1 p5
#define BUTTON_2 p6 
#define BUTTON_3 p7 
#define BUTTON_4 p8 

#define RED_LED p9
#define YELLOW_LED p10
#define BLUE_LED p11

//Define output
DigitalOut led1(RED_LED);
DigitalOut led2(YELLOW_LED);
DigitalOut led3(BLUE_LED);

//Define Interrupt Inputs
InterruptIn button_1(BUTTON_1);
InterruptIn button_2(BUTTON_2);
InterruptIn button_3(BUTTON_3);
InterruptIn button_4(BUTTON_4);

//Define ISRs for interrupts
void button_1_handler() {
	led1 = !led1;
}

void button_2_handler() {
	led2 = !led2;
}

void button_3_handler() {
	led3 = !led3;
}

void button_4_handler() {
	led1 = 1;
	led2 = 1;
	led3 = 1;
}

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/

int main() {

	//Initially turn off all LEDs
	led1 = 0;
	led2 = 0;
	led3 = 0;

	//Interrupt handlers
	button_1.rise(&button_1_handler);
	button_2.rise(&button_2_handler);
	button_3.rise(&button_3_handler);
	button_4.rise(&button_4_handler);

	//wait 100 ms
	while (1)
		wait_ms(100);
}
