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

/**
 * User definitions for the banner
 */
const int A[7] = {0x04, 0x0A, 0x11, 0x11, 0x1F, 0x11, 0x11}; 
const int C[7] = {0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E}; 
const int D[7] = {0x1E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1E}; 
const int E[7] = {0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x1F}; 
const int K[7] = {0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11}; 
const int L[7] = {0x10, 0x10, 0x10, 0x10, 0x10, 0x11, 0x1F}; 
const int M[7] = {0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11}; 
const int N[7] = {0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11}; 
const int O[7] = {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}; 
const int R[7] = {0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11}; 
const int S[7] = {0x0E, 0x11, 0x10, 0x0E, 0x01, 0x11, 0x0E}; 
const int T[7] = {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}; 
const int U[7] = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}; 
const int Y[7] = {0x11, 0x11, 0x11, 0x0A, 0x04, 0x04, 0x04}; 
const int ONE[7] = {0x04, 0x0C, 0x14, 0x04, 0x04, 0x04, 0x1F};
const int TWO[7] = {0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F};
const int THREE[7] = {0x0E, 0x11, 0x01, 0x06, 0x01, 0x11, 0x0E};

//** Function Definitions **//
int getNumber();
void doKeypadPW();
void doPs2PW();
void soundAlarm();
void unlock();

void put_start(){
	banner_init();
	banner_put(0, S);
	banner_put(1, T);
	banner_put(2, A);
	banner_put(3, R);
	banner_put(4, T);
}
void put_alarm(){
	banner_init();
	banner_put(0, A);
	banner_put(1, L);
	banner_put(2, A);
	banner_put(3, R);
	banner_put(4, M);
	banner_put(5, A);
}
void put_unlocked(){
	banner_init();
	banner_put(0, U);
	banner_put(1, N);
	banner_put(2, L);
	banner_put(3, O);
	banner_put(4, C);
	banner_put(5, K);
	banner_put(6, E);
	banner_put(7, D);
}
void put_intento1()
{
	banner_init();
	banner_put(3, T);
	banner_put(4, R);
	banner_put(5, Y);
	banner_put(7, ONE);
}
void put_intento2()
{
	banner_init();
	banner_put(3, T);
	banner_put(4, R);
	banner_put(5, Y);
	banner_put(7, TWO);
}
void put_intento3()
{
	banner_init();
	banner_put(3, T);
	banner_put(4, R);
	banner_put(5, Y);
	banner_put(7, THREE);
}

int main()
{
	Xuint32 opt = -1;

	leds_init();
	banner_init();
	print("---Entering main---\n\r");

	put_start();
	do
	{
		print(" Eliga una opcion: \n\r");
		print(" 1  : KEYPAD (password of length 4)\n\r");
		print(" 2  : TECLADO (password of length 8)\n\r");
		print(" 0  : Salir \n\r");
		opt = getNumber();

	} while (opt < 0 || opt > 2);

	switch (opt)
	{
	case 0:
		print("Saliendo... \n\r");
		break;
	case 1:
		doKeypadPW();
		break;
	case 2:
		doPs2PW();
		break;
	default:
		print("Opcion no valida\n\r");
		break;
	}

	print("Saliendo ...\n\r");

	return 0;
}
void doKeypadPW()
{
	short cont = 3;
	Xuint32 keypadPass[4];
	Xuint32 keypadTry[4];

	record_passKP(keypadPass);
	print(" Passoword saved\n\r");
	while (cont > -1)
	{
		if(cont == 3){
			put_intento1();
		}
		else if(cont == 2){
			put_intento2();
		}
		else if(cont == 1){
			put_intento3();
		}
		else{
			soundAlarm();
		}
		record_passKP(keypadTry);
		if (keypadTry[0] == keypadPass[0] && keypadTry[1] == keypadPass[1] && keypadTry[2] == keypadPass[2] && keypadTry[3] == keypadPass[3])
		{
			unlock();
			cont = -1;
		}
		else
		{
			--cont;
		}
	}
}

void doPs2PW()
{
	short cont = 3;
	Xuint32 ps2Pass[8];
	Xuint32 ps2Try[8];

	record_passPS2(ps2Pass);
	print(" Passoword saved\n\r");
	while (cont > -1)
	{
		if(cont == 3){
			put_intento1();
		}
		else if(cont == 2){
			put_intento2();
		}
		else if(cont == 1){
			put_intento3();
		}
		else{
			soundAlarm();
		}
		record_passPS2(ps2Try);
		if (ps2Try[0] == ps2Pass[0] && ps2Try[1] == ps2Pass[1] && ps2Try[2] == ps2Pass[2] && ps2Try[3] == ps2Pass[3] && ps2Try[4] == ps2Pass[4] && ps2Try[5] == ps2Pass[5] && ps2Try[6] == ps2Pass[6] && ps2Try[7] == ps2Pass[7])
		{
			unlock();
			cont = -1;
		}
		else
		{
			--cont;
		}
	}
}

void soundAlarm()
{
	unsigned int i;
	XGpio Gpio_zumbador;
	Xuint32 zumbador = XPAR_BUZZER_0_DEVICE_ID;
	ZUMBADOR_init(&Gpio_zumbador, zumbador);
	put_alarm();

	while (1)
	{
		ZUMBADOR_suena(&Gpio_zumbador);
		xil_printf("Suena\r\n");
		LEDS_RGB_mWriteSlaveReg0(XPAR_LEDS_RGB_0_BASEADDR, 0, 0); // encender led rojo
		for (i = 0; i < 0x00070000; i++)
		{
		} // retardo

		ZUMBADOR_calla(&Gpio_zumbador);
		xil_printf("Calla\r\n");
		LEDS_RGB_mWriteSlaveReg0(XPAR_LEDS_RGB_0_BASEADDR, 0, 255); // apagar led rojo
		for (i = 0; i < 0x00070000; i++)
		{
		} // retardo
	}
}

void unlock()
{
	unsigned int i;
	put_unlocked();						  // imprimir mensaje de desbloqueo
	LEDS_RGB_mWriteSlaveReg1(XPAR_LEDS_RGB_0_BASEADDR, 0, 0); // encender led verde
	for (i = 0; i < 0x0007F000; i++)
	{
	}															// retardo
	LEDS_RGB_mWriteSlaveReg1(XPAR_LEDS_RGB_0_BASEADDR, 0, 255); // apagar led verde
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
