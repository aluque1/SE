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

void record_passKP(Xuint32 *pass)
{
    Xuint32 Reg32Value, TeclaOld;
    short i = 0;
    print("Enter the password(4 digits)\n\r");
    Reg32Value = KEYPAD_mReadReg(XPAR_KEYPAD_0_BASEADDR, 0);
    KEYPAD_mWriteReg(XPAR_KEYPAD_0_BASEADDR, 0, 0);
    TeclaOld = Reg32Value;
    while (i < 4)
    {
        if (Reg32Value != TeclaOld && Reg32Value >> 28 != 0)
        {
            xil_printf("----> The number read was: %d\n\r", Reg32Value >> 28);
            pass[i] = Reg32Value >> 28;
            TeclaOld = Reg32Value;
            ++i;
        }
        Reg32Value = KEYPAD_mReadReg(XPAR_KEYPAD_0_BASEADDR, 0);
        KEYPAD_mWriteReg(XPAR_KEYPAD_0_BASEADDR, 0, 0);
    }
    print("The password is:");
    for (i = 0; i < 4; ++i)
        xil_printf("%d", pass[i]);
    print("\n\r");
}
