# ShinyHuntUnattended-StrongSpawn

Soft-reset for shiny strong spawns.

[Please read the appendix to understand how unattended shiny-hunting programs work.](../Appendix/UnattendedShinyHuntingPrograms.md)

When correctly utilized, this program will stop on a shiny thus allowing you to let it run unattended. This program will also work on the Swords of Justice legendaries, but slower.

To read more about this method, search online for “Strong Spawn Shiny Hunting Method”. We won’t bother reiterating the mechanics of the method here.

This program will only work on Pokémon with non-activating abilities or if both abilities activate with the same delay. It will not work with Pokémon that have two abilities where only one activates upon battle entry.

*Warning, this program will require calibration. The default settings are not guaranteed to work on your Switch. Read the instructions here carefully and be patient. Hardly anybody gets it right the first time.*

When correctly calibrated:
- If the encounter is not shiny, the program will run from the battle and move on to the next encounter.
- If the encounter is shiny, the program will trap itself inside the Pokémon menu. This allows you to manually back out and fight the shiny Pokémon.

<img src="images/ShinyHuntUnattended-StrongSpawn.png" width="800">

## Instructions:

Before you do any extended run, it is important to check your calibration (next section). Do not just fire up this program and expect it to work. Way too many people are overly eager and skip calibration just to end up wasting many hours from locking on false positives or running from shinies.

**General Requirements:**
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- The game save has been online at least once before.
- Your lead Pokémon must be able to run away. (faster or holding Smoke Ball)
- Your lead Pokémon must not have high happiness. The in-battle shaking and dialog adds timing variation.
- Change the date to one that has the appropriate weather for your desired strong spawn.

**Setup Instructions:** (There are many ways to do this. This is just an example.)
1. Despawn the Pokémon by fighting it and running, defeating, or catching it.
2. Stand directly above the spawn spot for your desired Pokémon.
3. Activate the VS (Y-COMM) glitch.
4. Change the date forward and backwards one day. (This forces a day skip while resetting the date.)
5. Save the game.

**Run Program Instructions:**
- Airplane mode must be off.
- The game must be closed.
-	Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

If done correctly, the program will start up the game and you will immediately get attacked by your desired strong spawn. If it is not-shiny, it runs away and resets the game. If it is shiny, it traps itself in the summary page.

**Additional Recommendations (to normalize timings):**

These are strongly recommended since they drastically simplify things.
- Your lead Pokémon is not shiny.
- Your lead Pokémon does not have an ability that activates upon entry to battle.

**Notes:**
- Have the shiny charm. It will reduce the average time to shiny from 68 hours to 23 hours.
- If you change the date to set the weather, be sure to change the date back before you catch the Pokémon. Otherwise, the catch date will be wrong.

The speed of this program is heavily affected by how quickly the program can reset the game. By default, the soft-reset timings are very loose to ensure that they work on the most Switches. You can optimize this by adjusting the `START_GAME_WAIT_DELAY` parameter.


## Calibration:

Before you continue, first read the appendix on unattended shiny-hunting calibration to better understand how the process works.
Section: Unattended Shiny-Hunting Calibration

The variable that controls the critical delay for this program is `ENTER_GAME_TO_RUN_DELAY`.
- When the encounter is not shiny, the LEDs will turn on ***0.5 – 1.5 seconds AFTER*** the battle menu appears. The program will run away from the battle.
- When the encounter is shiny, the LEDs will turn on ***0.5 -1.0 seconds BEFORE*** the battle menu appears. The program will not run away and will instead trap itself in the summary of your Pokémon.

Unlike the Regi and Sword of Justice programs, you will likely need to make large adjustments to the delay to make things work. Use a stopwatch to help you. Each tick is 8 milliseconds, and each second is 125 ticks.

Because you will get attacked the moment you enter the game, changing the lead will require repeating all the steps in “Setup Instructions”. So heads up since this can get annoying after a while.

*Due to the large number of strong spawn possibilities with different weather and ability combinations, the default setting is unlikely to work. Therefore you are pretty much required to calibrate.*

## Serial Output:

More on: [Serial Communication](../SerialCommunication.md)

This program outputs the number of attempted encounters. This can be read using the Device Logger.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Enter Game to Run Delay:
```
const uint16_t ENTER_GAME_TO_RUN_DELAY  =   2280;
```
This is the delay from when you enter the game to when you run from the encounter. This is the critical parameter that needs to be properly calibrated.

### Start Game Wait Delay:
```
const uint16_t START_GAME_WAIT_DELAY    =   20 * TICKS_PER_SECOND;
```
After starting the game, wait this long before press A to actually enter the game. By default, this is set very high to ensure that the program works. You can try reducing this to make resetting faster.

### Time Rollback:
```
const uint8_t TIME_ROLLBACK_HOURS   =   1;
```
Every this many hours, rollback the time by this many hours. This keeps the time constant to prevent the weather from changing. It also allows you to target time-specific marks. Set this to zero to disable this feature.




<hr>

**Back to:**
- [Project Home](/README.md)
- [Documentation Home](/Documentation/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
