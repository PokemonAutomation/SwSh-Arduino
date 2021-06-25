# Shiny Hunt Autonomous - Fishing

This program will shiny hunt fishing encounters. This program is new to the serial programs since it is infeasible without feedback.

- No calibration is needed. This program will detect a shiny from its animation.
- When a shiny is encountered, this program will save a video of the encounter.
- This program will keep track of encounter statistics.

**Demo Video:** https://cdn.discordapp.com/attachments/755635697737531544/823709108150075412/2021-03-22_19-04-14.mp4

<img src="images/ShinyHuntAutonomous-Fishing.jpg" width="800">

## Instructions:
- Screen size must be 100%.
- Video resolution is 1280 x 720 or higher. Shiny detection is not reliable at low resolutions.
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- You must be standing in front of a fishing spot.
- Your lead Pokémon must be able to run away. (faster or holding Smoke Ball)
- Your lead Pokémon must not be shiny. (this will cause false positive detections)
- You must be in the overworld. (not inside the menu)
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

**Recommended for Performance:**
- Have the Shiny Charm. This triples the chance to find a shiny.
- Your lead Pokémon does not have high happiness.
- Your lead Pokémon does not have an ability that activates upon entry to battle.
- Zoom in. The bigger exclamation icon is easier for the inference to detect. 

When a shiny is found, the program will save a video of the encounter.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

There is no option to search only for a square shiny. Nearly all shinies are square and only 15/65536 are star. Therefore it is infeasible to hunt for star shiny.


### Go Home when Done:

After finding a shiny, go to the Switch Home to idle. Turn this off for unattended streaming so that your viewers can see the shiny.


### Game Language:

If set to a language, the program will attempt to read the name of each Pokémon you encounter and log it.


### Time Rollback:

Every this many hours, rollback the time by this many hours. This keeps the time constant to prevent the weather from changing. It also allows you to target time-specific marks. Set this to zero to disable this feature.


## Advanced Settings:
These are advanced settings. You shouldn’t need to touch these unless something isn’t working and you’re trying to debug it yourself.


### Exit Battle Timeout:

After running, wait this long to return to the overworld. The program will resume before this time if it detects that that the battle has ended.

### Fish Respawn Time:

Wait this long for the fishing spot to respawn.

<hr>

**Back to:**
- [Project Home](/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
