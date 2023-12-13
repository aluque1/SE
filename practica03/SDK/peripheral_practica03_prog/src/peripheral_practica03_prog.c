/*
 * peripheral_practica03_prog.c
 *
 *  Created on: 12 Dec 2023
 *      Author: aluqu
 */

/*****************************
 * 		Include Files
*******************************/
#include <stdio.h>

#include "peripheral_practica03_prog.h"
#include "xparameters.h"
#include "xil_cache.h"
#include "xbasic_types.h"
/**************************
 * 		Function Definitions
***************************/
XStatus periphal_practica03_prog_SelfTest(void * baseaddr_p);
int getNumber();

int main() {
	Xuint32 valor, baseaddr;
	baseaddr = XPAR_PERIPHERAL_PRACTICA03_0_BASEADDR;

	print("-- Bienvenido --\n\r");

	print("Introduzca numero para reg0 (0 suma, 1 resta): \n\r");
	valor = getNumber();
	// escribir a reg0 y mostrar valor
	MY_PERIPHERAL_mWriteSlaveReg0(baseaddr, 0, valor);
	valor = MY_PERIPHERAL_mReadSlaveReg0(baseaddr, 0);
	xil_printf("Escrito: %d en reg0\n\r", valor);

	print("Introduzca numero para reg1: \n\r");
	valor = getNumber();
	// escribir a reg1 y mostrar valor
	MY_PERIPHERAL_mWriteSlaveReg1(baseaddr, 0, valor);
	valor = MY_PERIPHERAL_mReadSlaveReg1(baseaddr, 0);
	xil_printf("Escrito: %d en reg1\n\r", valor);

	print("Introduzca numero para reg2: \n\r");
	valor = getNumber();
	// escribir a reg2 y mostrar valor
	MY_PERIPHERAL_mWriteSlaveReg2(baseaddr, 0, valor);
	valor = MY_PERIPHERAL_mReadSlaveReg2(baseaddr, 0);
	xil_printf("Escrito: %d en reg2\n\r", valor);

	//mostrar reg3 por pantalla
	valor = MY_PERIPHERAL_mReadSlaveReg0(baseaddr, 0);
	if(valor & 1) // si el ultimo bit es 1
		print("reg1 - reg2 = ");
	else
		print("reg1 + reg2 = ");
	valor = MY_PERIPHERAL_mReadSlaveReg3(baseaddr, 0);
	xil_printf("%d\n\r", valor);

	print("-- Exiting main() --\r\n");
	return XST_SUCCESS;
}


/*
* @ param baseaddr_p is the base address of the MY_PERIPHERAL instance to be worked on.
*
* @return
*
* - XST_SUCCESS if all self-test code passed
* - XST_FAILURE if any self-test code failed
*
*/
XStatus periphal_practica03_prog_SelfTest(void * baseaddr_p)
{
	int Index;
	Xuint32 baseaddr;
	Xuint8 Reg8Value;
	Xuint16 Reg16Value;
	Xuint32 Reg32Value;
	// Base Address maybe 0. Up to developer to uncomment line below.

	// XASSERT_NONVOID(baseaddr_p != XNULL);

	baseaddr = (Xuint32) baseaddr_p;
	xil_printf("******************************\n\r");
	xil_printf("* User Peripheral Self Test  *\n\r");
	xil_printf("******************************\n\n\r");

	xil_printf(" - write 1 to slave register 0 word 0\n\r");
	MY_PERIPHERAL_mWriteSlaveReg0(baseaddr, 0, 1);
	Reg32Value = MY_PERIPHERAL_mReadSlaveReg0(baseaddr, 0);
	xil_printf(" - read %d from register 0 word 0\n\r", Reg32Value);
	if (Reg32Value != 1)
	{
		xil_printf(" - slave register 0 word 0 write/read failed\n\r");
		return XST_FAILURE;
	}

	xil_printf(" - write 1 to slave register 1 word 0\n\r");
	MY_PERIPHERAL_mWriteSlaveReg1(baseaddr, 0, 1);
	Reg32Value = MY_PERIPHERAL_mReadSlaveReg1(baseaddr, 0);
	xil_printf(" - read %d from register 1 word 0\n\r", Reg32Value);
	if (Reg32Value != 1)
	{
		xil_printf(" - slave register 1 word 0 write/read failed\n\r");
		return XST_FAILURE;
	}

	xil_printf(" - write 1 to slave register 2 word 0\n\r");
	MY_PERIPHERAL_mWriteSlaveReg2(baseaddr, 0, 1);
	Reg32Value = MY_PERIPHERAL_mReadSlaveReg2(baseaddr, 0);
	xil_printf(" - read %d from register 2 word 0\n\r", Reg32Value);
	if (Reg32Value != 1)
	{
		xil_printf(" - slave register 2 word 0 write/read failed\n\r");
		return XST_FAILURE;
	}
	
	// reg3 WRITE is desactivated through the VHDL
	xil_printf(" - write 1 to slave register 3 word 0\n\r");
	MY_PERIPHERAL_mWriteSlaveReg3(baseaddr, 0, 1);
	Reg32Value = MY_PERIPHERAL_mReadSlaveReg3(baseaddr, 0);
	xil_printf(" - read %d from register 3 word 0\n\r", Reg32Value);
	if (Reg32Value != 1)
	{
		xil_printf(" - slave register 3 word 0 write/read failed\n\r");
		return XST_FAILURE;
	}

	return XST_SUCCESS;
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
