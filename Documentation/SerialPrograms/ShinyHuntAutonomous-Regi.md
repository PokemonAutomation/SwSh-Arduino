# Shiny Hunt Autonomous - Regi

This is the autonomous version of [ShinyHuntUnattended-Regi](../NativePrograms/ShinyHuntUnattended-Regi.md).

This program will automatically hunt for a shiny Regi golem and automatically stop on a shiny. It fully utilizes video feedback and has these advantages over the unattended version of this program:
- No calibration is needed. This program will detect a shiny from its animation.
- When a shiny is encountered, this program will save a video of the encounter.
- This program will distinguish star shinies from square shinies.
- There is an option to hunt only for squares and run from all stars.
- Autonomous programs are faster than their unattended counterparts since they use feedback instead of timed waits.
- This program will keep track of encounter statistics.
- Light corrections are now on-demand instead of periodic. This program will detect when the floor lights are wrong and will do the correction only when needed.

**Demo Videos:**
- Star: https://cdn.discordapp.com/attachments/755635697737531544/821048280187928616/2021-03-15_10-31-35.mp4
- Square: https://cdn.discordapp.com/attachments/755635697737531544/824087881119301672/2021-03-23_20-06-38.mp4

<img src="images/ShinyHuntAutonomous-Regi.jpg" width="800">
<img src="images/ShinyHuntAutonomous-Regi-Square.jpg" width="800">

## Instructions:
- Screen size must be 100%.
- Video resolution is 1280 x 720 or higher. Shiny detection is not reliable at low resolutions.
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- You must have 7 or more badges or you cannot catch the Regi.
- Your lead Pokémon must be able to run away. (faster or holding Smoke Ball)
- Your lead Pokémon must not be shiny. (this will cause false positive detections)
- You must be standing in front the statue with no lights activated.
- For Regieleki and Regidrago, you must be locked into your choice. (No extra prompt talking to statue.)
- You must be in the overworld. (not inside the menu)
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

**Recommended for Performance:**
- Your lead Pokémon does not have high happiness.
- Your lead Pokémon does not have an ability that activates upon entry to battle.

When the desired shiny is found, the program will save a video of the encounter.

Note that the Shiny Charm does not work on the Regis.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Go Home when Done:

After finding a shiny, go to the Switch Home to idle. Turn this off for unattended streaming so that your viewers can see the shiny.

### Require Square:

The option will make the program run from star shinies and stop only on a square shiny. It will still record videos of all shinies.

### Regi:

This is what you’re resetting for. Pick from: `Regirock`, `Regice`, `Registeel`, `Regieleki`, and `Regidrago`.

### Rollover Prevention:

This is useful if your game is holding a den and you do not want an unintentional date-skip to destroy it.

Prevent the den from rolling over by periodically touching the date at this interval. Set this value to zero to disable the feature.


## Advanced Settings:
These are advanced settings. You shouldn’t need to touch these unless something isn’t working and you’re trying to debug it yourself.


### Exit Battle Timeout:

After running, wait this long to return to the overworld. The program will resume before this time if it detects that that the battle has ended.

### Transition Delay:

The time needed to enter and exit the building during a correction.


<hr>

**Back to:**
- [Project Home](/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
