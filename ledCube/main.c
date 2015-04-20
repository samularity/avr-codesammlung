#include <avr/io.h>
#define F_CPU 8000000UL  // 8 MHz
#include <util/delay.h>
#include <avr/interrupt.h>

#define DDR_REG(port) DDR ## port
#define PORT_REG(port) PORT ## port
#define PIN_REG(port) PIN ## port

#define SET_BIT(port, bit) do { (port) |= (1 << (bit)); } while(0)
#define CLR_BIT(port, bit) do { (port) &= ~(1 << (bit)); } while(0)
#define BIT_IS_SET(port, bit) ((((uint8_t)(port)) >> ((uint8_t)(bit))) & 0x1)

#define IO_SET_INPUT_AUX(port, bit) CLR_BIT(DDR_REG(port), bit)
#define SET_INPUT(io) IO_SET_INPUT_AUX(io)

#define IO_SET_OUTPUT_AUX(port, bit) SET_BIT(DDR_REG(port), bit)
#define SET_OUTPUT(io) IO_SET_OUTPUT_AUX(io)

#define IO_OUTPUT_0_AUX(port, bit) CLR_BIT(PORT_REG(port), bit)
#define SET_LOW(io) IO_OUTPUT_0_AUX(io)

#define IO_OUTPUT_1_AUX(port, bit) SET_BIT(PORT_REG(port), bit)
#define SET_HIGH(io) IO_OUTPUT_1_AUX(io)

#define IO_GET_INPUT_AUX(port, bit) BIT_IS_SET(PIN_REG(port), bit)
#define GET_INPUT(io) IO_GET_INPUT_AUX(io)


#define TOP		D,3
#define MIDDLE	D,4
#define LOW  	D,5

#define LED1	B,1
#define LED2  	B,0
#define LED3	D,6
#define LED4	B,4
#define LED5	B,3
#define LED6	B,2
#define LED7	B,7
#define LED8	B,6
#define LED9	B,5


void init_io(void);
void init_isr(void);
void set_led (uint8_t ebene);
void write_cube(uint8_t ebene);

void sleep_ms(uint16_t ms);
void sleep_us(uint16_t us);


//array mit helligkeit für jede led
volatile uint8_t led_values[27];


int main(void){
	
init_io();
init_isr();
sei();// Global Interrupts aktivieren
uint8_t i =0;

while(1){
	for(i=0;i<27;i++)
	{
		led_values[i]++;
	}
	sleep_ms(3);
	}
return 0;
}


//interrupt routine
volatile uint8_t counter=0;
ISR (TIMER0_COMPA_vect)
{
  	write_cube(counter);
  	counter++;
  	if (counter>2){counter=0;}
}


/* sleep schlaufe */
void sleep_ms(uint16_t ms){
while(ms){
	ms--;
	_delay_ms(1);
}
}

/* sleep schlaufe */
void sleep_us(uint16_t us){
while(us){
	us--;
	_delay_us(1);
}
}


void write_cube(uint8_t ebene)
{
	switch (ebene)
	{
		case 0:
			SET_LOW(TOP);SET_LOW(MIDDLE);SET_HIGH(LOW);
			break;
		case 1: 
			SET_LOW(TOP);SET_HIGH(MIDDLE);SET_LOW(LOW); 
			break;
		case 2: 
			SET_HIGH(TOP);SET_LOW(MIDDLE);SET_LOW(LOW);
			break;
		default:return;
	}
	set_led(ebene);
	//sleep_us(4);
	SET_LOW(TOP);SET_LOW(MIDDLE);SET_LOW(LOW);
}
void set_led (uint8_t ebene)
{
	uint8_t offset = ebene*9;
	uint8_t i =0;
	for (i =0; i<255;i++)
	{
		if (led_values[0+offset]>i)
			{SET_HIGH(LED1);}
		else{SET_LOW(LED1);}

		if (led_values[1+offset]>i)
			{SET_HIGH(LED2);}
		else{SET_LOW(LED2);}
		
		if (led_values[2+offset]>i)
			{SET_HIGH(LED3);}
		else{SET_LOW(LED3);}

		if (led_values[3+offset]>i)
			{SET_HIGH(LED4);}
		else{SET_LOW(LED4);}

		if (led_values[4+offset]>i)
			{SET_HIGH(LED5);}
		else{SET_LOW(LED5);}

		if (led_values[5+offset]>i)
			{SET_HIGH(LED6);}
		else{SET_LOW(LED6);}
		
		if (led_values[6+offset]>i)
			{SET_HIGH(LED7);}
		else{SET_LOW(LED7);}
		
		if (led_values[7+offset]>i)
			{SET_HIGH(LED8);}
		else{SET_LOW(LED8);}
		
		if (led_values[8+offset]>i)
			{SET_HIGH(LED9);}
		else{SET_LOW(LED9);}
		
		__asm("nop");__asm("nop");__asm("nop");
		__asm("nop");__asm("nop");__asm("nop");
	}
}


void init_isr(void)
{
  // Timer 0 konfigurieren
  TCCR0A = (1<<WGM01); // CTC Modus
 // TCCR0B |= (1<<CS01) | (1<<CS00); //presc. 64
  TCCR0B |= (1<<CS02); // Prescaler 256
  // TCCR0B |= (1<<CS02) | (1<<CS00); // Prescaler 1025
  // ((1000000/8)/1000) = 125
  // OCR0A = 125-1;
  OCR0A = 128;
 
  // Compare Interrupt erlauben
  TIMSK |= (1<<OCIE0A);
}
void init_io(void)
{
SET_OUTPUT(TOP);
SET_OUTPUT(MIDDLE);
SET_OUTPUT(LOW);

SET_LOW(TOP);
SET_LOW(MIDDLE);
SET_LOW(LOW);


SET_OUTPUT(LED1);
SET_OUTPUT(LED2);
SET_OUTPUT(LED3);
SET_OUTPUT(LED4);
SET_OUTPUT(LED5);
SET_OUTPUT(LED6);	
SET_OUTPUT(LED7);
SET_OUTPUT(LED8);
SET_OUTPUT(LED9);

SET_LOW(LED1);
SET_LOW(LED2);
SET_LOW(LED3);
SET_LOW(LED4);
SET_LOW(LED5);
SET_LOW(LED6);	
SET_LOW(LED7);
SET_LOW(LED8);
SET_LOW(LED9);


led_values[0]=0;
led_values[1]=0;
led_values[2]=0;
led_values[3]=0;
led_values[4]=0;
led_values[5]=0;
led_values[6]=0;
led_values[7]=0;
led_values[8]=0;

led_values[9]=85;
led_values[10]=85;
led_values[11]=85;
led_values[12]=85;
led_values[13]=85;
led_values[14]=85;
led_values[15]=85;
led_values[16]=85;
led_values[17]=85;

led_values[18]=170;
led_values[19]=170;
led_values[20]=170;
led_values[21]=85;
led_values[22]=0;
led_values[23]=85;
led_values[24]=170;
led_values[25]=170;
led_values[26]=170;
}
