@ECHO OFF
@REM ###########################################
@REM # Script file to run the flow 
@REM # 
@REM ###########################################
@REM #
@REM # Command line for ngdbuild
@REM #
ngdbuild -p xc3s1000ft256-5 -nt timestamp -bm practica05.bmm "U:/hlocal/temp/SE/practica05/implementation/practica05.ngc" -uc practica05.ucf practica05.ngd 

@REM #
@REM # Command line for map
@REM #
map -o practica05_map.ncd -pr b -ol high -timing -detail practica05.ngd practica05.pcf 

@REM #
@REM # Command line for par
@REM #
par -w -ol high practica05_map.ncd practica05.ncd practica05.pcf 

@REM #
@REM # Command line for post_par_trce
@REM #
trce -e 3 -xml practica05.twx practica05.ncd practica05.pcf 

