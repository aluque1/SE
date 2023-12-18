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

//** Function Definitions **//
int getNumner();

int main() 
{
   Xuint32 Reg32Value, TeclaOld;
   Xuint32 opt;

   print("---Entering main---\n\r");

   print(" LED's \n\r");
   print("Que color quieres cambiar de intensidad (1 = rojo, 2 = verde, 3 = azul)\n\r");
   opt = getNumber();
   switch (opt){
   case 1:
	   print("Introduce la intensidad del color rojo (0-255)\n\r");
	   Reg32Value = getNumber();
	   LEDS_mWriteReg(XPAR_LEDS_0_BASEADDR, 0, Reg32Value);
	   break;
   case 2:
	   print("Introduce la intensidad del color verde (0-255)\n\r");
	   Reg32Value = getNumber();
	   LEDS_mWriteReg(XPAR_LEDS_0_BASEADDR, 1, Reg32Value);
	   break;
   case 3:
	   print("Introduce la intensidad del color azul (0-255)\n\r");
	   Reg32Value = getNumber();
	   LEDS_mWriteReg(XPAR_LEDS_0_BASEADDR, 2, Reg32Value);
	   break;
	default:
		print("Opcion no valida\n\r");
		break;
   }

   print(" KEYPAD \n\r");
   print(" Pulse una tecla cualquiera \n\r");
   Reg32Value = KEYPAD_mReadReg(XPAR_KEYPAD_0_BASEADDR, 0);
   xil_printf("   Se ha leido %d del registro 0 del teclado \n\r", Reg32Value);
   KEYPAD_mWriteReg(XPAR_KEYPAD_0_BASEADDR, 0,0);
   TeclaOld=Reg32Value;
   while (1){
	   if (Reg32Value != TeclaOld)
		   xil_printf("    Se ha leido %d del registro 0 del teclado \n\r", Reg32Value);
	   TeclaOld = Reg32Value;
	   Reg32Value = KEYPAD_mReadReg (XPAR_KEYPAD_0_BASEADDR, 0);
	   KEYPAD_mWriteReg(XPAR_KEYPAD_0_BASEADDR, 0,0); /* Se escribe un 0 en el registro del teclado para borrar la �ltima tecla le�da */
	   
   }

   print("---Exiting main---\n\r");

   return 0;
}

int getNumber (){
	Xuint8 byte;
	Xuint8 uartBuffer[16];
	Xboolean validNumber;
	int digitIndex;
	int digit, number, sign;
	int c;	
	
	while(1){
		byte = 0x00;
		digit = 0;
		digitIndex = 0;
		number = 0;
		validNumber = XTRUE;
	
		//get bytes from uart until RETURN is entered
	
		while(byte != 0x0d && byte != 0x0A){
			byte = XUartLite_RecvByte(XPAR_XPS_UARTLITE_0_BASEADDR);
			uartBuffer[digitIndex] = byte; 
			XUartLite_SendByte(XPAR_XPS_UARTLITE_0_BASEADDR,byte);
			digitIndex++;
		}
			 
		//calculate number from string of digits
	
		for(c = 0; c < (digitIndex - 1); c++){
			if(c == 0){
				//check if first byte is a "-"
				if(uartBuffer[c] == 0x2D){
					sign = -1;
					digit = 0;
				}
				//check if first byte is a digit
				else if((uartBuffer[c] >> 4) == 0x03){
					sign = 1;
					digit = (uartBuffer[c] & 0x0F);
				}
				else	
					validNumber = XFALSE;	
			}
			else{
				//check byte is a digit
				if((uartBuffer[c] >> 4) == 0x03){  
					digit = (uartBuffer[c] & 0x0F);
				}
				else	
					validNumber = XFALSE;				
			}
			number = (number * 10) + digit;	
		}
		number *= sign;
		if(validNumber == XTRUE){
			return number;
		}
		print("This is not a valid number");
	}
}
