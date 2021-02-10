# Tutorial - Windows - Pro Micro

This section will walk you through the entire process of setting up your Pro Micro on a Windows computer.

The Pro Micro board is just as capable as the Teensy 2.0, but at a much lower cost. The catch is that the setup is more complicated and annoying.

## Step 1: Acquire the Hardware

Follow the [hardware guide](Hardware-ProMicro.md) for the "Basic Hardware" section.

## Step 2: Install WinAVR

Download and install [WinAVR](https://sourceforge.net/projects/winavr/files/).

It is strongly recommended to install it in the default directory (`C:/WinAVR-20100110`).

## Step 3: Download QMK Toolbox

Download [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases).

You want the file `qmk_toolbox.exe`.

## Step 4: Download the Arduino Programs

Download the latest version of our Arduino programs from the [main page](https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts).

(The link should look like something like `PASwShScripts-20210206.zip`)

If you get a virus or malware warning, ignore it. These are known false positives. If you don't trust us, the source code is in this repo.

Once you have downloaded the package, unzip to somewhere you can access later.

## Step 5: Generate a .hex file.

1. Open the package from previous section and double-click on `HexGenerator-Windows.cmd` to run it.
2. In the "Board Type" drop-down, change it to "Pro Micro" depending on which board you have.
3. In the program list, click on "Turbo A".

<img src="images/tutorial-windows-pro-micro-0.png" height="400">

4. Click on "Save and generate .hex file!".

After a while, you should get a confirmation box saying it was successful. You should now see a file `TurboA-ProMicro.hex` in the folder of the programs.

<img src="images/tutorial-windows-pro-micro-1.png" height="400">

## Step 6: Flash the .hex into the Pro Micro.

1. Run the QMK Toolbox program that you downloaded earlier.
2. Open the .hex you generated in the previous step.
3. Change the MCU to `atmega32u4`.
4. Check the "Auto-Flash" box.

<img src="images/tutorial-windows-pro-micro-2.png" height="600">

5. Plug the Pro Micro into your computer. Wait for the drivers to install.
6. Short the GND and RST holes. (use tweezers)

<img src="images/tutorial-windows-pro-micro-3.jpg" height="600">

The QMK program will now flash the program to the Pro Micro and show a bunch of logging.

<img src="images/tutorial-windows-pro-micro-4.png" height="600">

7. Unplug the Pro Micro from your computer.

## Step 7: Setup and run the program!

1. On your Switch, enter the game and navigate to somewhere you want to mash A in front of (such as the digging duo).

<img src="images/digging-duo.jpg" height="400">

2. Navigate to the grip menu without closing the game. This disconnects all controllers from the Switch so that the Pro Micro can take over.

<img src="images/grip-menu.jpg" height="400">

3. Plug the Pro Micro into your Switch (or the dock that's attached to it).

The program should now begin running. It will flash its light for a few seconds, then it will connect to the Switch and navigate its way back into the game. After a brief pause, it will start mashing A. To stop the program, simply unplug the Pro Micro at any time.

## Other Programs

You now know how to run TurboA - the most basic of the programs. You can choose any of the other programs and repeat steps 5-7.

It is important to read the manual for a program before you use it. Each program has a different set of instructions and startup conditions.
You can find the manual for a program by clicking on the "Online Documentation" link.

# Serial Programs

Now that you know how to use the native programs for your Teensy, you are ready to move onto the serial programs!

***Be aware that you will need a regular Switch (not Switch Lite) for proper video capture and video feedback. The Switch Lite does not output video.***

## Step 1: Acquire the Hardware

Follow the [hardware guide](Hardware-ProMicro.md) all the way to the end. (all 3 sections)

Strictly speaking, the final section on video capture isn't needed if you don't run any programs that require video feedback.
But the serial programs are much easier to use if you have video capture. If you're this far into the tutorial, you're probably going to have video capture anyway.

## Step 2: Setup video capture.

(coming soon)

## Step 3: Download the SerialPrograms package.

(coming soon)

## Step 4: Flash PABotBase into your Pro Micro.

(coming soon)

## Step 5: Setup the serial port and video capture device.

(coming soon)

## Step 6: Play around with the keyboard controls.

(coming soon)

## Step 7: Run a program.

(coming soon)

## Notes

Since the SerialPrograms use a prebuilt PABotBase .hex binary, you don't actually need to install WinAVR to use it. So if you intend to use only the serial programs, you can skip installing the toolchain.

Many of the programs in SerialPrograms are identical to the native ones that don't require serial. However, you don't need to start them in the grip menu.
The purpose of the grip menu is to disconnect your manual controller so that the device can take over as the primary controller. But if you're using the keyboard to control your Switch, the device is likely already the primary controller. So you can actually start the program in the Switch Home menu or even inside the game.



