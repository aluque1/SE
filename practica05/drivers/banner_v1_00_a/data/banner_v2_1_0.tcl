##############################################################################
## Filename:          C:\Users\aluqu\Desktop\uni\SE\practica05/drivers/banner_v1_00_a/data/banner_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Sat Dec 16 19:06:47 2023 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "banner" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
