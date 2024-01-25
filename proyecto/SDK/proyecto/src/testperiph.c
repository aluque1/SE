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
#include "kbd_ps2.h"
#include "buzzer.h"

//** Function Definitions **//
int getNumber();
char ps2ToAscii(int scanCode);

//** Function Definitions **//
int getNumber();
const int A[7] = {0x04, 0x05, 0x11, 0x1F, 0x11, 0x11, 0x11};

int main()
{
	Xuint32 opt = -1;
	Xuint32 keypadPass[4];
	Xuint32 ps2Pass[8];
	Xuint32 keypadTry[4];
	Xuint32 ps2Try[8];
	short cont = 3;

	leds_init();
	banner_init();
	print("---Entering main---\n\r");

	banner_put_phrase(START);
	do
	{
		print(" Eliga una opcion: \n\r");
		print(" 1  : KEYPAD (password of length 4)\n\r");
		print(" 2  : TECLADO (password of length 8)\n\r");
		print(" 0  : Salir \n\r");

		opt = getNumber();

		if (0 < opt || opt > 2)
			print("No es una opcion valida.\n\r");
		while (opt != 0)

		if(opt == 1){
			// record password
			record_passKP(keypadPass);
			print(" Passowrd saved\n\r");
			while(cont > 0){
				switch (cont)
				{
				case 3:	
					banner_put_phrase(INTENTO_1);
					break;
				case 2:
					banner_put_phrase(INTENTO_2);
					break;
				case 1:
					banner_put_phrase(INTENTO_3);
					break;
				default:
					// llamar a funcion de alarma
					break;
				}
				// try password
				record_passKP(keypadTry);
				int i;
				if(keypadTry[0] == keypadPass[0] && keypadTry[1] == keypadPass[1] && keypadTry[2] == keypadPass[2] && keypadTry[3] == keypadPass[3]){
					// llamar a la funcion de desbloqueo
					cont = 0;
				}
				else{
					--cont;
				}
			}
		}

		print("Saliendo ...\n\r");

		return 0;
	}

	print("---Exiting main---\n\r");
	return 0;
}

// Set 2 Make/Break codes to ASCII
char ps2ToAscii(int scanCode)
{
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
