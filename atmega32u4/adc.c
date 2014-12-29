//===============================acd.c==============================================
#include "adc.h"

uint16_t readADC( uint8_t adc_channel)
{
	uint32_t adc_Value = 0;
	
	// ADC deaktiviern
	ADCSRA &= ~(1<<ADEN); 
	ADCSRA &= ~(1<<ADSC); 

	switch (adc_channel) //wähle adc kanal
		{
		case 0:  adc_ch0; break;
		case 1:  adc_ch1; break;
		case 4:  adc_ch4; break;
		case 5:  adc_ch5; break;
		case 6:  adc_ch6; break;
		case 7:  adc_ch7; break;
		case 8:  adc_ch8; break;
		case 9:  adc_ch9; break;
		case 10:  adc_ch10; break;
		case 11:  adc_ch11; break;
		case 12:  adc_ch12; break;
		case 13:  adc_ch13; break;
		case 20: adc_temp; break;
		default:  {return (0);}	//fehler
		}

	ADCSRA |= (1<<ADEN); // ADC einschalten
	ADCSRA |= (1<<ADSC); // und initialisiern
	while(ADCSRA & (1 << ADSC)); //test messung 'leer'

	// ergebniss löschen
	ADCH = 0x00;
	ADCL = 0x00;

	// mittel aus 4 werten
		for (uint8_t g = 0; g < 4; g++) {
  			ADCSRA |= (1<<ADSC); //messung beginnen
			while(ADCSRA & (1 << ADSC)); // warten bis abgeschlossen
			adc_Value = adc_Value + ( ADC ); // wert speichern
			}	  
    adc_Value = adc_Value /4 ; //mittel aus den 4 werten
	return ADC; //wert zurückgeben
}

void adc_init () // adc initialisierung
{
	internal_vref
//	external_vref // siehe adc.h
	DDRF &= ~(( 1 << PF0 )|( 1 << PF1 ))   ;  // PIN PD 4,6,7 auf eingang  
	ADMUX &= ~(1<<ADLAR); //auf oder abrunden
	adc_ch10 //channel 10 zum einstellen
	ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)); //Prescaler auf 125KHz
	ADCSRA &= ~(1<<ADATE); //kein trigger mode
	ADCSRB |= (1<<ADHSM);//high speed mode
	ADCSRA |= (1<<ADEN); //einschalten
	ADCSRA |= (1<<ADSC); //initialisiern
	while(ADCSRA & (1 << ADSC)); //erste testmessung (leer)
}

