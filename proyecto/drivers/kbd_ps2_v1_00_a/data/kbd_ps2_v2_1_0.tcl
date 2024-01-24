##############################################################################
## Filename:          C:\Users\aluqu\Desktop\uni\SE\proyecto/drivers/kbd_ps2_v1_00_a/data/kbd_ps2_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Wed Jan 24 19:39:30 2024 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "kbd_ps2" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
