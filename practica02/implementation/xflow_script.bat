@ECHO OFF
@REM ###########################################
@REM # Script file to run the flow 
@REM # 
@REM ###########################################
@REM #
@REM # Command line for ngdbuild
@REM #
ngdbuild -p xc3s1000ft256-5 -nt timestamp -bm practica2.bmm "U:/hlocal/temp/p2/implementation/practica2.ngc" -uc practica2.ucf practica2.ngd 

@REM #
@REM # Command line for map
@REM #
map -o practica2_map.ncd -pr b -ol high -timing -detail practica2.ngd practica2.pcf 

@REM #
@REM # Command line for par
@REM #
par -w -ol high practica2_map.ncd practica2.ncd practica2.pcf 

@REM #
@REM # Command line for post_par_trce
@REM #
trce -e 3 -xml practica2.twx practica2.ncd practica2.pcf 

