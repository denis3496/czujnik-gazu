/*
 * uart.h
 *
 *  Created on: 20 wrz 2018
 *      Author: Denis
 */

#ifndef PWM_H_
#define PWM_H_

#include "main.h"

#define VCC 4.69
#define VH_14 1.4
#define VH_16 1.6
#define VH_0 0;

 uint8_t dc_14;
 uint8_t dc_16;
 uint8_t dc_0;


void initInterrupt0(void);

void calibrate_dutycycle(void);

#endif /* PWM_H_ */
