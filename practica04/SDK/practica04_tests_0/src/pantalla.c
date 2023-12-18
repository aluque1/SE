/*****************************************************************************
* Filename:          C:\Users\aluqu\Desktop\uni\SE\practica04/SDK/pantalla_practica04/src/pantalla.c
* Version:           1.00.a
* Description:       pantalla Driver Source File
* Date:              Wed Dec 13 14:02:28 2023 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "pantalla.h"
#include <stdio.h>
#include "xparameters.h"

/*************************** Const and Defines *****************************/

#define ROJO 0x000001C0
#define VERDE 0x00000038
#define VERDE_OSCURO 0x00000018
#define N_ROWS 16

/************************** Function Definitions ***************************/

int getNumber();

/* 
Ejemplo de escritura en la FIFO
  	posicion=columna *nfilas + fila; // nfilas =16
	color=ROJO;
	Data= ((color & 0x1FF) << 23)| (posicion & 0x7f) ;
	PANTALLA_mWriteToFIFO(baseaddr, 0, Data);
 * */


int main()
{
    int screen_addr = XPAR_PANTALLA_0_BASEADDR;
    int posicion, color, data, row, column;

    print("-- Bienvenido a la practica 4 --\n\r");
    print("-- Elija una opcion: \n\r");
    print("     1. Apartado 1\n\r");
    print("     2. Apartado 2\n\r");
    print("     3. Apartado 3\n\r");

    int option = getNumber();

    switch(option){
    case 1:
    	print("-- Apartado 1 --\n\r");
    	// ask for a color (0 = red, 1 = green, 2 = dark green)
    	do{
    		print("Introduzca un color. 0 = rojo, 1 = verde, 2 = verde oscuro\n\r");
    		color = getNumber();
    	}while(color < 0 || color > 2);
    	// ask for the row
    	do {
    		print("Introduzca la fila. Tiene que estar entre 0-15\n\r");
    		row = getNumber();
    	}while(row < 0 || row > 15);

    	// ask for the column
    	do {
    		print("Introduzca la columna. Tiene que estar entre 0-7\n\r");
    		column = getNumber();
    	}while(column < 0 || column > 7);
    	// calculate the position
    	posicion = column * N_ROWS + row;
    	data = ((color & 0x1FF) << 23)| (posicion & 0x7F);
    	PANTALLA_mWriteToFIFO(screen_addr, 0, data);
    	break;
    case 2:
    	print("-- Apartado 2 --\n\r");
    	break;
    case 3:
    	print("-- Apartado 3 --\n\r");
            break;
    default:
    	print("Opcion no valida\n\r");
    	break;
    }

    print("-- Exiting main() --\r\n");
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
