/*
 * buzzer.h
 *
 *  Created on: Jan 25, 2024
 *      Author: aluqu
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "xparameters.h"
#include "stdio.h"
#include "xutil.h"

#include "xgpio.h"

void ZUMBADOR_init(XGpio* Gpio_zumbador, Xuint32 zumbador);
void ZUMBADOR_suena(XGpio* Gpio_zumbador);
void ZUMBADOR_calla(XGpio *Gpio_zumbador);
void ZUMBADOR_oscila();


#endif /* BUZZER_H_ */
