/*
 * tool.c
 *
 * Created: 08.01.2014 17:01:49
 *  Author: Samuel
 */ 

#include "tool.h"

#define TIMER4_RESOLUTION 1023UL
#define PLL_FREQ 96000000UL

unsigned long pwmPeriod = 0;

/*
 //Timer init is done in usbserial.c already
//ISR( TIMER4_OVF_vect ) {} //overflow

void enable_intr(){
	TIMSK4 = _BV(TOIE4);
}

void disable_intr(){
	TIMSK4 = 0;
}
*/
void initialize(unsigned long freq) {
	
	/* Init the internal PLL */
//	PLLFRQ = _BV(PDIV1) |_BV(PDIV3) ; //set prescaler ist schon in usb.c gemacht
//	PLLCSR = _BV(PLLE); //enable prescaler ist in usb.c schon gemacht
//	while(!(PLLCSR & _BV(PLOCK))); //warten bis pll gestartet
//	PLLFRQ |= _BV(PLLTM1); /* PCK 96MHz */
	
	
	TCCR4A = (1<<PWM4A);
	TCCR4E = (1<<ENHC4);
	TCCR4D = (1<<WGM40); //set it to phase and frequency correct mode
	TCCR4C = 0;
	setPeriod(freq);
}

void setPwmDuty(unsigned int duty) {
	unsigned long dutyCycle = pwmPeriod;
	dutyCycle *= duty;
	dutyCycle >>= 9;
	TC4H = (dutyCycle) >> 8;
	OCR4A = (dutyCycle) & 255;
}

void start() {
	TCCR4A |= _BV(COM4A1);
}
void stop()  {
	TCCR4A &= ~(_BV(COM4A1));
}

void setPeriod(unsigned long freq)  {
	unsigned long cycles = PLL_FREQ / 2 / freq;
	unsigned char clockSelectBits = 0;
	
	if (cycles < TIMER4_RESOLUTION) {
		clockSelectBits = _BV(CS40);
		pwmPeriod = cycles;
	} else
	if (cycles < TIMER4_RESOLUTION * 2) {
		clockSelectBits = _BV(CS41);
		pwmPeriod = cycles / 2;
	} else
	if (cycles < TIMER4_RESOLUTION * 4) {
		clockSelectBits = _BV(CS41) | _BV(CS40);
		pwmPeriod = cycles / 4;
	} else
	if (cycles < TIMER4_RESOLUTION * 8) {
		clockSelectBits = _BV(CS42);
		pwmPeriod = cycles / 8;
	} else
	if (cycles < TIMER4_RESOLUTION * 16) {
		clockSelectBits = _BV(CS42) | _BV(CS40);
		pwmPeriod = cycles / 16;
	} else
	if (cycles < TIMER4_RESOLUTION * 32) {
		clockSelectBits = _BV(CS42) | _BV(CS41);
		pwmPeriod = cycles / 32;
	} else
	if (cycles < TIMER4_RESOLUTION * 64) {
		clockSelectBits = _BV(CS42) | _BV(CS41) | _BV(CS40);
		pwmPeriod = cycles / 64;
	} else
	if (cycles < TIMER4_RESOLUTION * 128) {
		clockSelectBits = _BV(CS43);
		pwmPeriod = cycles / 128;
	} else
	if (cycles < TIMER4_RESOLUTION * 256) {
		clockSelectBits = _BV(CS43) | _BV(CS40);
		pwmPeriod = cycles / 256;
	} else
	if (cycles < TIMER4_RESOLUTION * 512) {
		clockSelectBits = _BV(CS43) | _BV(CS41);
		pwmPeriod = cycles / 512;
	} else
	if (cycles < TIMER4_RESOLUTION * 1024) {
		clockSelectBits = _BV(CS43) | _BV(CS41) | _BV(CS40);
		pwmPeriod = cycles / 1024;
	} else
	if (cycles < TIMER4_RESOLUTION * 2048) {
		clockSelectBits = _BV(CS43) | _BV(CS42);
		pwmPeriod = cycles / 2048;
	} else
	if (cycles < TIMER4_RESOLUTION * 4096) {
		clockSelectBits = _BV(CS43) | _BV(CS42) | _BV(CS40);
		pwmPeriod = cycles / 4096;
	} else
	if (cycles < TIMER4_RESOLUTION * 8192) {
		clockSelectBits = _BV(CS43) | _BV(CS42) | _BV(CS41);
		pwmPeriod = cycles / 8192;
	} else
	if (cycles < TIMER4_RESOLUTION * 16384) {
		clockSelectBits = _BV(CS43) | _BV(CS42) | _BV(CS41) | _BV(CS40);
	pwmPeriod = cycles / 16384;     }
	/*else           clockSelectBits = _BV(CS43) | _BV(CS42) | _BV(CS41) | _BV(CS40);        pwmPeriod = TIMER4_RESOLUTION - 1; */
	TCCR4B = clockSelectBits;             TC4H = pwmPeriod >> 8;
	OCR4C = pwmPeriod;
	
}

void tool_init (void)
{
		initialize(10000);  // Frequency to generate in Hz
		setPwmDuty(512);     // Duty cycle 0-1024, 1024 is 100%, 512 is 50%
		start();
}

void set_tool_speed (uint16_t speed)// wird von den anderern genutzt von 0 bis 1024
{

	if (speed==0)
		{
		setPwmDuty(0);
		stop();
		}	
	else if (speed <= 1024)
		{	
		start();	
		setPwmDuty(speed);
		}
	else
		{
		start();	
		setPwmDuty(1024); //max speed
		}
}