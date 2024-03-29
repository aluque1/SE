/*****************************************************************************
 * Filename:          C:\Users\aluqu\Desktop\uni\SE\practica05/drivers/leds_rgb_v1_00_a/src/leds_rgb.c
 * Version:           1.00.a
 * Description:       leds_rgb Driver Source File
 * Date:              Mon Dec 18 10:19:14 2023 (by Create and Import Peripheral Wizard)
 *****************************************************************************/

/***************************** Include Files *******************************/

#include "leds_rgb.h"

/************************** Function Definitions ***************************/

void leds_init()
{
	LEDS_RGB_mWriteSlaveReg0(XPAR_LEDS_RGB_0_BASEADDR, 0, 255);
	LEDS_RGB_mWriteSlaveReg1(XPAR_LEDS_RGB_0_BASEADDR, 0, 255);
	LEDS_RGB_mWriteSlaveReg2(XPAR_LEDS_RGB_0_BASEADDR, 0, 255);
}

void do_leds()
{
	Xuint32 opt, led_color;
	led_color = -1;

	print("##### LED's #####\n\r");
	do
	{
		print("1  : Cambiar intensidad del rojo\n\r");
		print("2  : Cambiar intensidad del verde\n\r");
		print("3  : Cambiar intensidad del azul\n\r");
		print("0  : Salir\n\r");
		opt = getNumber();
		switch (opt)
		{
		case 0:
			print("Saliendo ...\n\r");
			break;
		case 1:
			while (led_color < 0 || led_color > 255)
			{
				print("Introduce la intensidad del color rojo (0-255)\n\r");
				led_color = getNumber();
			}
			LEDS_RGB_mWriteSlaveReg0(XPAR_LEDS_RGB_0_BASEADDR, 0, (255 - led_color));
			break;
		case 2:
			while (led_color < 0 || led_color > 255)
			{
				print("Introduce la intensidad del color verde (0-255)\n\r");
				led_color = getNumber();
			}
			LEDS_RGB_mWriteSlaveReg1(XPAR_LEDS_RGB_0_BASEADDR, 0, (255 - led_color));
			break;
		case 3:
			while (led_color < 0 || led_color > 255)
			{
				print("Introduce la intensidad del color azul (0-255)\n\r");
				led_color = getNumber();
			}
			LEDS_RGB_mWriteSlaveReg2(XPAR_LEDS_RGB_0_BASEADDR, 0, (255 - led_color));
			break;
		default:
			print("No es una opcion valida.\n\r");
			break;
		}
		led_color = -1;
	} while (opt != 0);
}
