/*
 * main.c
 *
 *  Created on: 18 wrz 2018
 *      Author: Denis
 */

#include "lcd44780.h"
#include "mkuart.h"
#include "adc.h"
#include "main.h" //// W PRZYPADKU GDY JEST MAIN.H TRZEBA TO DODAC DO KAZDEJ SZTUCZNIE DODANEJ BIBLIOTEKI(PLIKU .H) TAKIEJ JAK TA !!!
#include "pwm.h"

void set_systik(void){
	OCRxn_val = 0.5*(F_CPU/(2*PRESCALER*0.5)-1); //wylicza wartosc dla 0.5s
}

void initInterrupt1(void){
	TCCR1A |= 0;
	TCCR1B |= (1 << WGM12)|(1<<CS12) | (1<<CS10); // Ÿród³em CLK, preskaler 1024, Mode = CTC,
	TCNT1 = 0;
	TIMSK |= (1 << OCIE1A);
	OCR1A = OCRxn_val; // 0.5SEK. f_clk= 8MHz
	halfsec_count=0;
}


ISR(TIMER1_COMPA_vect) //tik co ok. 0.5 SEKUNDY
{
	halfsec_count++;
	lcd_locate(0,1);
	lcd_int(halfsec_count);

	if((halfsec_count==10) && (STATE==IDLE))
		{
			OCR0 =dc_16;// 1,6V
			halfsec_count=0;
			STATE=PREHEAT;
		}
	 if((halfsec_count==1) && (STATE== PREHEAT)){
		PORTB ^= ENABLE;
		OCR0 =dc_14;// 1,4V
		if(bit_is_clear(ADMUX,ADSC)) ADCSRA |= (1<<ADSC);
		halfsec_count=0;
		STATE=MEASUREMENT;
		lcd_cls();
	}
	 if((halfsec_count==2) && (STATE==MEASUREMENT)){
		PORTB ^= ENABLE;
		OCR0=dc_0;
		halfsec_count=0;
		STATE=IDLE;
		lcd_locate(1,1);
		lcd_int(theTenBitResults);
		uart_putint((int)theTenBitResults,10);
		uart_putc('\r');
		uart_putc('\n');
	}

}

int main(void){
	DDRB |= ENABLE;
	PORTB &=~ENABLE;
	USART_Init( __UBRR );
	calibrate_dutycycle();
	set_systik();
	initInterrupt0();
	initInterrupt1();
	initADC();
	lcd_init();
	STATE= IDLE;
	sei();
	while(1);

	return 0;
}



