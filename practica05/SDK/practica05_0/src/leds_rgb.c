/*****************************************************************************
* Filename:          C:\Users\aluqu\Desktop\uni\SE\practica05/drivers/leds_rgb_v1_00_a/src/leds_rgb.c
* Version:           1.00.a
* Description:       leds_rgb Driver Source File
* Date:              Mon Dec 18 10:19:14 2023 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "leds_rgb.h"

/************************** Function Definitions ***************************/

void init_leds(){
	LEDS_RGB_mWriteSlaveReg0(XPAR_LEDS_RGB_0_BASEADDR, 0, 255);
	LEDS_RGB_mWriteSlaveReg1(XPAR_LEDS_RGB_0_BASEADDR, 0, 255);
	LEDS_RGB_mWriteSlaveReg2(XPAR_LEDS_RGB_0_BASEADDR, 0, 255);
}

