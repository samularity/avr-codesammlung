/*
 * millis.c
 *
 * Created: 31.07.2013 01:12:53
 *  Author: Samuel
 */ 

#include "main.h"

// Timer 1 OCR1A compare values adjusted for CTC mode 1 sec = 62499 .5 sec = 31249 .25 sec = 15624 ?  0.1 sec 6249
#define Int_Timer_Ticks  250//250  // 62499 //6249
//
uint32_t uptime = 0;
uint16_t sec_counter=0;
uint32_t last_sek=0;

void timer_init() {

	//  Clear Global Interrupts  -  Should we really do this here?
	//cli();

	//  TCCR1A    Normal port operation, OCnA/OCnB/OCnC disconnected.
	//            WGM10 & WGM11 are clear for CTC mode see TCCR1B
	//  On reset cleared to 0 Not really necessary Better safe than sorry
	TCCR1A = 0;

	
	TCCR1B = (1 << WGM12) | (1 << CS11)| (1 << CS10);//  TCCR1B Prescaler = clk/8, CTC mode
	//TCCR1B = (1 << WGM12) | (1 << CS12); //prescaler und ctc mode = clk/256
	//TCCR1B = (1 << WGM12) | (1 << CS10); //prescaler und ctc mode = clk/1

	//  TCCR1C not forcing output compare
	//  On reset cleared to 0 Not really necessary Better safe than sorry
	TCCR1C = 0;

	// TCNT1 set timer counter initial value (16 bit value)
	//  On reset cleared to 0 Not really necessary Better safe than sorry
	TCNT1 = 0;

	// OCR1A Interrupts on OCR1A compare  (every 1 second)
	OCR1A = Int_Timer_Ticks;

	//   OCR1AH = (Int_Timer_Ticks >> 8);
	//   OCR1AL = (Int_Timer_Ticks & 0x00FF);

	// T1MSK1 Timer/Counter1 Output Compare A Match interrupt is enabled
	TIMSK1 = (1 << OCIE1A);
}

ISR( TIMER1_COMPA_vect) // 16 bit timer 1 compare 1A match
{
	uptime++;
	interrupt_1ms();
}

void interrupt_1s()
{
	//E6_toggle //debug only
	
	///////////////////////////  X //////////////////////////////////////////////
	// steps_x wird in main eingelesen per tastendruck einelesen
	if (steps_x>0)//positive laufrichtung
	{
		steps_x--; //i step weniger da er erledigt ist
		stepper_x_forward();
	}
	else if (steps_x<0) //negative laufrichtung erstmal ignoriern
	{
		steps_x++; //i step weniger da er erledigt ist (nähr an 0)
		stepper_x_backward();
	}
	//////////////////////////////////////////////////////////////////////////////

	///////////////////////////  Y  //////////////////////////////////////////////
	// steps_y wird in main eingelesen per tastendruck einelesen
	if (steps_y>0)//positive laufrichtung
	{
		steps_y--; //i step weniger da er erledigt ist
		stepper_y_forward();
	}
	else if (steps_y<0) //negative laufrichtung erstmal ignoriern
	{
		steps_y++; //i step weniger da er erledigt ist (nähr an 0)
		stepper_y_backward();
	}
	////////////////////////////////////////////////////////////////////////////

	
	///////////////////////////  Z //////////////////////////////////////////////
	// steps_z wird in main eingelesen per tastendruck einelesen
	if (steps_z>0)//positive laufrichtung
	{
		steps_z--; //i step weniger da er erledigt ist
		stepper_z_forward();
	}
	else if (steps_z<0) //negative laufrichtung erstmal ignoriern
	{
		steps_z++; //i step weniger da er erledigt ist (nähr an 0)
		stepper_z_backward();
	}
	////////////////////////////////////////////////////////////////////////////

}

void interrupt_1ms()
{
	sec_counter++;
	if (sec_counter>=readADC(0))
	{
		sec_counter=0;
		interrupt_1s();
	}
	
	
	/*
		if (uptime%200==0) //alle 200ms
		{
		usb_send_str("\r\n");
		usb_send_int (uptime/1000);
		usb_send_str(" sek:");
		usb_send_int(readADC(1));
		}
	*/
}

uint32_t millis()
{
	return uptime;
}
