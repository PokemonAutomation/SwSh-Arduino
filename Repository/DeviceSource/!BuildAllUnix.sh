#!/usr/bin/env bash

# change directory to library location
cd "$(dirname "$0")"

# define the MCU, which is the board type
MCU=$1

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

# if the boards were given by integer, we can update them here
if [ "$MCU" == "1" ]; then MCU="at90usb1286"; fi
if [ "$MCU" == "2" ]; then MCU="atmega16u2"; fi
if [ "$MCU" == "3" ]; then MCU="atmega32u4"; fi

# say what we're building for convenience
echo "Ready to build for board: $MCU"
echo ""

# and send off to build
bash Scripts/BuildAllUnix.sh "$MCU" 1> /dev/null

# let them know we finished
echo -e "\033[1mFinished building hex files for board: $MCU \033[0m"
echo "Please make sure the hex files were properly built or updated."
echo "You can now close this window if you wish."
echo ""
# really done
