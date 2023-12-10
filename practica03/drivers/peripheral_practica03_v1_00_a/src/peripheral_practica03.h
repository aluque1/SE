/*****************************************************************************
* Filename:          C:\Users\aluqu\Desktop\uni\SE\practica03/drivers/peripheral_practica03_v1_00_a/src/peripheral_practica03.h
* Version:           1.00.a
* Description:       peripheral_practica03 Driver Header File
* Date:              Sun Dec 10 13:08:50 2023 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef PERIPHERAL_PRACTICA03_H
#define PERIPHERAL_PRACTICA03_H

/***************************** Include Files *******************************/

#include "xbasic_types.h"
#include "xstatus.h"
#include "xil_io.h"

/************************** Constant Definitions ***************************/


/**
 * User Logic Slave Space Offsets
 * -- SLV_REG0 : user logic slave module register 0
 * -- SLV_REG1 : user logic slave module register 1
 * -- SLV_REG2 : user logic slave module register 2
 * -- SLV_REG3 : user logic slave module register 3
 */
#define PERIPHERAL_PRACTICA03_USER_SLV_SPACE_OFFSET (0x00000000)
#define PERIPHERAL_PRACTICA03_SLV_REG0_OFFSET (PERIPHERAL_PRACTICA03_USER_SLV_SPACE_OFFSET + 0x00000000)
#define PERIPHERAL_PRACTICA03_SLV_REG1_OFFSET (PERIPHERAL_PRACTICA03_USER_SLV_SPACE_OFFSET + 0x00000004)
#define PERIPHERAL_PRACTICA03_SLV_REG2_OFFSET (PERIPHERAL_PRACTICA03_USER_SLV_SPACE_OFFSET + 0x00000008)
#define PERIPHERAL_PRACTICA03_SLV_REG3_OFFSET (PERIPHERAL_PRACTICA03_USER_SLV_SPACE_OFFSET + 0x0000000C)

/**************************** Type Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *******************/

/**
 *
 * Write a value to a PERIPHERAL_PRACTICA03 register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the PERIPHERAL_PRACTICA03 device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void PERIPHERAL_PRACTICA03_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
 *
 */
#define PERIPHERAL_PRACTICA03_mWriteReg(BaseAddress, RegOffset, Data) \
 	Xil_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/**
 *
 * Read a value from a PERIPHERAL_PRACTICA03 register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the PERIPHERAL_PRACTICA03 device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	Xuint32 PERIPHERAL_PRACTICA03_mReadReg(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define PERIPHERAL_PRACTICA03_mReadReg(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (RegOffset))


/**
 *
 * Write/Read 32 bit value to/from PERIPHERAL_PRACTICA03 user logic slave registers.
 *
 * @param   BaseAddress is the base address of the PERIPHERAL_PRACTICA03 device.
 * @param   RegOffset is the offset from the slave register to write to or read from.
 * @param   Value is the data written to the register.
 *
 * @return  Data is the data from the user logic slave register.
 *
 * @note
 * C-style signature:
 * 	void PERIPHERAL_PRACTICA03_mWriteSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Value)
 * 	Xuint32 PERIPHERAL_PRACTICA03_mReadSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define PERIPHERAL_PRACTICA03_mWriteSlaveReg0(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PERIPHERAL_PRACTICA03_SLV_REG0_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PERIPHERAL_PRACTICA03_mWriteSlaveReg1(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PERIPHERAL_PRACTICA03_SLV_REG1_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PERIPHERAL_PRACTICA03_mWriteSlaveReg2(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PERIPHERAL_PRACTICA03_SLV_REG2_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PERIPHERAL_PRACTICA03_mWriteSlaveReg3(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PERIPHERAL_PRACTICA03_SLV_REG3_OFFSET) + (RegOffset), (Xuint32)(Value))

#define PERIPHERAL_PRACTICA03_mReadSlaveReg0(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PERIPHERAL_PRACTICA03_SLV_REG0_OFFSET) + (RegOffset))
#define PERIPHERAL_PRACTICA03_mReadSlaveReg1(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PERIPHERAL_PRACTICA03_SLV_REG1_OFFSET) + (RegOffset))
#define PERIPHERAL_PRACTICA03_mReadSlaveReg2(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PERIPHERAL_PRACTICA03_SLV_REG2_OFFSET) + (RegOffset))
#define PERIPHERAL_PRACTICA03_mReadSlaveReg3(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PERIPHERAL_PRACTICA03_SLV_REG3_OFFSET) + (RegOffset))

/************************** Function Prototypes ****************************/


/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the PERIPHERAL_PRACTICA03 instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus PERIPHERAL_PRACTICA03_SelfTest(void * baseaddr_p);

#endif /** PERIPHERAL_PRACTICA03_H */
