# Shiny Hunt Autonomous - Berry Tree

This program will shiny hunt the berry tree encounters. This program is new to the serial programs since it is infeasible without feedback.

- No calibration is needed. This program will detect a shiny from its animation.
- When a shiny is encountered, this program will save a video of the encounter.
- This program will distinguish star shinies from square shinies.
- There is an option to hunt only for squares and run from all stars.
- This program will keep track of encounter statistics.

**Demo Video:** https://cdn.discordapp.com/attachments/755635697737531544/821977215725469726/2021-03-18_00-21-14.mp4

<img src="images/ShinyHuntAutonomous-BerryTree.jpg" width="800">

## Instructions:
- Video resolution is 1280 x 720 or higher. Shiny detection is not reliable at low resolutions.
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- The VS (Y-COMM) glitch must be active.
- Your lead Pokémon must be able to run away. (faster or holding Smoke Ball)
- Your lead Pokémon must not be shiny. (this will cause false positive detections)
- You must be standing in front of a berry tree.
- You must be in the overworld. (not inside the menu)
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

**Recommended for Performance:**
- Have the Shiny Charm. This triples the chance to find a shiny.
- Your lead Pokémon does not have high happiness.
- Your lead Pokémon does not have an ability that activates upon entry to battle.

When the desired shiny is found, the program will save a video of the encounter. Then it will go to the Switch home to idle.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Go Home when Done:

After finding a shiny, go to the Switch Home to idle. Turn this off for unattended streaming so that your viewers can see the shiny.

### Require Square:

The option will make the program run from star shinies and stop only on a square shiny. It will still record videos of all shinies.

### Exit Battle Time:

After running, wait this long to return to the overworld.

<hr>

**Back to:**
- [Project Home](/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
