#include "mbed.h"

#define CUT_TIME	12
#define CAPACITY	8

InterruptIn adult_btn(p5);
InterruptIn childpar_btn(p6);
InterruptIn fire_al_btn(p7);

DigitalOut at_capacity(p8);
DigitalOut barb1_led(p9);
DigitalOut barb2_led(p10);
DigitalOut barb3_led(p11);
DigitalOut clock_led(p12);
BusOut seat_leds(p13, p14, p15, p16, p17, p18, p19, p20);

unsigned int b1_prog, b2_prog, b3_prog;
unsigned int seat_pat, adults, childpars;

void fire_al_isr()
{
	at_capacity = 1;
	barb1_led = barb2_led = barb3_led = 0;

	while (seat_pat != 0) {
		seat_pat >>= 1;
		seat_leds = seat_pat;
		wait(.5);
	}
	adults = childpars = 0;
	at_capacity = 0;
}

void childpar_isr()
{
	if (adults + childpars < CAPACITY - 1) {
		childpars += 2;
		seat_pat <<= 2;
		seat_pat |= 3;
	} else {
		at_capacity = 1;
		wait(1);
		at_capacity = 0;
	}
}

void adult_isr()
{
	if (adults + childpars < CAPACITY) {
		++adults;
		seat_pat <<= 1;
		seat_pat |= 1;
	} else {
		at_capacity = 1;
		wait(1);
		at_capacity = 0;
	}
}

int main()
{

	adult_btn.rise(&adult_isr);
	childpar_btn.rise(&childpar_isr);
	fire_al_btn.rise(&fire_al_isr);

	while (1) {
		if (barb1_led == 1) {
			++b1_prog;
			if (b1_prog == CUT_TIME)
				barb1_led = 0;
		} else if (adults > 0) {
			barb1_led = 1;
			--adults;
			seat_pat >>= 1;
			b1_prog = 0;
		}
		if (barb2_led == 1) {
			++b2_prog;
			if (b2_prog == CUT_TIME)
				barb2_led = 0;
		} else if (adults > 0) {
			barb2_led = 1;
			--adults;
			seat_pat >>= 1;
			b2_prog = 0;
		}
		if (barb3_led == 1) {
			++b3_prog;
			if (b3_prog == CUT_TIME) {
				barb3_led = 0;
				--childpars;
				seat_pat >>= 1;
			} 
		} else if (childpars > 0) {
			barb3_led = 1;
			--childpars;
			seat_pat >>= 1;
			b3_prog = 0;
		}
		seat_leds = seat_pat;
		clock_led = !clock_led;
		wait(1);
	}
}
