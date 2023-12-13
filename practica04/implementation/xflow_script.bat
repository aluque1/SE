@ECHO OFF
@REM ###########################################
@REM # Script file to run the flow 
@REM # 
@REM ###########################################
@REM #
@REM # Command line for ngdbuild
@REM #
ngdbuild -p xc3s1000ft256-5 -nt timestamp -bm practica04.bmm "U:/hlocal/temp/SE/practica04/implementation/practica04.ngc" -uc practica04.ucf practica04.ngd 

@REM #
@REM # Command line for map
@REM #
map -o practica04_map.ncd -pr b -ol high -timing -detail practica04.ngd practica04.pcf 

@REM #
@REM # Command line for par
@REM #
par -w -ol high practica04_map.ncd practica04.ncd practica04.pcf 

@REM #
@REM # Command line for post_par_trce
@REM #
trce -e 3 -xml practica04.twx practica04.ncd practica04.pcf 

