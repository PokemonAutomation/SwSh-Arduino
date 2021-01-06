#!/usr/bin/env bash

# change directory to library location
cd "$(dirname "$0")"

# Parse Command line arguments for MCU, Program and Device Path
MCU=$1
program=$2
device_path=$3

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


if [ -z "$program" ]; then
    echo ""
    read -p "Please enter the name of the program (without .hex): " program
    echo ""
fi

if [[ -z $device_path ]]; then
    echo ""
    read -p "Would you like to attempt auto detecting your device? [y/n]: " autodetect_device
    autodetect_device="${autodetect_device:-y}"

    if [[ $autodetect_device == "n" ]]; then
        echo ""
        read -p "Please enter the path to your devicd (ex. /dev/ttyACM0): " device_path
        echo ""
    elif [[ $autodetect_device != "y" ]]; then
        echo ""
        echo "Invalid input, defaulting to autodetection"
        echo ""
        autodetect_device="y"
    fi
fi

if [ -f "$program.hex" ]; then
    HEXFILE="$program.hex"
    if [[ $autodetect_device == "y" ]]; then
        while true; do
            echo "Waiting for device to connect..."
            found_device_path="$(ls /dev/tty* | grep -i 'acm\|usb')"
            if [[ ! -z "$found_device_path" ]]; then
                echo "================================="
                echo "Device connected at [${found_device_path}]"
                echo "Attempting to flash $program.hex to $MCU now"
                echo "================================="
                avrdude -p "${MCU}" -P "${found_device_path}" -c avr109 -U flash:w:${HEXFILE}
                break; 
            fi
            sleep 1;
        done
    else
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
    fi
elif [ -f "$program.c" ]; then
    echo "It looks like there is no hex file for $program.c"
    DOBUILD="n"
    read -p "Would you like to build it now and then flash it? [y/n]: " DOBUILD

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
    if [[ $autodetect_device == "y" ]]; then
        while true; do
            echo "Waiting for device to connect..."
            found_device_path="$(ls /dev/tty* | grep -i 'acm\|usb')"
            if [[ ! -z "$found_device_path" ]]; then
                echo "================================="
                echo "Device connected at [${found_device_path}]"
                echo "Attempting to flash $program.hex to $MCU now"
                echo "================================="
                avrdude -p "${MCU}" -P "${found_device_path}" -c avr109 -U flash:w:${HEXFILE}
                break; 
            fi
            sleep 1;
        done
    else
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
    fi
    else
        exit
    fi
else
    echo "No such program exists to flash. Exiting."
    exit
fi

echo -e "\033[1mFinished flashing $program.hex to $MCU! \033[0m"
echo -e ""


