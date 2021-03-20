# Shiny Hunt Autonomous - Regigigas2

This is the autonomous version of [ShinyHuntUnattended-Regigigas2](../NativePrograms/ShinyHuntUnattended-Regigigas2.md).

This program will automatically hunt for Regigigas and automatically stop on a shiny. It fully utilizes video feedback and has these advantages over the unattended version of this program:
- No calibration is needed. This program will detect a shiny from its animation.
- When a shiny is encountered, this program will save a video of the encounter.
- This program will distinguish star shinies from square shinies.
- There is an option to hunt only for squares and run from all stars.
- Autonomous programs are faster than their unattended counterparts since they use feedback instead of timed waits.
- This program will keep track of encounter statistics.
- This program will detect error situations and automatically reset the game.

**Demo Video:** https://cdn.discordapp.com/attachments/755635697737531544/822702343606632458/2021-03-20_00-22-46.mp4

<img src="images/ShinyHuntAutonomous-Regigigas2.jpg" width="800">


## Instructions:
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- *The first move on your lead Pokémon must be able to OHKO the Regigigas. (see below)*
- You must be saved in front of the Regigigas den.
- The `REVERSAL_PP` parameter must be set to no more than the amount of PP of your second move.
- You must be in the overworld. (not inside the menu)
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

**Recommended for Performance:**
- Battle animations are off.
- Your lead Pokémon does not have high happiness.
- Your lead Pokémon does not have an ability that activates upon entry to battle.
- The first move on your lead Pokémon (Reversal) is fully PP up’ed to 24 PP.

**As of this writing, there is only one known way to ensure a OHKO on Regigigas:**
1. Your Pokémon is fighting type (for STAB).
2. Your Pokémon has only 1 HP. (base power 200) Use the move Endure to help get to 1 HP.
3. Your Pokémon is holding a Choice Band.
4. The move being used is Reversal.
5. Your Pokémon has a very high attack stat. (high base stat + 252 EVs + 31 IV + beneficial nature)

Here is an example of a lead Pokémon that is properly setup to guarantee a OHKO on Regigigas.

<img src="../NativePrograms/images/ShinyHuntUnattended-Regigigas2-0.png" width="400"> <img src="../NativePrograms/images/ShinyHuntUnattended-Regigigas2-1.png" width="400">
<img src="../NativePrograms/images/ShinyHuntUnattended-Regigigas2-2.png" width="400">

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Reversal PP:

This is the amount of PP of your attacking move. Reversal has 24 PP when fully PP up’ed.

### Catch to Overworld Delay:

The amount of time from when you choose not to catch Regigigas to when you return to the overworld.

### Rollover Prevention:

This is useful if your game is holding a den and you do not want an unintentional date-skip to destroy it.

Prevent the den from rolling over by periodically touching the date at this interval. Set this value to zero to disable the feature.

<hr>

**Back to:**
- [Project Home](/README.md)
- [Documentation Home](/Documentation/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
