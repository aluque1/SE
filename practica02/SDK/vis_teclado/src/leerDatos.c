#include <stdio.h>

#include "xparameters.h"
#include "xil_cache.h"
#include "xbasic_types.h"
#include "xgpio.h"

#define XPAR_RS232_UART_1_BASEADDR 0x84000000
  
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
			byte = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
			uartBuffer[digitIndex] = byte; 
			XUartLite_SendByte(XPAR_RS232_UART_1_BASEADDR,byte);
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

// Write the num to leds do it inline
void gpio_write(XGpio leds, int num){
	XGpio_DiscreteWrite(&leds, 1, 0x00);
	XGpio_DiscreteWrite(&leds, 1, num);
}

int main()
{
	int operando1 = -1;
	int operando2 = -1;
	int wait = -1;
	XGpio Gpio_LEDs, Gpio_SWs;
	long status;
	int option = -1;

	// initialize leds
	// Initialize the GPIO driver so that it's ready to use
	// Device ID in xparameters.h
	status = XGpio_Initialize(&Gpio_LEDs, XPAR_XPS_GPIO_0_DEVICE_ID);
	if(status != XST_SUCCESS)
		return XST_FAILURE;

	// initialize switches
	status = XGpio_Initialize(&Gpio_SWs, XPAR_XPS_GPIO_1_DEVICE_ID);
	if(status != XST_SUCCESS)
		return XST_FAILURE;
	// Set the direction for all signals of leds to be outputs
	XGpio_SetDataDirection(&Gpio_LEDs, 1, 0x00);
	XGpio_SetDataDirection(&Gpio_SWs, 1, 0xFFFFFFFF);

	while(1){
		print("-- Bienvenido --\n\r");
			print(" Elija una opcion:\n\r");
			print("1  : Visualizar dato introducido por teclado\n\r");
			print("2  : Restador con operandos introducidos por teclado\n\r");
			print("3  : Visualizar dato introducio por switches\n\r");

			option = getNumber();
			switch(option){

			case 1:
				print("Visualizacion de dato introducido por teclado\n\r");
				while(operando1 < 0 || operando1 > 9){
					print("Introduzca un numero. Tiene que estar entre 0-9\n\r");
					operando1 = getNumber();
				}
				gpio_write(Gpio_LEDs, operando1);
				break;
			case 2:
				print("Restador con operandos escrito por teclado\n\r");
				while(operando1 < 0 || operando1 > 9){
					print("Introduzca el primer operando. Tiene que estar entre 0-9\n\r");
					operando1 = getNumber();
				}
				gpio_write(Gpio_LEDs, operando1);

				while(operando2 <= 0 || operando2 >= 9){
					print("Introduzca el segundo operando. Tiene que estar entre 0-9\n\r");
					operando2 = getNumber();
				}
				gpio_write(Gpio_LEDs, operando2);

				while(wait != 0){
					xil_printf("Introduzca 0 para obtener el resultado de %d - %d\n\r", operando1, operando2);
					wait = getNumber();
				}

				int result = operando1 - operando2;
				gpio_write(Gpio_LEDs, result);

				break;
			case 3:

				while(operando1 != 0){
					print("Use los switches para elegir su numero. Introduzca 0 cuando este elegido.\n\r");
					operando1 = getNumber();
				}
				operando2 = XGpio_DiscreteRead(&Gpio_SWs, 1);
				gpio_write(Gpio_LEDs, operando2);
				break;
			// do default
			}
	}

	print("-- Exiting main() --\r\n");
	return status;
}
