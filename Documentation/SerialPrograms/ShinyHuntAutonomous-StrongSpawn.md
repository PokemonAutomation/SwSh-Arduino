# Shiny Hunt Autonomous - Strong Spawn

This is the autonomous version of [ShinyHuntUnattended-StrongSpawn](../NativePrograms/ShinyHuntUnattended-StrongSpawn.md).

This program will automatically hunt for a shiny strong spawn and automatically stop on a shiny. It fully utilizes video feedback and has these advantages over the unattended version of this program:
- No calibration is needed. This program will detect a shiny from its animation.
- When a shiny is encountered, this program will save a video of the encounter.
- This program will keep track of encounter statistics.

**Demo Video:** https://cdn.discordapp.com/attachments/755635697737531544/822487995407532032/StrongSpawn.mp4

<img src="images/ShinyHuntAutonomous-StrongSpawn.jpg" width="800">

## Instructions:

**General Requirements:**
- Video resolution is 1280 x 720 or higher. Shiny detection is not reliable at low resolutions.
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- Your lead Pokémon must be able to run away. (faster or holding Smoke Ball)
- Your lead Pokémon must not be shiny. (this will cause false positive detections)
- Change the date to one that has the appropriate weather for your desired strong spawn.

**Setup Instructions:** (There are many ways to do this. This is just an example.)
1. Despawn the Pokémon by fighting it and running, defeating, or catching it.
2. Stand directly on the spawn spot for your desired Pokémon.
3. Activate the VS (Y-COMM) glitch.
4. Change the date forward and backwards one day. (This forces a day skip while resetting the date.)
5. Save the game.

**Run Program Instructions:**
- The game must be closed.
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

**Recommended for Performance:**
- Have the Shiny Charm. This triples the chance to find a shiny.
- Your lead Pokémon does not have high happiness.
- Your lead Pokémon does not have an ability that activates upon entry to battle.

When the a shiny is found, the program will save a video of the encounter. Then it will go to the Switch home to idle.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

There is no option to search only for a square shiny. Nearly all shinies are square and only 15/65536 are star. Therefore it is infeasible to hunt for star shiny.

### Go Home when Done:

After finding a shiny, go to the Switch Home to idle. Turn this off for unattended streaming so that your viewers can see the shiny.

### Time Rollback:

Every this many hours, rollback the time by this many hours. This keeps the time constant to prevent the weather from changing. It also allows you to target time-specific marks. Set this to zero to disable this feature.


## Advanced Settings:
These are advanced settings. You shouldn’t need to touch these unless something isn’t working and you’re trying to debug it yourself.


### Exit Battle Time:

After running, wait this long to return to the overworld.


<hr>

**Back to:**
- [Project Home](/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
