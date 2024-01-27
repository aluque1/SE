#include "xparameters.h"
#include "stdio.h"
#include "xutil.h"

#include "xgpio.h"

//===============================================================================
// PR�CTICA : Zumbador
//===============================================================================

void ZUMBADOR_init(XGpio *Gpio_zumbador, Xuint32 zumbador)
{
	Xuint32 status;
	// Configuraci�n de la GPIO para el zumbador de la placa de expansi�n
	status = XGpio_Initialize(Gpio_zumbador, zumbador);

	if (status != XST_SUCCESS)
		xil_printf("Error en la inicializacion\r\n");
	else
	{
		XGpio_SetDataDirection(Gpio_zumbador, 1, 0x00);
		xil_printf("Inicializado con exito\r\n");
	}
}

void ZUMBADOR_suena(XGpio *Gpio_zumbador)
{
	XGpio_DiscreteWrite(Gpio_zumbador, 1, (u8)0);
}

void ZUMBADOR_calla(XGpio *Gpio_zumbador)
{
	XGpio_DiscreteWrite(Gpio_zumbador, 1, (u8)1);
}

void ZUMBADOR_oscila()
{

	xil_printf("ALARMA ACTIVADA\r\n");

	unsigned int i;

	// La instancia del zumbador usada para la comunicaci�n con el propio zumbador
	XGpio Gpio_zumbador;

	// Los Device IDs del zumbador para la comunicaci�n con el propio zumbador
	Xuint32 zumbador = XPAR_BUZZER_0_DEVICE_ID;

	ZUMBADOR_init(&Gpio_zumbador, zumbador);

	while (1)
	{
		ZUMBADOR_suena(&Gpio_zumbador);
		xil_printf("Suena\r\n");
		for (i = 0; i < 0x00070000; i++)
		{
		} // retardo

		ZUMBADOR_calla(&Gpio_zumbador);
		xil_printf("Calla\r\n");
		for (i = 0; i < 0x00070000; i++)
		{
		} // retardo
	}
}
