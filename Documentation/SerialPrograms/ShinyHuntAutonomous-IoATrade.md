# Shiny Hunt Autonomous - Isle of Armor Trade

This is the autonomous version of [ShinyHuntUnattended-IoATrade](../NativePrograms/ShinyHuntUnattended-IoATrade.md).

This program will automatically hunt for a shiny Regina trade and stop on a shiny. It fully utilizes video feedback and has these advantages over the unattended version of this program:
- No calibration is needed. This program will detect a shiny from its shiny icon.
- When a shiny is found, this program will save a video of the encounter.
- Autonomous programs are faster than their unattended counterparts since they use feedback instead of timed waits.
- This program will keep track of encounter statistics.
- This program will automatically recover from errors by resetting the game.

**Demo Video:** https://cdn.discordapp.com/attachments/755635697737531544/823274129292525638/2021-03-21_14-14-40.mp4

<img src="images/ShinyHuntAutonomous-IoATrade.jpg" width="800">

## Instructions:
- Screen size must be 100%.
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- The Pokémon that you will be trading away must be in the first party slot.
- The menu icons are in their default locations:
  - The Pokédex must be in the upper-left corner.
  - The Pokémon option must be in the 1st row, 2nd from the left. 
- The cursor in the menu is over the "Pokédex" option.
- You must be standing in front of the lady who will do the trade.
- You must be saved in the above position.
- You must be in the overworld. (not inside the menu)
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

When a shiny is found, the program will save a video of the encounter.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Go Home when Done:

After finding a shiny, go to the Switch Home to idle. Turn this off for unattended streaming so that your viewers can see the shiny.

### Rollover Prevention:

This is useful if your game is holding a den and you do not want an unintentional date-skip to destroy it.

Prevent the den from rolling over by periodically touching the date at this interval. Set this value to zero to disable the feature.


## Advanced Settings:
These are advanced settings. You shouldn’t need to touch these unless something isn’t working and you’re trying to debug it yourself.


### Mash to Trade Delay:

This is how long from when you start the trade to when the trade ends. You shouldn’t need to change this.


<hr>

**Back to:**
- [Project Home](/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
