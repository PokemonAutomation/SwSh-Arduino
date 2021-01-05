#!/usr/bin/env bash

# change directory to library location
cd "$(dirname "$0")"

# define the MCU, which is the board type
MCU=$1

# do a check for the MCU especially if it wasn't specified
if [ -z "$MCU" ]; then
    MCUBOARDS=("1" "2" "3" "at90usb1286" "atmega16u2" "atmega32u4")
    echo "Please select your board type by either number or name:"
    echo "1 - at90usb1286  (for Teensy 2.0++)"
    echo "2 - atmega16u2   (for Arduino UNO R3)"
    echo "3 - atmega32u4   (for Arduino Micro, and Teensy 2.0)"
    
    CONTINUE=false
    read -p "Enter your board type: " MCU

    while true ; do
        for i in "${MCUBOARDS[@]}"; do
            if [[ "$MCU" = "$i" ]]; then
                CONTINUE=true
            fi
        done

        # break if we got continue to be true
        if [ "$CONTINUE" = true ]; then
            break
        fi

        # otherwise, we've got to ask again (and again)
        read -p "Invalid board, try again: " MCU

    done

fi

# change the board type to the correct name if numbers were given
if [ "$MCU" == "1" ]; then MCU="at90usb1286"; fi
if [ "$MCU" == "2" ]; then MCU="atmega16u2"; fi
if [ "$MCU" == "3" ]; then MCU="atmega32u4"; fi

# define the program
program=$2

if [ -z "$program" ]; then
    read -p "Please enter the name of the program (without .hex): " program
fi

device_path=$3

if [ -z "$device_path" ]; then
    read -p "Please enter the path to your devicd (ex. /dev/ttyACM0): " device_path
fi

if [ -f "$program.hex" ]; then
    HEXFILE="$program.hex"
    while true; do  
        device_present=$(ls ${device_path} >/dev/null 2>&1 );  
        if [[ $? -eq 0 ]]; then    
            echo "Flashing $program.hex to $MCU now"
            avrdude -p "${MCU}" -P "${device_path}" -c avr109 -U flash:w:${HEXFILE}
            break; 
        fi; 
        echo "Device not found, retrying in 1 second..."
        sleep 1
    done
elif [ -f "$program.c" ]; then
    echo "It looks like there is no hex file for $program.c"
    DOBUILD="n"
    read -p "Would you like to build it now and then flash it? [y/n]" DOBUILD

    if [ "$DOBUILD" == "y" ]; then
        # build the hex file for that one script
        sh Scripts/BuildOneUnix.sh $MCU $program

        retVal=$?
        if [ $retVal -ne 0 ]; then
            echo "ERROR - CRITICAL: An error occured while building."
            echo "Please check logs and perhaps run the cleanup script before trying again."
            exit 1
        fi
        
        # then flash
        HEXFILE="$program.hex"
        while true; do  
            device_present=$(ls ${device_path} >/dev/null 2>&1 );  
            if [[ $? -eq 0 ]]; then    
                echo "Flashing $program.hex to $MCU now"
                avrdude -p "${MCU}" -P "${device_path}" -c avr109 -U flash:w:${HEXFILE}
                break; 
            fi; 
            echo "Device not found, retrying in 1 second..."
            sleep 1
        done
    else
        exit
    fi
else
    echo "No such program exists to flash. Exiting."
    exit
fi

echo -e "\033[1mFinished flashing $program.hex to $MCU! \033[0m"
echo -e ""


