/*
 * adc.c
 *
 *  Created on: 20 wrz 2018
 *      Author: Denis
 */
#include "adc.h"
#include "mkuart.h"

void initADC(void){
	ADMUX|= (1<<ADLAR);
	ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	DDRA &=~ADC0;
}

ISR(ADC_vect){
	/*float tmp; PRZETWORZENIE WARTOSCI ANALOGOWEJ
	tmp = (ADCH*4.65)/255;*/
	uint8_t tmp= ADCL >>6;
	theTenBitResults= ADCH<<2 | tmp;// '|' oznacza '+'
//	uint8_t theLowADC = ADCL;
//	uint16_t theTenBitResults = ADCH<<8 | theLowADC;

}
