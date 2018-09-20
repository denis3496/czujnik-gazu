/*
 * main.h
 *
 *  Created on: 20 wrz 2018
 *      Author: Denis
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>

uint16_t OCRxn_val;
uint8_t halfsec_count;
#define MEASUREMENT 0
#define PREHEAT 1
#define IDLE 2
unsigned char STATE;
#define PRESCALER 1024
#define ENABLE (1<<PB4)

#endif /* MAIN_H_ */
