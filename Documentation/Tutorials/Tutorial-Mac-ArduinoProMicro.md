# Tutorial - Mac - Arduino Uno R3 and Pro Micro

This section will walk you through the entire process of setting up your Arduino or Pro Micro on a Mac computer.

At this time, the HexGenerator program on Windows is not yet available for Mac or Linux.

## Step 1: Acquire the Hardware

Follow the hardware guide for the "Basic Hardware" section:
- [Pro Micro](Hardware-ProMicro.md)
- [Arduino Uno R3](Hardware-ArduinoUnoR3.md)

## Step 2: Install ???

## Step 3: Download the Arduino Programs

Download the latest version of our Arduino programs from the [main page](https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts).

(The link should look like something like `PASwShScripts-20210206.zip`)

If you get a virus or malware warning, ignore it. These are known false positives. If you don't trust us, the source code is in this repo.

Once you have downloaded the package, unzip to somewhere you can access later.

## Step 4: Configure the program.

This step isn't needed for the TurboA example here, but is for nearly every other program.

1. Navigate into the `DeviceSource` folder.
2. Open `TurboA` with a text editor.

Normally you will see a bunch of options that can configured. But TurboA has nothing.

3. After you have made your changes, save the file.

See the documentation for the respective program for a description of all the options.

## Step 5: Generate a .hex file and flash to the Pro Micro

1. Open Terminal
2. Type `bash ` (with a trailing space!) Do not hit enter after entering this.
3. Drag from finder the "00-FlashUnix.sh" script into the Terminal Window.
4. Press enter.

Once you run the script, it will prompt you for:
- The board type. Enter `ArduinoUnoR` `ProMicro` depending on your board.
- Which program to compile and load. For this tutorial, enter `TurboA`.

It will automatically build the program and flash it to your device.

**[Insert screenshot]**

## Step 6: Setup and run the program!

1. On your Switch, enter the game and navigate to somewhere you want to mash A in front of (such as the digging duo).

<img src="images/digging-duo.jpg" height="400">

2. Navigate to the grip menu without closing the game. This disconnects all controllers from the Switch so that the Pro Micro can take over.

<img src="images/grip-menu.jpg" height="400">

3. Plug the Pro Micro into your Switch (or the dock that's attached to it).

The program should now begin running. It will flash its light for a few seconds, then it will connect to the Switch and navigate its way back into the game. After a brief pause, it will start mashing A.

**Usage Notes:**

- To stop the program, simply unplug the Pro Micro at any time.
- Do not change video output or mess with the HDMI. These can cause the program to Switch to freeze for multiple seconds and break the program. If you want turn off the TV, do it *before* you start the program.

## Other Programs

You now know how to run TurboA - the most basic of the programs. You can choose any of the other programs and repeat steps 4-6.

It is important to read the manual for a program before you use it. Each program has a different set of instructions and startup conditions.
You can find the manual for a program by clicking on the "Online Documentation" link.

# Serial Programs

(coming soon)





