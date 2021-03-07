# ShinyHuntUnattended-IoATrade

Soft-reset for shiny Isle of Armor foreign form trades. 

[Please read the appendix to understand how unattended shiny-hunting programs work.](../Appendix/UnattendedShinyHuntingPrograms.md)

In all seriousness, this (along with Regigigas) should not be the first unattended shiny-hunting program that you choose to use. Both programs are very absurd and are only possible by abusing a large number of exploits. 

This program does one encounter every ~2 minutes. This leads to 5.5 day odds for a shiny. If you intend to square hunt with this program, average time is 3 months on one Switch. Therefore, this program will be a test of patience.

*Warning, this program may require calibration. The default settings are not guaranteed to work on your Switch. Read the instructions here carefully and be patient. Hardly anybody gets it right the first time.*

This program works by performing a trade and then forcing an encounter with the Beartic on Route 10.

When correctly calibrated:
- If neither Pokémon is shiny, the program will run from the Beartic and reset for the next attempt.
- If either the traded Pokémon or the Beartic is shiny, the program will lock itself in the Pokémon summary.

With Shiny Charm, 75% of the shiny locks will be on a shiny Beartic. The remaining 25% will be for the traded Pokémon. Therefore, this program is more efficient without Shiny Charm.

<img src="images/ShinyHuntUnattended-IoATrade.png" width="800">

## Instructions:
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- Airplane mode must be off.
- The game save has been online at least once before.
- The fly spot on Route 10 must be activated.
- The Beartic on Route 10 must be active. (not despawned due to a prior encounter)
- The Pokémon that you will be trading away must be in the first party slot.
- The Pokémon in your second party slot must be holding a Smoke Ball.
- The menu icons are in their default locations:
  - The Pokédex must be in the upper-left corner.
  - The Pokémon option must be in the 1st row, 2nd from the left. 
  - The Town Map must be in the 2nd row on the far left.
- The cursor in the menu is over the "Pokédex" option.
- You must be standing in front of the lady who will do the trade.
- You must be on your bike.
- You must be saved in the above position.
- You must be in the overworld. (not inside the menu)
-	Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

Once started, the program will do the following:
1. Perform the trade.
2. Go into your Pokémon summary to move the Smoke Ball from the 2nd Pokémon to the lead Pokémon.
3. Fly to Route 10.
4. Bike to the right to encounter the Beartic.
5. If neither Pokémon is shiny, it will run. If either is shiny, it will lock in the summary.
6. Perform a conditional soft-reset.
7. Repeat steps 1-6.


*If the program locks on a shiny Beartic, you do not have to throw it away by resetting. The Isle of Armor trades can be repeated. You just need to day skip to reroll and find Regina again until you she offers you the same trade.*

*If you get a Shiny trade (or you decide to keep a shiny Beartic instead), the Beartic will respawn after a day skip.*

On a shiny trade, it will appear shiny in the trade itself.

<img src="images/ShinyHuntUnattended-IoATrade-0.png" width="400">

## Calibration:

Before you continue, first read the appendix on unattended shiny-hunting calibration to better understand how the process works.

Section: [Unattended Shiny-Hunting Calibration](../Appendix/UnattendedShinyHuntingPrograms.md#calibration)

**Calibrating the Run-Away time:**
The variable that controls the critical delay for this program is “START_TO_RUN_DELAY”.
- If neither Pokémon is shiny, the LEDs will turn on ***0.5 – 1.5 seconds AFTER*** the battle menu appears. The program will run from the Beartic.
- If either Pokémon is shiny, the LEDs will turn on ***0.5 – 1.0 seconds BEFORE*** the battle menu appears. The program will not run and will instead trap  itself in the summary of your Pokémon.

Make only small changes at a time, no more than +/- 50 ticks at a time. Most Switches will have a working value somewhere between 1200 and 1300. Each tick is 8 milliseconds. (125 ticks per second)

Because of the nature of this program, you will not be able to use a shin lead to test shiny calibration. You must use the method of subtracting 250 ticks.

**Calibrating the Fly Duration:**

To complicate things even further, there is a second delay which may need to be calibrated for the program to work correctly, `FLY_DURATION`.

This controls how long it takes to fly to Route 10. This delay can vary a lot from Switch to Switch and whether your game is physical or digital.

If you find that your character does not move towards the Beartic soon after landing and the Beartic wanders too far from its spawn location, you will need to reduce this time. If you modify this value, you may need to recalibrate `START_TO_RUN_DELAY`.


## Serial Output:

More on: [Serial Communication](../SerialCommunication.md)

This program outputs the number of attempted encounters. This can be read by the serial programs.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Start to Run Delay:
```
const uint16_t START_TO_RUN_DELAY   =   1240;
```
This is the delay from when stop moving toward the Beartic to when you run away. This is the critical parameter that needs to be properly calibrated.

### Fly Duration:
```
const uint16_t FLY_DURATION         =   800;
```
This is the time it takes to fly to Route 10. This number may need to be calibrated if you spend too much time standing after flying such that the Beartic moves away from the spawn spot.

### Move Duration:
```
const uint16_t MOVE_DURATION        =   300;
```
This is how long to move towards the Beartic after landing on Route 10.

### Mash to Trade Delay:
```
const uint16_t MASH_TO_TRADE_DELAY  =   3625;
```
This is how long from when you start the trade to when the trade ends. You shouldn’t need to change this.

### Rollover Prevention:
```
const uint32_t TOUCH_DATE_INTERVAL = (uint32_t)4 * 3600 * TICKS_PER_SECOND;  //  4 hours
```
This is useful if your game is holding a den and you do not want an unintentional date-skip to destroy it.

Prevent the den from rolling over by periodically touching the date at this interval.

Set this value to zero to disable the feature.





<hr>

**Back to:**
- [Project Home](/README.md)
- [Documentation Home](/Documentation/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
