# DateSpam-BerryFarmer

BerryFarmer will farm berries from a tree. It requires activating the VS glitch.

This program runs at 13.1 seconds per fetch.

<img src="images/DateSpam-BerryFarmer.png" width="800">

## Instructions:
- Casual mode is off.
- Your text speed must be set to fast.
- You must have system time unsynced.
- The VS (Y-COMM) glitch must be active.
- You must be standing in front of a berry tree.
- Your location should be safe from getting attacked by wild Pokémon.
-	Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

This program will not work if the system update window is present. Instead, it will safely enter a do-nothing loop within the settings.

## Serial Output:

More on: [Serial Communication](../SerialCommunication.md)

This program outputs the number of berry fetch attempts. This can be read using the Device Logger.

## Stability Recommendations:

Stand behind the berry tree so that the tree is directly in front of (and blocking) your character.

Sometimes, the program will miss a button press which causes the date-spamming to happen in the game instead of the Switch settings. This will cause the character to move downwards and away from the tree if you’re not standing behind it.

## Options:
This program does not have the ability to avoid the system update window. Should the window appear while the program is running, the program will enter a safe do-nothing loop within the Switch settings.

### Fetch Attempts:
```
const uint32_t SKIPS            =   100000;
```
Perform this many fetch attempts. The only reason to set this number is if you’re also skipping to a den frame and you don’t want to overshoot. But be aware that this program isn’t intended to be an accurate date skipper. It may occasionally miss skips which can cause it to fall short.

### Periodically Save the Game:
```
const uint16_t SAVE_ITERATIONS  =   0;
```
If set to anything other than zero, the program will periodically save the game at the specified interval. In rare cases, the date-skipping can cause the game to crash, thus periodic saves can be enabled to reduce the amount of work that is lost.

