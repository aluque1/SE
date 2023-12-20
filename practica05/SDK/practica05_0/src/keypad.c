/*****************************************************************************
 * Filename:          C:\Users\aluqu\Desktop\uni\SE\practica05/drivers/keypad_v1_00_a/src/keypad.c
 * Version:           1.00.a
 * Description:       keypad Driver Source File
 * Date:              Sun Dec 17 18:10:30 2023 (by Create and Import Peripheral Wizard)
 *****************************************************************************/

/***************************** Include Files *******************************/

#include "keypad.h"
#include "xparameters.h"

/************************** Function Definitions ***************************/

void do_keypad()
{
    Xuint32 Reg32Value, TeclaOld;
    print(" Pulse una tecla cualquiera \n\r");
    Reg32Value = KEYPAD_mReadReg(XPAR_KEYPAD_0_BASEADDR, 0);
    xil_printf("   Se ha leido %d del registro 0 del teclado \n\r", Reg32Value);
    KEYPAD_mWriteReg(XPAR_KEYPAD_0_BASEADDR, 0, 0);
    TeclaOld = Reg32Value;
    while (1)
    {
        if (Reg32Value != TeclaOld)
            xil_printf("    Se ha leido %d del registro 0 del teclado \n\r", Reg32Value);
        TeclaOld = Reg32Value;
        Reg32Value = KEYPAD_mReadReg(XPAR_KEYPAD_0_BASEADDR, 0) >> 28;
        KEYPAD_mWriteReg(XPAR_KEYPAD_0_BASEADDR, 0, 0); // Se escribe un 0 en el registro del teclado para borrar la ultima tecla leida
    }
}