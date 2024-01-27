/*****************************************************************************
* Filename:          C:\Users\aluqu\Desktop\uni\SE\proyecto/drivers/kbd_ps2_v1_00_a/src/kbd_ps2.c
* Version:           1.00.a
* Description:       kbd_ps2 Driver Source File
* Date:              Wed Jan 24 19:39:30 2024 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "kbd_ps2.h"
#include "xparameters.h"

/************************** Function Definitions ***************************/

void do_ps2(){
    Xuint32 Reg32Value, TeclaHome;
    print(" Pulse una tecla cualquiera \n\r");
    Reg32Value = KBD_PS2_mReadReg(XPAR_KBD_PS2_0_BASEADDR, 0);
    xil_printf("   Se ha leido %d del registro 0 del teclado \n\r", Reg32Value);
    KBD_PS2_mWriteReg(XPAR_KBD_PS2_0_BASEADDR, 0, 0xF0);
    TeclaHome = Reg32Value;
    while (1)
    {
        if (Reg32Value != TeclaHome)
            xil_printf("    Se ha leido %d del registro 0 del teclado \n\r", Reg32Value);
        TeclaHome = Reg32Value;
        Reg32Value = KBD_PS2_mReadReg(XPAR_KBD_PS2_0_BASEADDR, 0);
        KBD_PS2_mWriteReg(XPAR_KBD_PS2_0_BASEADDR, 0, 0xF0); // Escribimos rango fuera de rango para que no se repita se pone como 0 no se porque
    }
}

void record_passPS2(Xuint32 *pass)
{
    int i;
    Xuint32 Reg32Value, TeclaHome;
    TeclaHome = 0x01;
    KBD_PS2_mWriteReg(XPAR_KBD_PS2_0_BASEADDR, 0, TeclaHome);
    print(" Introduzca el password: (longitud 8)\n\r");
    for (i = 0; i < 8; ++i)
    {
        Reg32Value = KBD_PS2_mReadReg(XPAR_KBD_PS2_0_BASEADDR, 0);
        if (Reg32Value != TeclaHome){
            xil_printf("----> Se ha leido %d\n\r", Reg32Value);
            pass[i] = Reg32Value;
        }
        KBD_PS2_mWriteReg(XPAR_KBD_PS2_0_BASEADDR, 0, TeclaHome); // Escribimos rango fuera de rango para que no se repita se pone como 0 no se porque
    }
}