##############################################################################
## Filename:          C:\Users\aluqu\Desktop\uni\SE\practica05/drivers/keypad_v1_00_a/data/keypad_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Sun Dec 17 18:10:30 2023 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "keypad" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
