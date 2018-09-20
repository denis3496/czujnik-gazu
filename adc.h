/*
 * adc.h
 *
 *  Created on: 20 wrz 2018
 *      Author: Denis
 */

#ifndef ADC_H_
#define ADC_H_

#include "main.h"
#define ADC0 (1<<PA0)
void initADC(void);

uint16_t theTenBitResults;

#endif /* ADC_H_ */
