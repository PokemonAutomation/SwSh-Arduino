#!/usr/bin/env bash
# NOTE: this script is a helper script that *should not be called directly*
# please use the scripts provided in the root of this directory

# get the MCU from the first argument
# define the MCU 
MCU=$1

if [ -z "$MCU" ]; then
      read -p 'No MCU Type given, please enter: ' MCU
fi

# get the program from the second argument
program=$2

if [ -z "$program" ]; then
      read -p 'No program given, please enter: ' MCU
fi

# delete the existing hex program if it exists
if [ -f "$program.hex" ]; then
    rm $program.hex
fi

# then call make
make MCU="$MCU" TARGET="$program"

# then we can clean up the map, eep, bin, lss, sym, tmp
rm $program.map > /dev/null 2>&1
rm $program.eep > /dev/null 2>&1
rm $program.bin > /dev/null 2>&1
rm $program.lss > /dev/null 2>&1
rm $program.sym > /dev/null 2>&1
rm $program.elf > /dev/null 2>&1
