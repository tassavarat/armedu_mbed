#include "mbed.h"

DigitalIn start_btn(p5);
DigitalIn stop_btn(p6);
DigitalIn guard(p7);
DigitalIn temp(p8);

DigitalOut ready(p9);
DigitalOut running(p10);
DigitalOut guard_fault(p11);
DigitalOut temp_fault(p12);

int main()
{
	while(1) {
		while ((guard == 0) || (temp == 1)) {
			running = guard_fault = temp_fault = 0;
			ready = !ready;
			wait(.2); 
		}
		ready = 1;
		while (start_btn == 0)
			wait(.01);
		while ((guard == 1) && (temp == 0) && (stop_btn == 0)) {
			ready = 0;
			running = 1;
			wait(.2);
		}
		if (guard == 0) {
			running = 0;
			guard_fault = 1;
			wait(.5);
			guard_fault = 0;
		}
		if (temp == 1) {
			running = 0;
			temp_fault = 1;
			wait(.5);
			temp_fault = 0;
		}
		if (stop_btn == 1)
			running = 0;
	}
}
