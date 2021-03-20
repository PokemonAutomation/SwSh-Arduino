# DenRoller

Roll a den forward by N days, show what it is, then reset.

Use this program to roll for a specific Pokémon in your den.

## Instructions:
- Casual mode is off.
- Your text speed must be set to fast.
- You must have system time unsynced.
- You must be standing in front of a wishing piece den with watts collected.
- Your location should be safe from getting attacked by wild Pokémon.
- You must be in the overworld.
- You must be saved in the above position.
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

*If starting the game requires checking the internet (because it is digital on a non-primary Switch), you will need to open up `PokemonSettings.c` and change `START_GAME_REQUIRES_INTERNET` to true.*

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_SLOW`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-slow) to bypass the system update window.

### Frame Skips:
```
const uint8_t SKIPS         =   3;
```
The number of frames to roll. The default is 3. But some people may prefer to save high-value dens more than 3 days back for added safety in case of accidental roll-over.

### Catchability:
```
//  ALWAYS_CATCHABLE    All pokemon in this den are catchable.
//  MAYBE_UNCATCHABLE   There may be uncatchable pokemon.
const Catchability CATCHABILITY     =   ALWAYS_CATCHABLE;
```
Some dens have uncatchable Pokémon (i.e. Mewtwo or Zeraora). If the den has any such uncatchable Pokémon, you must this to `MAYBE_UNCATCHABLE`.

## Delay Before Reset:
```
const uint16_t VIEW_TIME    =   5 * TICKS_PER_SECOND;
```
View the rolled Pokémon for this long before resetting.




<hr>

**Back to:**
- [Project Home](/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
