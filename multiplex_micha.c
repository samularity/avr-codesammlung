//includes


main ()
{

DDRA = 0b00000000; 		// (8 dateneingänge 1|0 bis 4|1)  alle pins port b als eingang
PORTA = 0x00;			// interne Pull-Ups an allen Port-Pins deaktivieren 

DDRB = 0b00001111;    	//  (bit 0 bis 3 als ausgang 1Y bis 4Y) (bit 4 als enable und bit 5 als select  input)   port b pin 0,1,2,3 als ausgang rest eingang
PORTB &= ~(  (1<<PB4)   (1<<PB5)   ); // pullups deaktivieren für enable und select

bool enable = false;	//bit4 port b
bool select = false;	//bit5 port b


while(1)
	{
		enable = !(PINB & (1<<PINB4)); //enable ist true wenn portpin low 
		select = PINB & (1<<PINB5); //select true wenn portpin high

		if (select ==true && enable==true)
			{
				//ausgang 1Y in abhängikeit des eingangs setzten
				//das geht bestimmt auch schöner, weiß aber nicht wie
				if (PINA & (1 << PA0))		//wenn 1|0 high 
					{PORTB |= (1<<PB0);}	//high output 1Y (PB0)
				else						//wenn 1|0 low
					{PORTB &= ~(1<<PB0);}	//low output   1Y (PB0)
				  
				//... hier die 3 verbleibenden 2|0  , 3|0 , 4|0
			}
		else if (select ==false && enable==true)
			{
				//ausgang 1Y in abhängikeit des eingangs setzten
				if (PINA & (1 << PA1))		//wenn 1|1 high 
					{PORTB |= (1<<PB0);}	//high output 1Y (PB0)
				else						//wenn 1|1 low
					{PORTB &= ~(1<<PB1);}	//low output   1Y (PB0)
				  
				//... hier die 3 verbleibenden 2|1  , 3|1 , 4|1
			}
		else // enable ist falsch , eingänge sind egal
			{
				PORTB = 0x00; //alle ausgänge low
			}
	
	}
}

