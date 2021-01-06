#!/usr/bin/env bash

# change directory to library location
cd "$(dirname "$0")" || exit

# Parse Command line arguments for MCU, Program and Device Path
MCU=$1
PROGRAM=$2
DEVICE_PATH=$3

SUDO=""
BUILD_HEX=""
PLATFORM=""
HEXFILE=""
PROGRAM_COMMAND="program_avrdude ${MCU} ${HEXFILE}" # Default to using avrdude

MCUBOARDS=("1" "2" "3" "at90usb1286" "atmega16u2" "atmega32u4")

if [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="mac"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    PLATFORM="linux"
else
    boxed_msg "${RED}${OSTYPE} is not a recognized platform. Please run only on Mac or Linux${RESET}"
    exit 1
fi

function run() {

    configure

    if [[ $BUILD_HEX == "y" ]]; then
        build_hex
    fi

    boxed_msg "Flashing ${PROGRAM}.hex ..."
    $PROGRAM_COMMAND

    boxed_msg "Finished flashing ${HEXFILE} to ${MCU}!"
}

function configure() {
    boxed_msg "Configuration"
    
    if [[ "$EUID" -ne 0 ]]; then
        SUDO="sudo"
        note "Using sudo for flashing device, you may need to provide your password!"
    fi
    
    if [ -z "${MCU}" ]; then
        echo -e "${YELLOW}Please select your board type by either number or name:${RESET}"
        echo -e "${YELLOW}1 - at90usb1286  (for Teensy 2.0++)${RESET}"
        echo -e "${YELLOW}2 - atmega16u2   (for Arduino UNO R3)${RESET}"
        echo -e "${YELLOW}3 - atmega32u4   (for Arduino Micro, and Teensy 2.0)${RESET}"
        
        question "Enter your board type" "MCU"

        while true ; do
            found=0
            for i in "${MCUBOARDS[@]}"; do
                if [[ "${MCU}" = "$i" ]]; then
                    found=1
                fi
            done
            if [[ $found ]]; then
                break
            else
                question "Invalid selection, please re-enter board selection" MCU
            fi
        done
        # change the board type to the correct name if numbers were given
        if [ "${MCU}" == "1" ]; then MCU="at90usb1286"; fi
        if [ "${MCU}" == "2" ]; then MCU="atmega16u2"; fi
        if [ "${MCU}" == "3" ]; then MCU="atmega32u4"; fi
    fi

    if [ -z "${PROGRAM}" ]; then
        question "Please enter the name of the program (without .hex)" "PROGRAM"
        HEXFILE="${PROGRAM}.hex"
    fi
    
    if [[ ! -f "${HEXFILE}" ]] && [[ -f "${PROGRAM}.c" ]]; then
        question "${HEXFILE} for ${PROGRAM} not found, build it now? ${WHITE}[y/n]${RESET}" "DOBUILD"
        DOBUILD="${DOBUILD:-n}"
        if [ "$DOBUILD" == "y" ]; then
            BUILD_HEX="y"
        else
            logmsg "Nothing to flash, exiting.."
            exit
        fi
    fi

    # Logic below to determine if we need to us dfu-programmer or not
    if [[ $PLATFORM == "mac" ]] && [[ ${MCU} == "atmega16u2" ]]; then
        which dfu-programmer >/dev/null 2>&1
        if [[ $? -eq 0 ]]; then
            question "Mac platform detected, UNO R3 configured, should I use dfu-programmer ${WHITE}[y/n]${RESET}" "use_dfu"
            use_dfu="${use_dfu:-n}"
            if [[ "${use_dfu}" == "y" ]]; then
                PROGRAM_COMMAND="program_dfu ${MCU} ${HEXFILE}"
            fi
        else
            logmsg "dfu-programmer not installed, defaulting to avrdude"
        fi
    fi
}

function build_hex {
        boxed_msg "Build ${PROGRAM}.c"

        note "Cleaning Build Environment"
        ./00-CleanupUnix.sh >/dev/null

        note "Running Build Script"
        sh Scripts/BuildOneUnix.sh "${MCU}" "${PROGRAM}" > /dev/null
        retVal=$?
        if [ $retVal -ne 0 ]; then
            boxed_msg "${RED}ERROR - CRITICAL: An error occured while building.\nPlease check logs and perhaps run the cleanup script before trying again.${RESET}"
            exit 1
        else 
            note "${PROGRAM}.hex successfully built!"
        fi
}

function detect_device() {
    local -r delay='0.75'
    local spinstr='\|/-'
    local temp
    while true; do
        temp="${spinstr#?}"
        printf "${YELLOW}Waiting for device... [%c]  ${RESET}" "${spinstr}"
        spinstr=${temp}${spinstr%"${temp}"}
        # shellcheck disable=SC2010
        found_device_path="$(ls /dev/tty* | grep -i 'acm\|usb')"
        if [[ -n "$found_device_path" ]]; then
            DEVICE_PATH="${found_device_path}"
            break
        fi
        sleep "${delay}"
        printf "%0.s\b" {1..28}
    done
    printf "    \b\b\b\b\n"
    boxed_msg "Device connected at [${found_device_path}]" "short"
}

function program_dfu {
    # start with clearing the board
    ${SUDO} dfu-programmer "${MCU}" erase || true
    # then flash the hex to the board
    ${SUDO} dfu-programmer "${MCU}" flash "${HEXFILE}"
    if [[ $? -ne 0 ]]; then
        boxed_msg "${RED}Flash Error: Check the output above for more info.${RESET}"
        exit 1
    fi
    # then reset the board
    ${SUDO} dfu-programmer "${MCU}" reset
    if [[ $? -ne 0 ]]; then
        boxed_msg "${RED}Device Reset Error: Check the output above for more info.${RESET}"
        exit 1
    fi
}

function program_avrdude {
    if [[ -z $DEVICE_PATH ]]; then
        question "Would you like to attempt auto detecting your device? ${WHITE}[y/n]${RESET}" "autodetect_device"
        autodetect_device="${autodetect_device:-y}"
        if [[ $autodetect_device == "n" ]]; then
            question "Please enter the path to your device ${WHITE}(ex. /dev/ttyACM0)${RESET}" "DEVICE_PATH"        
        elif [[ $autodetect_device == "y" ]]; then
            detect_device 
        else
            note "Invalid input, defaulting to autodetection"
            detect_device
        fi
    fi
    
    note "Attempting to flash ${WHITE}${PROGRAM}.hex${RESET} to ${WHITE}${DEVICE_PATH}${RESET} now"
    ${SUDO} avrdude -q -p "${MCU}" -P "${DEVICE_PATH}" -c avr109 -U flash:w:"${HEXFILE}"
}

function boxed_msg() {
    msg=$1
    len=$2
    [[ $len == short ]] && div="\n===============\n" || div="\n=================================\n"
    echo -e "${div}${GREEN}${msg}${RESET}${div}"
}

function question() {
    echo -e "\n${YELLOW}${1}: ${RESET}"
    read -r "$2"
}

function logmsg {
    msg=$1
    echo -e "${LBLUE}${msg}${RESET}"
}

function note() {
    msg=$1
    div='** '
    echo -e "${YELLOW}${div}${msg}${RESET}"
}

## Color Helpers
RED=$'\e[1;31m'
YELLOW=$'\e[1;33m'
GREEN=$'\e[1;32m'
LBLUE=$'\e[1;34m'
WHITE=$'\e[1;37m'
RESET=$'\e[0m'

# LEZZGOOO!
run

