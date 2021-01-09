@echo off

set MCU=%1
set program=%2

cd /D "%~dp0"
cd "../DeviceSource"


:: Check MCU Compatibility
if exist "obj\*.o" (
    echo Existing build found. Checking MCU compatibility.
    if not exist obj\build-%MCU% (
        echo Incompatible MCU, cleaning...
        @call !Cleanup.cmd >NUL 2>&1
    ) else (
        echo Existing build is compatible.
    )
) else (
    echo No build found, continuing...
)
copy NUL obj\build-%MCU% > NUL


del "%program%.hex"
del "../%program%.hex"


:: Just in case the PATH is messed up, but is installed in the usual place.
set PATH=%PATH%C:\WinAVR-20100110\bin;
set PATH=%PATH%C:\WinAVR-20100110\utils\bin;


echo Checking make command...
echo.
make -v
echo.
echo.
if %errorlevel% NEQ 0 (
    echo make not found. Please install WinAVR.
    echo.
    pause
    exit
)

make MCU="%MCU%" TARGET="%program%"

if not exist "%program%.hex" (
    echo.
    echo Build failed. Please scroll up to see the error.
    echo.
    pause
)

del "%program%.map"
del "%program%.eep"
del "%program%.bin"
del "%program%.lss"
del "%program%.sym"
del "%program%.tmp"

mv "%program%.hex" "../%program%-%MCU%.hex"

::pause