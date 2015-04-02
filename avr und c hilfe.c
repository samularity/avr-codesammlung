
//makros
#define	SET_HIGH(s)		PORTB |= (1<<s);	//PB high
#define SET_LOW(s)		PORTB &= ~(1<<s);	//PB low
#define E6_toggle 		PORTE^=(1<<PINE6);	//toggelt einen pin



DDRA &= ~( (1<<PA0) | (1<<PA3) );  /* PA0 und PA3 als Eingaenge */
PORTA |= ( (1<<PA0) | (1<<PA3) );  /* Interne Pull-Up fuer beide einschalten */


DDRA = 0xff;  		//alle pins port a als ausgang

DDRB = 0x00; 		//alle pins port b als eingnag

DDRB = 0b00011111;    	//port b pin 0,1,2,3,4 als ausgang und 5,6,7 als eingng

PORTB = 0b00000100;     //port b pin 2 high
PORTB = 0b00000111;     //port b pin 0,1,2 high




char h;		// char h='a'; h='A'; h='\n';
char outs[20];  	//char array mit name outs 20 länge
char hallo[] = { 'H', 'a', 'l', 'l', 'o', ' ', 'W', 'e', 'l', 't', '\n', '\0' }; //0terinator von hans
const char hallo[] = { "Hallo Welt\n" }; //oterminator automatisch


uint8_t i;		// 8bit unsigned 		0	bis	255
int8_t j;		// 8bit signed  	  -128 	bis 	+127 
uint16_t k; 	// 16bit unsigend 		0	bis	65535
int16_t l; 		// 16bit signed  	–32768 	bis	+32767
uint32_t m;		// 32bit unsigned 		0	bis	4294967296
int32_t n;		// 32bit signed	  -2147483648 bis +2147483647

float o; 		// 32bit Fließkomma			1.2E-38 3.4E+38
double p;		// 64bit Fließkomma 		2.3E-308 1.7E+308

#define F_CPU 8000000UL  // 8 MHz
#include <util/delay.h>
void sleep_ms(uint16_t ms);   //wird benötigt um "variable" zeit zu pausieren
/* sleep schlaufe */
void sleep_ms(uint16_t ms){
	while(ms){
		ms--;
		_delay_ms(1);
	}
}



//for schleife
uint8_t i;
for (i = 0; i < 4; i++) { }

// int to ascii conversation
char Buffer[12]; // in diesem {} lokal
utoa( potValue, Buffer, 10 ); 
itoa( potValue, Buffer, 10 ); 


//switch bespiel
switch (variable) {
  case 1:       // Anweisungen für diesen Zweig, wenn variable == 1
    break;
  case 14: 
  case 17:      // Anweisungen für diesen Zweig, wenn variable == 14 oder 17
    break;
  default:      // Anweisungen wenn keine der oben definierten Bedingungen erfüllt ist
    break;
}



void bootloader (void) //springt beim atmega32 u4 in den bootloader
{
	MCUCR  |=  (1 << IVCE);  //IVCE  = 1		//register f?r restret
	MCUCR  |=  (1 << IVSEL); //IVSEL = 1		//register f?r restret
	TIMSK0 = 0;             //Timer-Interrupt ausschalten
	TIMSK1 = 0;				//noch ein Timer-Interrupt ausschalten
	TIMSK4 = 0;				//und noch einer
	sleep_ms(500);
	asm volatile ("jmp 0x3800");
}

//arry füllen
memset	(&inputbuffer,0,250);//memset fills array &inputbuffer with 0's



if (strncmp(command,"movex ",6)==0) // prüft anfang vom string
{  
	stepper_x_move (  200 *  (atol	(command+6))); // wandelt ab dem 6.zeichen in zahl
 }
 
 
 
 
 /***************************************************************************************
 AVR PIN als Touch sensor missbrauchen
 ****************************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
typedef unsigned char  u8;
typedef unsigned short u16;
u8 getcap( void )
{
  u8 i = 10;
  DDRD &= ~(1<<PD5);                     	// input
  PORTD |= 1<<PD5;      			// pullup on
	for (int n=10; n>0; n--) {
	if( PIND & 1<<PD5 )
		i--;
		}
  PORTD &= ~(1<<PD5);			// low level
  DDRD |= 1<<PD5;                        	// discharge
  return i;
}
int main(void){
	DDRB = 0xff; //als ausgang
 u16 i;
  for(;;){
    i = getcap();
    if( i < 2 )				
		PORTB = 0b00000000; 
    else
		PORTB = 0b00000001;
		_delay_us (2);
		PORTB = 0b00000000; 
		_delay_us (2);
  }
}


/**********************************************
************      Ringbuffer     **************
**********************************************/

#define BUFFER_SIZE 256 // muss 2^n betragen (8, 16, 32, 64 , 128 , 256, 512, ...)
#define BUFFER_MASK (BUFFER_SIZE-1) // Klammern auf keinen Fall vergessen

int8_t BufferIn(uint8_t byte);
int8_t BufferOut(uint8_t *pByte);

struct RingBuffer
{
  uint8_t Data[BUFFER_SIZE];
  uint16_t WritePos;
  uint16_t ReadPos;
  bool	EndOfLine;
} ringbuffer = {{},0,0,false};

int8_t BufferIn(uint8_t byte)
{
  uint8_t next = ((ringbuffer.WritePos + 1) & BUFFER_MASK);
  if (ringbuffer.ReadPos == next)
    return -1;//buffer full
  ringbuffer.Data[ringbuffer.WritePos] = byte;
  if ((byte == '\r')||(byte == '\n'))
	  ringbuffer.EndOfLine=true;
  // ringbuffer.Data[buffer.WritePos & BUFFER_MASK] = byte; // absolut Sicher
  ringbuffer.WritePos = next;
  return 0;//SUCCESS
}

int8_t BufferOut(uint8_t *pByte)
{
  if (ringbuffer.ReadPos == ringbuffer.WritePos)
    return -1;//buffer empty
  *pByte = ringbuffer.Data[ringbuffer.ReadPos];
//  *pByte = ringbuffer.Data[ringbuffer.ReadPos];
  if ((*pByte=='\r')||(*pByte=='\n'))
	  ringbuffer.EndOfLine=false;
  ringbuffer.ReadPos = (ringbuffer.ReadPos+1) & BUFFER_MASK;
  return 0;//SUCCESS
}



