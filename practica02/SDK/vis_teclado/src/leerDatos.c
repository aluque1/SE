#include <stdio.h>

#include <xstatus.h>

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




int operando1, operando2, result;
char key;
int main()
{
	/*
	// escribe un mensaje en la pantalla del hyperterminal
	xil_printf("Introduce una letra\n\r");
	
	// lee una letra de teclado 
	key = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
	
	// escribe una letra en la pantalla del hyperterminal
	XUartLite_SendByte(XPAR_RS232_UART_1_BASEADDR,key);
	print("\r\n");
	*/
	

	do{ // TODO maybe a while with a break would be better, the prompt before and the print after the while
		// escribe un mensaje en la pantalla
		xil_printf("Introduzca el primer operando. Tiene que estar entre 0-9\n\r");

		// lee un n�mero de teclado
		operando1 = getNumber();
		xil_printf("Operando 1: %d\n\r", operando1);
	}while(operando1 < 0 || operando1 > 9);

	do{
		// escribe un mensaje en la pantalla
		xil_printf("Introduzca el segundo operando. Tiene que estar entre 0-9\n\r");

		// lee un n�mero de teclado
		operando2 = getNumber();
		xil_printf("Operando 2: %d\n\r", operando2);
	}while(operando2 < 0 || operando2 > 9);

	result = operando1 - operando2;
	xil_printf("Resultado = %d\n\r", result);

	print("-- Exiting main() --\r\n");
	return 0;

}