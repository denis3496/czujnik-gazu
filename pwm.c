/*
 * uart.c
 *
 *  Created on: 20 wrz 2018
 *      Author: Denis
 */
#include "pwm.h"

void initInterrupt0(void){
	DDRB |= (1<<PB3);
	TCCR0 |= (1<<COM01)|(1<<COM00)|(1<<WGM01)|(1<<WGM00)|(1<<CS00);// inverting, fast pwm, prescaler 1
	OCR0 = dc_0;;
}

void calibrate_dutycycle(void)
{
	float tmp;
	tmp = 255-((VH_14/VCC)*255);
	dc_14= (uint8_t) tmp;

	tmp = 255-((VH_16/VCC)*255);
	dc_16= (uint8_t) tmp;

	dc_0=255;
}
