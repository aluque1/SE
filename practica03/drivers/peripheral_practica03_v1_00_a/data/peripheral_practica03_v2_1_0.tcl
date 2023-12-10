##############################################################################
## Filename:          C:\Users\aluqu\Desktop\uni\SE\practica03/drivers/peripheral_practica03_v1_00_a/data/peripheral_practica03_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Sun Dec 10 13:08:50 2023 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "peripheral_practica03" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
