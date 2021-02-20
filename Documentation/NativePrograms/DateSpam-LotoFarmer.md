# DateSpam-LotoFarmer

LotoFarmer will farm the loto. It requires activating the VS glitch.

This program runs at 18.4 seconds per attempt.

<img src="images/DateSpam-LotoFarmer.png" width="800">

## Instructions:
- Casual mode is off.
- Your text speed must be set to fast.
- You must have system time unsynced.
- The VS (Y-COMM) glitch must be active.
- You must be standing in front of the PC.
-	Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

This program will not work if the system update window is present. Instead, it will safely enter a do-nothing loop within the settings.

## Serial Output:

More on: [Serial Communication](../SerialCommunication.md)

This program outputs the number of loto attempts. This can be read using the Device Logger.

## Options:
This program does not have the ability to avoid the system update window. Should the window appear while the program is running, the program will enter a safe do-nothing loop within the Switch settings.

### Attempts:
```
const uint32_t SKIPS    =   100000;
```
Perform this many loto attempts. The only reason to set this number is if you’re also skipping to a den frame and you don’t want to overshoot. But be aware that this program isn’t intended to be an accurate date skipper. It may occasionally miss skips which can cause it to fall short.

### Mash B Duration:
```
const uint16_t MASH_B_DURATION  =   8 * TICKS_PER_SECOND;
```
Mash B this long to exit the dialog after attempt. You shouldn’t need to touch this. But for some languages (like German), you may need to increase this by a 1 or 2 seconds.




<hr>

**Back to:**
- [Project Home](/README.md)
- [Documentation Home](/Documentation/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
