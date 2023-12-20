@ECHO OFF
@REM ###########################################
@REM # Script file to run the flow 
@REM # 
@REM ###########################################
@REM #
@REM # Command line for ngdbuild
@REM #
ngdbuild -p xc3s1000ft256-5 -nt timestamp -bm practica03.bmm "C:/Users/aluqu/Desktop/uni/SE/practica03/implementation/practica03.ngc" -uc practica03.ucf practica03.ngd 

@REM #
@REM # Command line for map
@REM #
map -o practica03_map.ncd -pr b -ol high -timing -detail practica03.ngd practica03.pcf 

@REM #
@REM # Command line for par
@REM #
par -w -ol high practica03_map.ncd practica03.ncd practica03.pcf 

@REM #
@REM # Command line for post_par_trce
@REM #
trce -e 3 -xml practica03.twx practica03.ncd practica03.pcf 

