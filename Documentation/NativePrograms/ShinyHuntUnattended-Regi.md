# ShinyHuntUnattended-Regi

Hunt for a shiny Regi golem.

[Please read the appendix to understand how unattended shiny-hunting programs work.](../Appendix/UnattendedShinyHuntingPrograms.md)

When correctly utilized, this program will stop on a shiny thus allowing you to let it run unattended. Note that the Shiny Charm does not work on the Regis, thus the average running time to a shiny is about 50 hours.

*Warning, this program may require calibration. The default settings are not guaranteed to work on your Switch. Read the instructions here carefully and be patient.*

When correctly calibrated:
- If the encounter is not shiny, the program will run from the battle and move on to the next encounter.
- If the encounter is shiny, the program will trap itself inside the Pokémon menu. This allows you to manually back out and fight the shiny Pokémon.

This Regi program involves the (error prone) process of solving the light puzzle. To counter these errors, the program will periodically leave and reenter the building to reset the lights.

<img src="images/ShinyHuntUnattended-Regi.png" width="800">

## Instructions:

*Before you do any extended run, it is important to check your calibration (next section). Do not just fire up this program and expect it to work. Way too many people are overly eager and skip calibration just to end up wasting many hours from locking on false positives or running from shinies.*
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- You must have 7 or more badges or you cannot catch the Regi.
- You must be offline.
- Your lead Pokémon must be able to run away. (faster or holding Smoke Ball)
- Your lead Pokémon must not have high happiness. The in-battle shaking and dialog adds timing variation.
- You must turn off your lead Pokémon following you. Following will cause happiness to increase enough to shake in battle. You can do this by talking to the boy in Freezington.
- You must be standing in front the statue with no lights activated.
- For Regieleki and Regidrago, you must be locked into your choice. (No extra prompt talking to statue.)
- You must be in the overworld. (not inside the menu)
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

**Additional Recommendations (to normalize timings):**

These are strongly recommended since they drastically simplify things.
- Your lead Pokémon is not shiny.
- Your lead Pokémon does not have an ability that activates upon entry to battle.

**Notes:**
- Regice is nearly the same color shiny and non-shiny. The only difference is the shade of the blue, therefore it will be difficult to tell what the program traps on is a shiny. Take a screenshot of a non-shiny Regice on the Switch before you go unattended. That way when it traps, you will have a screenshot on your Switch to compare the shade of blue in the exact same lighting conditions.
- Pay attention to the Pokérus status of your party. This program involves a large number of encounters without any resetting. Thus the chance of getting Pokérus from the wild is actually quite high. If you want your Pokémon untouched, keep them safely in the box. 4 day skips will cure Pokérus from your party.

## Calibration:

Before you continue, first read the appendix on unattended shiny-hunting calibration to better understand how the process works.

Section: [Unattended Shiny-Hunting Calibration](../Appendix/UnattendedShinyHuntingPrograms.md#calibration)

The variable that controls the critical delay for this program is `START_TO_RUN_DELAY`.
- When the encounter is not shiny, the LEDs should turn on ***0.5 – 1.5*** seconds AFTER the battle menu appears. The program will run away from the battle.
- When the encounter is shiny, the LEDs should turn on ***0.5 - 1.0*** seconds BEFORE the battle menu appears. The program will not run away and will instead trap itself in the summary of your Pokémon.

Make only small changes at a time, no more than +/- 50 ticks at a time. Most Switches will have a working value somewhere between 1950 and 2050. Each tick is 8 milliseconds. (125 ticks per second)

## Serial Output:

More on: [Serial Communication](../SerialCommunication.md)

This program outputs the number of attempted encounters. This can be read by the serial programs.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Start to Run Delay:
```
const uint16_t START_TO_RUN_DELAY   =   1970;
```
This is the delay from the last A press on the statue to when you run from the battle. This is the critical parameter that needs to be properly calibrated.

### Regi to Reset For:
```
const RegiGolem REGI_NAME           =   Registeel;
```
This is what you’re resetting for. Pick from: `Regirock`, `Regice`, `Registeel`, `Regieleki`, and `Regidrago`.

### Correction Interval:
```
const uint16_t CORRECTION_INTERVAL  =   20;
```
The light puzzle is not 100% reliable. Sometimes it will miss lights. To counter that, the program will periodically leave and re-enter the building after this many encounters. Zero disables the corrections. If you disable corrections, the program will stop working when it misses a light and will not self-recover.

### Transition Delay:
```
const uint16_t TRANSITION_DELAY     =   5 * TICKS_PER_SECOND;
```
The time needed to enter and exit the building during a correction.

### Rollover Prevention:
```
const uint32_t TOUCH_DATE_INTERVAL = (uint32_t)4 * 3600 * TICKS_PER_SECOND;  //  4 hours
```
This is useful if your game is holding a den and you do not want an unintentional date-skip to destroy it.

Prevent the den from rolling over by periodically touching the date at this interval. Set this value to zero to disable the feature.







<hr>

**Back to:**
- [Project Home](/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
