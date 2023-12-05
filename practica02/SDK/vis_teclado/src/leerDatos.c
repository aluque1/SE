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

int main()
{
	int operando1 = -1;
	int operando2 = -1;
	XGpio Gpio_LEDs;
	long status;
	// Initialize the GPIO driver so that it's ready to use
	// Device ID in xparameters.h
	status = XGpio_Initialize(&Gpio_LEDs, XPAR_XPS_GPIO_0_DEVICE_ID);
	if(status != XST_SUCCESS)
		return XST_FAILURE;

	// Set the direction for all signals to be outputs
	XGpio_SetDataDirection(&Gpio_LEDs, 1, 0x00);
	XGpio_DiscreteWrite(&Gpio_LEDs, 1, 0x00);

	while(operando1 <= 0 || operando1 >= 9){
		// escribe un mensaje en la pantalla
		xil_printf("Introduzca el primer operando. Tiene que estar entre 0-9\n\r");
		operando1 = getNumber();
	}
	// Set the GPIO outputs to operando1
	XGpio_DiscreteWrite(&Gpio_LEDs, 1, operando1);

	while(operando2 <= 0 || operando2 >= 9){
		// escribe un mensaje en la pantalla
		xil_printf("Introduzca el segundo operando. Tiene que estar entre 0-9\n\r");
		operando2 = getNumber();
	}
	// Set the GPIO outputs to operando1
	XGpio_DiscreteWrite(&Gpio_LEDs, 1, 0x00);
	XGpio_DiscreteWrite(&Gpio_LEDs, 1, operando2);

	int result = operando1 - operando2;

	XGpio_DiscreteWrite(&Gpio_LEDs, 1, 0x00);
	XGpio_DiscreteWrite(&Gpio_LEDs, 1, result);

	print("-- Exiting main() --\r\n");
	return status;
}
