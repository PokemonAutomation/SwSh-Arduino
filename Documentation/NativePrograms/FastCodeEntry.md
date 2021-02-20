# FastCodeEntry

This is one of the most evil programs. FastCodeEntry can enter any 8-digit raid code in about ~0.5 seconds. This includes complicated codes that require multiple keypad traversals.

So in all cases, this is fast enough to muscle your way into people’s coded raids at superhuman speeds.

*By using this program, you agree that you are an asshole. Furthermore, you will be required to embrace your asshole status by flaunting it in front of all the people you’ve blocked out of raids.*

This is the same code entry routine that’s used by the auto-hosts. But as a standalone program, it is much more dangerous and morally reprehensible.

Due to the nature of this program and its intended use-case, this program does not wait to start nor does it flash the LEDs. It runs immediately after connecting to the Switch.

## Instructions:
- The code entry pad must be up.
- The cursor must be over the "1" digit.
- No digits have been entered yet.
- Plug in the Arduino/Teensy and it will enter the code.

Once the program finishes entering the code, it will enter the lobby and disconnect itself from the Switch.

The idea here is that once you see the stamp you want, you manually mash A into it until the code entry pad pops up. Then you plug in or turn on the Arduino and it will hammer the code out for you.

To use this program effectively, it is strongly recommended to get a USB cable with a power button to easily turn on and off the Arduino/Teensy.

<img src="images/FastCodeEntry-0.png" width="400">

## Options:

### Raid Code:
```
const char* RAID_CODE = "9107 3091";
```
Pretty self-explanatory.

The program will skip non-digit characters. So the space or hyphen separator is optional.




<hr>

**Back to:**
- [Project Home](/README.md)
- [Documentation Home](/Documentation/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
