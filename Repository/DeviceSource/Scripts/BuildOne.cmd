::echo off

set MCU=%1
set program=%2

if [%MCU%] == [] (
    set /p MCU="MCU Type: "
)
if [%program%] == [] (
    set /p program="Program Name: "
)

del "%program%.hex"
make MCU="%MCU%" TARGET="%program%"

::if %errorlevel% NEQ 0 (
::   echo Build Failed. Error %errorlevel%
::   del "%program%.hex"
::   pause
::)

del "%program%.map"
del "%program%.eep"
del "%program%.bin"
del "%program%.lss"
del "%program%.sym"
del "%program%.tmp"
