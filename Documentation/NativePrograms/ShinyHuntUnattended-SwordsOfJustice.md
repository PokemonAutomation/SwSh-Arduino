# ShinyHuntUnattended-SwordsOfJustice

Hunt for shiny Swords of Justice and Spiritomb.

[Please read the appendix to understand how unattended shiny-hunting programs work.](../Appendix/UnattendedShinyHuntingPrograms.md)

***Warning, this program requires calibration and is significantly harder to calibrate than the other unattended programs. Read the instructions here carefully and be patient. Hardly anybody gets it right the first time.***

When correctly calibrated:
- If the encounter is not shiny, the program will run from the battle and move on to the next encounter.
- If the encounter is shiny, the program will trap itself inside the Pokémon menu. This allows you to manually back out and fight the shiny Pokémon.

Be aware that even when correctly calibrated, this program is not 100% reliable. It may trap on a non-shiny (false positive) and it may run from a shiny (false negative).

If you come back and see it trapped, it doesn’t guarantee that the encounter is shiny. This program has a lot more variation and has a higher chance of false positives than the other unattended shiny-hunting programs.

<img src="images/ShinyHuntUnattended-SwordsOfJustice.png" width="800">

## Instructions:

*Before you do any extended run, it is important to check your calibration (next section). Do not just fire up this program and expect it to work. Way too many people are overly eager and skip calibration just to end up wasting many hours from locking on false positives or running from shinies.*

- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- Airplane mode must be off.
- You must be offline.
- The cursor in the menu is over the "Pokémon Camp" option.
- Your lead Pokémon must be faster than the Sword of Justice.
- Your lead Pokémon must not have high happiness. The in-battle shaking and dialog adds timing variation.
- You must have no Pokémon in your party with max happiness. This can add delays in the camp.
- You must have previously defeated or ran away from the Sword of Justice so that it is no longer present.
- You must be standing exactly on the spawn point of the Sword of Justice.
- You must be in the overworld. (not inside the menu)
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

**Additional Recommendations:**

These are strongly recommended since they drastically simplify things.
- Your lead Pokémon is not shiny.
- Your lead Pokémon does not have an ability that activates upon entry to battle.
- The 2nd move on your lead Pokémon should OHKO the Sword of Justice. (helps for failure case recovery)
- The weather in the area does not result in battle weather or terrain (sunlight, rain, snow/sandstorm). Therefore you should change the date to one that has neutral weather unless you are hunting for a mark that requires it.

**Notes:**
- Have the shiny charm. It will reduce the average time to shiny from 35 hours to 12 hours.
- If you change the date to set the weather, be sure to change the date back before you catch the Pokémon. Otherwise, the catch date will be wrong.
- Pay attention to the Pokérus status of your party. This program involves a large number of encounters without any resetting. Thus the chance of getting Pokérus from the wild is actually quite high. If you want your Pokémon untouched, keep them safely in the box. 4 day skips will cure Pokérus from your party.

By default, you cannot use multiple Switches to run this program simultaneously on the same Pokémon. They will try to enter each other’s camps which will break the program. If you need to do this, turn on airplane mode and set `AIRPLANE_MODE` to true.

## Calibration:

Before you continue, first read the appendix on unattended shiny-hunting calibration to better understand how the process works.

Section: [Unattended Shiny-Hunting Calibration](../Appendix/UnattendedShinyHuntingPrograms.md#calibration)

The variable that controls the critical delay for this program is `EXIT_CAMP_TO_RUN_DELAY`.
- When the encounter is not shiny, the LEDs should turn on ***0.3 – 1.7 seconds AFTER*** the battle menu appears. The program will run away from the battle.
- When the encounter is shiny, the LEDs should turn on at least ***~0.3 seconds BEFORE*** the battle menu appears. The program will not run away and will instead trap itself in the summary of your Pokémon.

Make only small changes at a time, no more than +/- 50 ticks at a time. Most Switches will have a working value somewhere between 1800 and 1930 – which corresponds to more than a second difference between the fastest and slowest Switches. Each tick is 8 milliseconds. (125 ticks per second)

**Important Note:**

*The SoJ program has significantly higher timing variation than the other SR programs. As a result, it will be harder to calibrate. It may not even be possible in some cases.*

When you attempt to calibrate, you will find that the variation can be upwards of one second. In other words, you will get an entire range of delays. For the program to work correctly, that entire range of delays needs to fit into the **0.3 – 1.7 second** window as suggested above. Therefore you will need to be patient and time multiple encounters to find that range of delays.

In reality, the range of delays is probably a Gaussian distribution. So even when you think you’ve found the range, there will be occasional outliers that fall outside the window and can cause a false positive or a false negative. False negatives you won’t know unless you happen to see it. False positives will stop the program. If you get false positives after multiple hours of correct operation, then try increasing your delay by 10 ticks.

**Too Much Variation:**

On some Switches and environments, you may find that your range of delays is too large to fit into the recommended timing window. Here are some tricks you can try to reduce that variation:
- Restart your Switch.
- Turn on airplane mode and set “AIRPLANE_MODE” to true.
- Detach your Joy-Cons.

If this still doesn’t work, then it may be impossible to completely avoid both false positives and false negatives. Thus you must choose which one is more acceptable. False negatives are usually more acceptable since they don’t stop the program. Thus you want to calibrate it such that the shortest menu->LED time is about 0.3 seconds. Any shiny encounter that comes in exceptionally fast will be lost since the program will run from it.

If the variation is so high such that it will run from more than 50% of the shiny encounters, then it becomes more time efficient to use the [ShinyHuntUnattended-StrongSpawn](ShinyHuntUnattended-StrongSpawn.md) program instead.

## Serial Output:

More on: [Serial Communication](../SerialCommunication.md)

This program outputs the number of attempted encounters. This can be read by the serial programs.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Exit Camp to Run Delay:
```
const uint16_t EXIT_CAMP_TO_RUN_DELAY   =   1890;
```
This is the delay from when you leave the camp to when you run from the battle. This is the critical parameter that needs to be properly calibrated.
If it is set too high, it will run from a shiny. If it is set too low, it will stop on a non-shiny. There is less than a half-second interval where the program will work reliably. This window will differ from Switch to Switch.

### Airplane Mode:
```
const bool AIRPLANE_MODE                =   false;
```
If you need to run the program in airplane mode, set this to true. It will slow down the program by a couple seconds.

### Time Rollback:
```
const uint8_t TIME_ROLLBACK_HOURS   =   1;
```
Every this many hours, rollback the time by this many hours. This keeps the time constant to prevent the weather from changing. It also allows you to target time-specific marks. Set this to zero to disable this feature.

This feature will also prevent any unintentional day-skips that will destroy any dens that are on the save file.


## Advanced Settings:
These are advanced settings. You shouldn’t need to touch these unless something isn’t working and you’re trying to debug it yourself.


### Enter Camp Delay:
```
const uint16_t ENTER_CAMP_DELAY         =   8 * TICKS_PER_SECOND;
```
Wait this long after entering camp before you leave.





<hr>

**Back to:**
- [Project Home](/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
