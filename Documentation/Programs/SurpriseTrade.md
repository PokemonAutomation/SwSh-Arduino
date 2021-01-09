# SurpriseTrade

SurpriseTrade will surprise trade entire boxes of Pokémon. The main use case is gathering trainer IDs for Loto farming and to farm hacked Pokémon+items surprise trades.

This program is similar to brianuuuSonic's BoxSurpriseTrade, but is also tolerant to errors when changing boxes.

## Instructions:
- Casual mode is off.
- Your text speed must be set to fast.
- Nicknaming needs to be off. (in case of a trade evolution)
- If you are trading online, make sure you have a strong internet connection.
- You must be in the overworld. (not in the menu)
- There is nothing in front of you that can be interacted with.
- You should be backed into a corner where you cannot travel down or right.
- Your location should be safe from getting attacked by wild Pokémon.
- If you wish to surprise trade online, be connected to the internet before you start the program. Thus you will need to be fast when starting the program or you will be disconnected.
-	Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

Once started, this program will surprise trade the specified number of boxes consecutively starting from the current box.

When the program reaches the end of a box, it will pause for a longer period before moving the next box. This is to ensure that any errors from a preceding trade will have cleared out.

## Box Setup:
- Place boxes* of Pokémon to be surprise traded consecutively.
- You must be on the first box.
- Do not have any untradable Pokémon in these boxes. (no eggs or fused Pokémon)

*The boxes do not need to be full. Empty slots are safely skipped.

## Safety Recommendations:
- It goes without saying that this is a very dangerous program. Don’t run this program unattended unless the game is completely free of Pokémon you want to keep.

## Corner Cases:
**Known Corner Cases:**
- If a box slot is empty, it will be safely skipped.
- If a trade takes too long, the program will self-recover.*
- If no trading partner is found, the program will self-recover.*
- If a trade results in a new Pokédex entry, the program will self-recover.*
- If a trade results in an evolution, the program will self-recover.*
- If a trade results in an evolution and a new move, the program should recover*, but it may take more than one loop.
- This program will tolerate the above errors even at the end of a box.

*In these cases, self-recovery will mean skipping the next trade.

**Untested Corner Cases:**
- Untradable Pokémon: eggs, fused, illegal, etc...
- You get disconnected from the internet while the program is running.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### # of Boxes to Trade:
```
const uint8_t BOXES_TO_TRADE    =   2;
```
This is the number of boxes to trade away.

### Wait for Partner Delay:
```
const uint16_t INITIAL_WAIT     =   30 * TICKS_PER_SECOND;
```
Wait this long for a partner to be found before continuing.

## Advanced Settings:

These are advanced settings. You shouldn’t need to touch these unless something isn’t working and you’re trying to debug it yourself.

### Misc. Timings:
```
const uint16_t TRADE_ANIMATION  =   23 * TICKS_PER_SECOND;
const uint16_t EVOLVE_DELAY     =   30 * TICKS_PER_SECOND;
```
These are pretty self-explanatory. You shouldn’t need to change them. 


