/*
 * millis.h
 *
 * Created: 17.12.2013 19:24:02
 *  Author: Samuel
 */ 


#ifndef MILLIS_H_
#define MILLIS_H_
#include <avr/interrupt.h>
uint32_t millis();
void timer_init();
void interrupt_1ms();
void interrupt_1s();

#endif /* MILLIS_H_ */