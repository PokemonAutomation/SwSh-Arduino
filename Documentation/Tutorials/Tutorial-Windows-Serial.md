# Tutorial - Windows - Serial Connection and Video Capture

This the guide for setting up serial programs on Windows. If you are here, your basic hardware setup should be fully working. So now you are ready to move up to the level - serial connectivity and video capture.

Setting up serial connection and video capture is the same regardless of what device you have. Therefore all the device-specific tutorials will merge here.

***Note that Switch Lite cannot output video. Therefore it cannot run any programs that require video capture. If you wish to pursue this level of automation, it might be worth considering investing in a full Switch.***

## Step 1: Acquire the Hardware

Complete the "Serial Hardware" and "Video Hardware" sections for your device.

- [Teensy 2.0 and Teensy++ 2.0](Hardware-Teensy2.md#serial-hardware)
- [Pro Micro](Hardware-ProMicro.md#serial-hardware)
- [Arduino Uno R3](Hardware-ArduinoUnoR3.md#serial-hardware)

## Step 2: Download the SerialPrograms package.

Download the latest version of the serial programs from the [main page](https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts).

(The link should look like something like `PASwShSerialPrograms-yyyymmdd.zip`)

## Step 3: Flash PABotBase into your Device.

The root folder of the SerialPrograms package should have a set of .hex files for each of the different devices.

<img src="images/serial-programs-root.png" height="300">

Flash the appropriate one to your device.

## Step 4: Setup the serial connection.

1. Turn on your Switch.
2. Connect your device (Teensy/Pro Micro/Arduino) to the Switch or its dock.
3. Connect the UART to your computer.

## Step 5: Setup the video capture.

1. Connect an HDMI cable from your Switch dock to your video capture card.
2. Connect your capture card to your computer.

Here is an example of a setup after steps 4 and 5.

<img src="images/serial-setup.jpg" height="600">

## Step 6: Open up SerialPrograms.

1. Run the `SerialPrograms-Windows.cmd` script.
<img src="images/serial-programs-main.png" height="600">

2. Under the "Serial Port" dropdown, select your serial device.
3. Under the "Camera" dropdown, select your video capture device.

If everything worked correctly, it should look like this. Note that you will not hear any sound. (see next section)

<img src="images/serial-programs-setup.png">

**Troubleshooting:**

If nothing shows up for Serial Port or Camera, then there is something wrong with your setup.

Common serial connection errors are:
- Switching the TX and RX connections.
- The serial port is in use by another program.
- The device is not running a compatible program.

Common video capture errors are:
- The capture card is in use by another program.
- The capture card is not receiving enough power over the USB connection.
- There are multiple capture cards connected to the same physical USB port on the computer (by means of a hub). (see [multiple capture cards](#multiple-video-capture-cards-are-finicky))


## Step 7: Setup sound.

As mentioned in the previous section, the program does not support sound playback nor does it need it.
If you want to hear sound on your computer, you need to do it through Windows.

1. Right-click on your sound icon and select "Open sound settings".

<img src="images/serial-programs-sound-0.png" height="200">

2. Click on "Sound Control Panel".

<img src="images/serial-programs-sound-1.png" height="400">

3. Click on the "Recording" tab and find your capture card. Then go into its properties.

<img src="images/serial-programs-sound-2.png" height="400">

4. Click on the "Listen" tab and check the box for "Listen to this device".

<img src="images/serial-programs-sound-3.png" height="400">

5. Press OK to confirm changes and close all the windows.

You should now be able to hear the sound of your Switch from your computer. It not then there can be many issues causing it. If you need help resolving this, please ask in our Discord server.

## Step 6: Play around with the keyboard controls.

If you make it here, then both your serial connection and your video is working. Congrats! Now it's time to play with the program.

The default program is the Virtual Console. It simply displays the video from your Switch. If you click on the video, it will also activate keyboard controls so you can send button presses to the Switch. This allows you to play your Switch on your computer. Subsequently, this also allows full remote access to your Switches.

To view the keyboard/controller mapping, click on "Keyboard Layout" in the bottom left section of the program.

<img src="images/serial-programs-mapping.png" height="400">

The joystick mappings should be fairly standard for FPS and 3D adventure games. The remaining buttons are somewhat arbitrary and not necessarily intuitive.
As of this writing, there is no support for changing the key mapping.

The playability of this will depend drastically on the quality of your capture card. Some capture cards have very low video latency. Other cards may be to slow to play on the computer in real time. Regardless, even if it is slow, you can use the program for remote access to setup and run programs while you are away.

**Note:** Since `Shift` is mapped to the B button, you will need to disable Sticky Keys in the system. Alternatively, you can press `CTRL` for B. Some buttons have multiple keyboard keys that can be used to invoke it, but they are undocumented at this time.

## Step 7: Run a program.

Now that you know how to use the Virtual Console, you can try running some programs on the left panel. The first thing that you will notice is that every program is a virtual console!

Most of the current programs are identical to the native ones as they were directly ported from device code to computer. Only this time, you can configure and run them with a few clicks. There is no more need to flash the device every time you change programs!

You will notice that the programs are color-coded:
- **Black:** Not a real program.
- **Blue:** Program does not use video feedback. It can run on all devices (including Arduino Uno R3).
- **Red:** Program does not use video feedback. It cannot run on the Arduino Uno R3.
- **Green:** Program uses video feedback and requires video capture. It can run on all devices (including Arduino Uno R3).
- **Purple:** Program uses video feedback and requires video capture. It cannot run on the Arduino Uno R3.

## Notes

### WinAVR is not necessary.

Since the SerialPrograms use a prebuilt PABotBase .hex binary, you don't actually need to install WinAVR to use it. So if you intend to use only the serial programs, you can skip installing the toolchain.

### SerialPrograms can connect to the native programs.

This tutorial assumes that the device is running PABotBase. In reality SerialPrograms will work with any of the [basic programs](../ProgramList.md) running natively on the device provided that the protocol versions are compatible.

PABotBase is the only program that will accept commands over serial, so you will not be able to control the other programs. However, logging from the program will appear in the output window. Therefore SerialPrograms supercedes the DeviceLogger that was released in the native programs.

### Programs do not need to start in the grip menu.

Many of the programs in SerialPrograms are identical to the native ones that don't require serial. However, you don't need to start them in the grip menu.
The purpose of the grip menu is to disconnect your manual controller so that the device can take over as the primary controller. But if you're using the keyboard to control your Switch, the device is likely already the primary controller. So you can actually start the program in the Switch Home menu or even inside the game.

### Multiple Switch Considerations

If you have played with the Switch Viewer program, you will notice that it supports multiple Switches. This is a precursor to future releases that may have programs that utilize multiple Switches simultaneously.

However, we have found that setting up the hardware to handle multiple serial ports and capture cards can be tricky. Sometimes they work, sometimes they don't. And it's often difficult to troubleshoot. This is regardless of whether you are running multiple Switches under the same instance or if you are running multiple instances of one Switch each.

**Serial ports and Cameras can only be used at once place at a time.**

Both serial ports and cameras (capture cards) can only be used by one application at a time. Therefore you cannot view the same video capture from both OBS and SerialPrograms simultaneously. If you want to do this, use the OBS Virtual Camera.

The single-use limitation also applies within the same application. When viewing multiple Switch setups simultaneously, both the serial ports and cameras can only be used at one place at a time. If you try to use the same serial port on a second setup, it won't connect. If you try to use the same camera on a second setup, it won't display.

**Capture Cards don't always play well with USB hubs.**

Capture cards are very hit-and-miss when you try to put multiple of them on the same USB hub.

Some general observations:
1. Capture cards draw a lot of power. If you put them with other high-powered USB devices drawing power from the same source, the card may not function.
2. Capture cards use a lot of USB bandwidth. If you put multiple capture cards on the same USB hub, you may saturate the bandwidth on that hub.
3. For some unknown reason (even when both the above do not apply), it can be difficult to get multiple capture cards on the same physical USB port (by means of a hub) on the computer to work simultaneously. You may need to spread them out. Thus for a 4-Switch setup, your computer will need at least 4 USB ports - one for each capture card. But within each port, you can use a hub to connect *one* capture card and other devices as well. (such as the UART serial connections)






<hr>

**Back to:**
- [Project Home](/README.md)
- [Documentation Home](/Documentation/README.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
