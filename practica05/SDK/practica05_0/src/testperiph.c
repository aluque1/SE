/*
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 *
 *
 * This file is a generated sample test application.
 *
 * This application is intended to test and/or illustrate some
 * functionality of your system.  The contents of this file may
 * vary depending on the IP in your system and may use existing
 * IP driver functions.  These drivers will be generated in your
 * SDK application project when you run the "Generate Libraries" menu item.
 *
 */

#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xbasic_types.h"
#include "banner.h"
#include "keypad.h"
#include "leds_rgb.h"

//** Function Definitions **//
int getNumner();

int main()
{
	Xuint32 Reg32Value, TeclaOld;
	Xuint32 opt, led_color;

	init_leds();

	print("---Entering main---\n\r");

	print("##### LED's #####\n\r");
	do{
		led_color = -1;
		print("1  : Cambiar intensidad del rojo\n\r");
		print("2  : Cambiar intensidad del verde\n\r");
		print("3  : Cambiar intensidad del azul\n\r");
		print("0  : Salir\n\r");
		opt = getNumber();
		switch(opt){
		case 0:
			print("Saliendo ...\n\r");
			break;
		case 1:
			while(led_color < 0 || led_color > 255){
				print("Introduce la intensidad del color rojo (0-255)\n\r");
				led_color = getNumber();
			}
			LEDS_RGB_mWriteSlaveReg0(XPAR_LEDS_RGB_0_BASEADDR, 0, !led_color);
			break;
		case 2:
			while(led_color < 0 || led_color > 255){
				print("Introduce la intensidad del color verde (0-255)\n\r");
				led_color = getNumber();
			}
			LEDS_RGB_mWriteSlaveReg1(XPAR_LEDS_RGB_0_BASEADDR, 0, !led_color);
			break;
		case 3:
			while(led_color < 0 || led_color > 255){
				print("Introduce la intensidad del color azul (0-255)\n\r");
				led_color = getNumber();
			}
			LEDS_RGB_mWriteSlaveReg2(XPAR_LEDS_RGB_0_BASEADDR, 0, !led_color);
			break;
		default:
			print("No es una opcion valida.\n\r");
			break;
		}
	}
	while(opt != 0);

	print("---Exiting main---\n\r");
	return 0;
	/*
	print("##### KEYPAD #####\n\r");
	print(" Pulse una tecla cualquiera \n\r");
	Reg32Value = KEYPAD_mReadReg(XPAR_KEYPAD_0_BASEADDR, 0);
	xil_printf("   Se ha leido %d del registro 0 del teclado \n\r", Reg32Value);
	KEYPAD_mWriteReg(XPAR_KEYPAD_0_BASEADDR, 0, 0);
	TeclaOld = Reg32Value;
	while (1)
	{
		if (Reg32Value != TeclaOld)
			xil_printf("    Se ha leido %d del registro 0 del teclado \n\r", Reg32Value);
		TeclaOld = Reg32Value;
		Reg32Value = KEYPAD_mReadReg(XPAR_KEYPAD_0_BASEADDR, 0);
		KEYPAD_mWriteReg(XPAR_KEYPAD_0_BASEADDR, 0, 0); // Se escribe un 0 en el registro del teclado para borrar la ultima tecla leida
	}
	*/

	/* enter a hex code for the color with the keypad and use that hex to get the rgb code */
	/* use the rgb code to change the intensity of the color */
	/*print("##### Testing keypad and hexcodes #####\n\r");
	Xuint32 hex_color[6];
	int cont = 0;
	while (cont < 6)
	{
		Reg32Value = KEYPAD_mReadReg(XPAR_KEYPAD_0_BASEADDR, 0);
		xil_printf("   Se ha leido %d del registro 0 del teclado \n\r", Reg32Value);
		KEYPAD_mWriteReg(XPAR_KEYPAD_0_BASEADDR, 0, 0);
		hex_color[cont] = Reg32Value;
		++cont;
	}
	// convert hex to decimal for red, green and blue components
	Xuint32 red = (hex_color[0] * 16) + hex_color[1];
	Xuint32 green = (hex_color[2] * 16) + hex_color[3];
	Xuint32 blue = (hex_color[4] * 16) + hex_color[5];
	// change the intensity of the color
	LEDS_RGB_mWriteSlaveReg0(XPAR_LEDS_RGB_0_BASEADDR, 0, red);
	LEDS_RGB_mWriteSlaveReg1(XPAR_LEDS_RGB_0_BASEADDR, 1, green);
	LEDS_RGB_mWriteSlaveReg2(XPAR_LEDS_RGB_0_BASEADDR, 2, blue);

	print(" MIRA LOS LEDs \n\r");
	*/
}

int getNumber()
{
	Xuint8 byte;
	Xuint8 uartBuffer[16];
	Xboolean validNumber;
	int digitIndex;
	int digit, number, sign;
	int c;

	while (1)
	{
		byte = 0x00;
		digit = 0;
		digitIndex = 0;
		number = 0;
		validNumber = XTRUE;

		// get bytes from uart until RETURN is entered

		while (byte != 0x0d && byte != 0x0A)
		{
			byte = XUartLite_RecvByte(XPAR_XPS_UARTLITE_0_BASEADDR);
			uartBuffer[digitIndex] = byte;
			XUartLite_SendByte(XPAR_XPS_UARTLITE_0_BASEADDR, byte);
			digitIndex++;
		}

		// calculate number from string of digits

		for (c = 0; c < (digitIndex - 1); c++)
		{
			if (c == 0)
			{
				// check if first byte is a "-"
				if (uartBuffer[c] == 0x2D)
				{
					sign = -1;
					digit = 0;
				}
				// check if first byte is a digit
				else if ((uartBuffer[c] >> 4) == 0x03)
				{
					sign = 1;
					digit = (uartBuffer[c] & 0x0F);
				}
				else
					validNumber = XFALSE;
			}
			else
			{
				// check byte is a digit
				if ((uartBuffer[c] >> 4) == 0x03)
				{
					digit = (uartBuffer[c] & 0x0F);
				}
				else
					validNumber = XFALSE;
			}
			number = (number * 10) + digit;
		}
		number *= sign;
		if (validNumber == XTRUE)
		{
			return number;
		}
		print("This is not a valid number");
	}
}
