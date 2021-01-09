# TradeBot

TradeBot is a coded version of [SurpriseTrade](SurpriseTrade.md). The main use case is for hosting giveaways.

The program can sustain a trade every ~103 seconds. Thus it takes almost an hour to process a box. 

This program is experimental and is more suited for high-demand and high-quantity giveaways. As with SurpriseTrade, this program will skip Pokémon if no trade happens. Thus there will be many untraded Pokémon. Likewise, you will need many Pokémon to sustain a giveaway that lasts for a long period of time unattended.

## Instructions:
- Casual mode is off.
- Your text speed must be set to fast.
- Nicknaming needs to be off. (in case of a trade evolution)
- If you are trading online, make sure you have a strong internet connection.
- The cursor in the menu is over the "Pokémon" option.
- You must be in the overworld. (not in the menu)
- There is nothing in front of you that can be interacted with.
- You should be backed into a corner where you cannot travel down or right.
- Your location should be safe from getting attacked by wild Pokémon.
- If you wish to trade online, be connected to the internet before you start the program. Thus you will need to be fast when starting the program or you will be disconnected.
-	Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

Once started, this program will trade the specified number of boxes consecutively starting from the current box.

When the program reaches the end of a box, it will pause for a longer period before moving the next box. This is to ensure that any errors from a preceding trade will have cleared out.

## Box Setup:
-	Place boxes* of Pokémon to be traded consecutively.
-	You must be on the first box.
-	Do not have any untradable Pokémon in these boxes. (no fused Pokémon)

## Safety Recommendations:
- It goes without saying that this is a very dangerous program. Don’t run this program unattended unless the game is completely free of Pokémon you want to keep.

*The boxes do not need to be full. Empty slots are safely skipped, but you will leave the partner waiting for a long time before disconnecting them without trading anything.

## Corner Cases:

**Known Corner Cases:**
- If no trading partner is found, no trade happens and the current Pokémon is skipped.
- If the trade partner is too slow to pick a Pokémon or confirm the trade, the trade will be canceled.
- If the trade partner cancels at any time, the program should back out without issues.
- If a trade results in an evolution, the program will self-recover.*
- If a trade results in an evolution and a new move, the program should recover*.
- This program will tolerate the above errors even at the end of a box.

*In these cases, self-recovery will mean skipping the next trade.

**Untested Corner Cases:**
- If a box slot is empty, it should be safely skipped.
- If a trade results in a new Pokédex entry, the program should self-recover.
- Untradable Pokémon: fused, illegal, etc...
- You get disconnected from the internet while the program is running.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Trade Code:
```
const char* TRADE_CODE          =   "1280 0000";
```
Pretty self-explanatory.

The program will skip non-digit characters. So the space or hyphen separator is optional.

### # of Boxes to Trade:
```
const uint8_t BOXES_TO_TRADE    =   2;
```
This is the number of boxes to trade away.

### Search Delay:
```
const uint16_t SEARCH_DELAY     =   20 * TICKS_PER_SECOND;
```
Wait this long to search for a trade partner before canceling (if no partner found) or proceeding to trade.

### Confirm Trade Delay:
```
const uint16_t CONFIRM_DELAY    =   10 * TICKS_PER_SECOND;
```
Once you select a Pokémon to trade, give the user this long to confirm the trade before you cancel the trade.

### Internet Connection Delays:
```
const uint16_t TRADE_START          =   10 * TICKS_PER_SECOND;
const uint16_t TRADE_COMMUNICATION  =   20 * TICKS_PER_SECOND;
```
Increase these if your internet connection is slow.

## Advanced Settings:
These are advanced settings. You shouldn’t need to touch these unless something isn’t working and you’re trying to debug it yourself.

### Misc. Timings:
```
const uint16_t TRADE_ANIMATION  =   23 * TICKS_PER_SECOND;
const uint16_t EVOLVE_DELAY     =   30 * TICKS_PER_SECOND;
```
These are pretty self-explanatory. You shouldn’t need to change them. 


