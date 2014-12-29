//=================================adc.h===================================000
#ifndef _adc_h_
#define _adc_h_

#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t readADC( uint8_t adc_channel);
void adc_init ();

#define internal_vref ADMUX |= (1<<REFS0); 	ADMUX |= (1<<REFS1);	//vref intern 2,56V
#define external_vref ADMUX &= ~(1<<REFS0); 	ADMUX &= ~(1<<REFS1); //vref external

#define adc_ch0 ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2)| (1<<MUX3)| (1<<MUX4));			ADCSRB &= ~(1<<MUX5);		// 000000
#define adc_ch1 ADMUX &= ~((1<<MUX1) | (1<<MUX2) | (1<<MUX3)| (1<<MUX4)); ADMUX |= (1<<MUX0);	ADCSRB &= ~(1<<MUX5);		// 000001
#define adc_ch4 ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX3)| (1<<MUX4)); ADMUX |= (1<<MUX2);	ADCSRB &= ~(1<<MUX5);		// 000100
#define adc_ch5 ADMUX |=  ((1<<MUX0) | (1<<MUX2)) ;ADMUX&=~((1<<MUX1)|(1<<MUX3)| (1<<MUX4));	ADCSRB &= ~(1<<MUX5);		// 000101
#define adc_ch6 ADMUX |=  ((1<<MUX1) | (1<<MUX2)) ;ADMUX&=~((1<<MUX0)| (1<<MUX3)| (1<<MUX4));	ADCSRB &= ~(1<<MUX5);		// 000110
#define adc_ch7 ADMUX |=  ((1<<MUX0) | (1<<MUX1)|(1<<MUX2)); ADMUX&=~((1<<MUX3)| (1<<MUX4));	ADCSRB &= ~(1<<MUX5);		// 000111
#define adc_ch8 ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2)| (1<<MUX3)| (1<<MUX4));			ADCSRB |=(1<<MUX5);		    // 100000
#define adc_ch9 ADMUX &= ~((1<<MUX1) | (1<<MUX2) | (1<<MUX3)| (1<<MUX4)); ADMUX |= (1<<MUX0);	ADCSRB |=(1<<MUX5);		    // 100001
#define adc_ch10 ADMUX &= ~((1<<MUX0) | (1<<MUX2) | (1<<MUX3)| (1<<MUX4)); ADMUX |= (1<<MUX1);	ADCSRB |=(1<<MUX5);		    // 100010
#define adc_ch11 ADMUX &= ~((1<<MUX2) | (1<<MUX3) | (1<<MUX4)); ADMUX |= ((1<<MUX1)|(1<<MUX0));	ADCSRB |=(1<<MUX5);		    // 100011
#define adc_ch12 ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX3)| (1<<MUX4)); ADMUX |= (1<<MUX2);	ADCSRB |=(1<<MUX5);		    // 100100
#define adc_ch13 ADMUX &= ~((1<<MUX1) | (1<<MUX3) | (1<<MUX4)); ADMUX |= ((1<<MUX2)|(1<<MUX0));	ADCSRB |=(1<<MUX5);		    // 100100
#define adc_temp ADMUX &=~((1<<MUX3)  | (1<<MUX4)); ADMUX|=((1<<MUX0)|(1<<MUX1)|(1<<MUX2));		ADCSRB |= (1<<MUX5);		//adc temp = 20
#endif
