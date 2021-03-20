# ShinyHuntUnattended-Regigigas2

Soft-reset for shiny Regigigas.

[Please read the appendix to understand how unattended shiny-hunting programs work.](../Appendix/UnattendedShinyHuntingPrograms.md)

This is a more optimized version of [ShinyHuntUnattended-Regigigas](ShinyHuntUnattended-Regigigas.md) that runs at about one minute per encounter. It uses a method based on a comment under one of brianuuuSonic’s videos suggesting that Reversal can OHKO Regigigas.

This program uses a 1 HP lead that is able to OHKO the Regigigas using the move Reversal. Then it retries until it runs out of PP where it will do a soft-reset to restore the PP and continue.

*Warning, this program may require calibration. The default settings are not guaranteed to work on your Switch. Read the instructions here carefully and be patient. Hardly anybody gets it right the first time.*

When correctly calibrated:
- If the encounter is not shiny, the program will kill Regigigas, not catch it, and move on.
- If the encounter is shiny, the program will trap itself inside the Pokémon menu. This allows you to manually back out and fight the shiny Regigigas.

<img src="images/ShinyHuntUnattended-Regigigas2.png" width="800">

## Instructions:

**Instructions:**
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- Battle animations are off.
- Airplane mode must be off.
- The game save has been online at least once before.
- Your lead Pokémon must not have high happiness. The in-battle shaking and dialog adds timing variation.
- Your lead Pokémon must be faster than Regigigas.
- *The second move on your lead Pokémon must be able to OHKO the Regigigas. (see below)*
- You must be saved in front of the Regigigas den.
- The `REVERSAL_PP` parameter must be set to no more than the amount of PP of your second move.
- You must be in the overworld. (not inside the menu)
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

**Additional Recommendations (to normalize timings):**
- Your lead Pokémon is not shiny.
- Your lead Pokémon does not have an ability that activates upon entry to battle.
- The second move on your lead Pokémon (Reversal) is fully PP up’ed to 24 PP.

**As of this writing, there is only one known way to ensure a OHKO on Regigigas:**
1. Your Pokémon is fighting type (for STAB).
2. Your Pokémon has only 1 HP. (base power 200) Use the move Endure to help get to 1 HP.
3. Your Pokémon is holding a Choice Band.
4. The move being used is Reversal.
5. Your Pokémon has a very high attack stat. (high base stat + 252 EVs + 31 IV + beneficial nature)

Here is an example of a lead Pokémon that is properly setup to guarantee a OHKO on Regigigas.

<img src="images/ShinyHuntUnattended-Regigigas2-0.png" width="400"> <img src="images/ShinyHuntUnattended-Regigigas2-1.png" width="400">
<img src="images/ShinyHuntUnattended-Regigigas2-2.png" width="400">

## Calibration:

Before you continue, first read the appendix on unattended shiny-hunting calibration to better understand how the process works.

Section: [Unattended Shiny-Hunting Calibration](../Appendix/UnattendedShinyHuntingPrograms.md#calibration)

The variable that controls the critical delay for this program is `START_TO_ATTACK_DELAY`.
- When the encounter is not shiny, the LEDs will turn on ***0.5 – 1.5 seconds AFTER*** the battle menu appears. The program will attack and kill Regigigas, then return to the front of the den for the next encounter.
- When the encounter is shiny, the LEDs will turn on ***0.5 – 1.0 seconds BEFORE*** the battle menu appears. The program will not attack and will instead trap itself in the summary of your Pokémon.

Make only small changes at a time, no more than +/- 50 ticks at a time. Most Switches will have a working value somewhere between 3650 and 3800. Each tick is 8 milliseconds. (125 ticks per second)

## Serial Output:

More on: [Serial Communication](../SerialCommunication.md)

This program outputs the number of attempted encounters. This can be read by the serial programs.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Reversal PP:
```
const uint8_t REVERSAL_PP       =   24;
```
This is the amount of PP of your attacking move. Reversal has 24 PP when fully PP up’ed.

### Start to Attack Delay:
```
const uint16_t START_TO_ATTACK_DELAY    =   3750;
```
This is the delay from when talk to the den to when you attack Regigigas. This is the critical parameter that needs to be properly calibrated.

### Attack to Catch Delay:
```
const uint16_t ATTACK_TO_CATCH_DELAY    =   11 * TICKS_PER_SECOND;
```
The amount of time from when you attack Regigigas to when you can choose to catch or leave it.

### Catch to Overworld Delay:
```
const uint16_t CATCH_TO_OVERWORLD_DELAY =   8 * TICKS_PER_SECOND;
```
The amount of time from when you choose not to catch Regigigas to when you return to the overworld.

### Rollover Prevention:
```
const uint32_t TOUCH_DATE_INTERVAL = (uint32_t)4 * 3600 * TICKS_PER_SECOND;  //  4 hours
```
This is useful if your game is holding a den and you do not want an unintentional date-skip to destroy it.

Prevent the den from rolling over by periodically touching the date at this interval. Set this value to zero to disable the feature.










<hr>

**Back to:**
- [Project Home](/README.md)
- [Documentation Home](/Documentation/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
