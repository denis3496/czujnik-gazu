/*
 * main.c
 *
 *  Created on: 18 wrz 2018
 *      Author: Denis
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "lcd44780.h"
uint8_t halfsec_count;
#define MEASUREMENT 0
#define PREHEAT 1
#define IDLE 2
volatile unsigned char STATE;
volatile uint8_t dc_14;
volatile uint8_t dc_16;
volatile uint8_t dc_0;
#define VCC 4.69
#define VH_14 1.4
#define VH_16 1.6
#define VH_0 0;
#define PRESCALER 1024

uint16_t OCRxn_val;



void calibrate_dutycycle(void)
{
	float tmp;
	tmp = 255-((VH_14/VCC)*255);
	dc_14= (uint8_t) tmp;

	tmp = 255-((VH_16/VCC)*255);
	dc_16= (uint8_t) tmp;

	dc_0=255;
}

void set_systik(void){
	OCRxn_val = 0.5*(F_CPU/(2*PRESCALER*0.5)-1); //wylicza wartosc dla 0.5s
}

void initInterrupt0(void){
	DDRB |= (1<<PB3);
	TCCR0 |= (1<<COM01)|(1<<COM00)|(1<<WGM01)|(1<<WGM00)|(1<<CS00);// inverting, fast pwm, prescaler 1
	OCR0 = dc_0;;
	STATE= IDLE;
}
void initInterrupt1(void){
	TCCR1A |= 0;
	TCCR1B |= (1 << WGM12)|(1<<CS12) | (1<<CS10); // Ÿród³em CLK, preskaler 1024, Mode = CTC,
	TCNT1 = 0;
	TIMSK |= (1 << OCIE1A);
	OCR1A = OCRxn_val; // 0.5SEK. f_clk= 8MHz
	halfsec_count=0;
}

ISR(TIMER1_COMPA_vect) //tik co ok. 1 sekunde
{
	halfsec_count++;
	  lcd_locate(0,1);
		  lcd_int(halfsec_count);

	if((halfsec_count==117) && (STATE==IDLE))
		{
			OCR0 =dc_16;// 1,6V
			halfsec_count=0;
			STATE=PREHEAT;
			lcd_cls();

		}
	 if((halfsec_count==1) && (STATE== PREHEAT)){
		OCR0 =dc_14;// 1,4V
		halfsec_count=0;
		STATE=MEASUREMENT;
		lcd_cls();
	}
	 if((halfsec_count==2) && (STATE==MEASUREMENT)){
		OCR0=dc_0;
		halfsec_count=0;
		STATE=IDLE;
		lcd_cls();
	}
}

int main(void){
	calibrate_dutycycle();
	set_systik();
	initInterrupt0();
	initInterrupt1();
	lcd_init();
	sei();
	while(1);

	return 0;
}



