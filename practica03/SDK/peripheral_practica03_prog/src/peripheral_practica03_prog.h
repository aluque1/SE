/*
 * peripheral_practica03_prog.c
 *
 *  Created on: 12 Dec 2023
 *      Author: aluqu
 */

/***************************** Include Files *******************************/
#include "xbasic_types.h"
#include "xstatus.h"
#include "xio.h"
/************************** Constant Definitions ***************************/
/**
* User Logic Slave Space Offsets
* -- SLV_REG0 : user logic slave module register 0
* -- SLV_REG1 : user logic slave module register 1
* -- SLV_REG2 : user logic slave module register 2
* -- SLV_REG3 : user logic slave module register 3
*/
#define MY_PERIPHERAL_USER_SLV_SPACE_OFFSET (0x00000000)
#define MY_PERIPHERAL_SLV_REG0_OFFSET (MY_PERIPHERAL_USER_SLV_SPACE_OFFSET + 0x00000000)
#define MY_PERIPHERAL_SLV_REG1_OFFSET (MY_PERIPHERAL_USER_SLV_SPACE_OFFSET + 0x00000004)
#define MY_PERIPHERAL_SLV_REG2_OFFSET (MY_PERIPHERAL_USER_SLV_SPACE_OFFSET + 0x00000008)
#define MY_PERIPHERAL_SLV_REG3_OFFSET (MY_PERIPHERAL_USER_SLV_SPACE_OFFSET + 0x0000000C)

/***************** Macros (Inline Functions) Definitions *******************/
/** Escritura en un registro (32 bits)
*
* @param BaseAddress is the base address of the MY_PERIPHERAL device.
* @param RegOffset is the register offset from the base to write to.
* @param Data is the data written to the register.
*
* @return None.
**
*/
#define MY_PERIPHERAL_mWriteReg(BaseAddress, RegOffset, Data) \
		XIo_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/** Lectura en un registro del perif�rico (32 bits)
*
* @param BaseAddress is the base address of the MY_PERIPHERAL device.
* @param RegOffset is the register offset from the base to write to.
*
* @return Data is the data from the register.
*
*/
#define MY_PERIPHERAL_mReadReg(BaseAddress, RegOffset) \
		XIo_Out32((BaseAddress) + (RegOffset))

/** Lecturas y escrituras de 32 bits en los registros internos de my:peripheral
*
* @param BaseAddress is the base address of the MY_PERIPHERAL device.
* @param RegOffset is the offset from the slave register to write to or read from.
* @param Value is the data written to the register.
* @return Data is the data from the user logic slave register.
** C-style signature:
* void MY_PERIPHERAL_mWriteSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Value)
* Xuint32 MY_PERIPHERAL_mReadSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset)
*/
#define MY_PERIPHERAL_mWriteSlaveReg0(BaseAddress, RegOffset, Value) \
	XIo_Out32((BaseAddress) + (MY_PERIPHERAL_SLV_REG0_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_PERIPHERAL_mReadSlaveReg0(BaseAddress, RegOffset) \
	XIo_In32((BaseAddress) + (MY_PERIPHERAL_SLV_REG0_OFFSET) + (RegOffset))

#define MY_PERIPHERAL_mWriteSlaveReg1(BaseAddress, RegOffset, Value) \
	XIo_Out32((BaseAddress) + (MY_PERIPHERAL_SLV_REG1_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_PERIPHERAL_mReadSlaveReg1(BaseAddress, RegOffset) \
	XIo_In32((BaseAddress) + (MY_PERIPHERAL_SLV_REG1_OFFSET) + (RegOffset))

#define MY_PERIPHERAL_mWriteSlaveReg2(BaseAddress, RegOffset, Value) \
	XIo_Out32((BaseAddress) + (MY_PERIPHERAL_SLV_REG2_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_PERIPHERAL_mReadSlaveReg2(BaseAddress, RegOffset) \
	XIo_In32((BaseAddress) + (MY_PERIPHERAL_SLV_REG2_OFFSET) + (RegOffset))

#define MY_PERIPHERAL_mWriteSlaveReg3(BaseAddress, RegOffset, Value) \
	XIo_Out32((BaseAddress) + (MY_PERIPHERAL_SLV_REG3_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_PERIPHERAL_mReadSlaveReg3(BaseAddress, RegOffset) \
	XIo_In32((BaseAddress) + (MY_PERIPHERAL_SLV_REG3_OFFSET) + (RegOffset))

