# EggCombined2

This is the combined egg fetching+hatching program. When used properly, it is nearly as fast as manual hatching.

This program is capable of sustaining upwards of ***1700 eggs/day*** (5120 step) even when including time to perform mass release. Thus this is one of the fastest (if not the fastest) automatic egg hatcher that does not require custom firmware.

The EggCombined programs require setup so they may be less convenient if you are only trying to hatch one or two shinies of a specific species. But if you are hatching for squares, then this is definitely the program for you.

This program requires that you already have a “reservoir” of eggs (recommended at least 3 boxes). You can run [EggFetcher2](EggFetcher2.md) to obtain these eggs.

Starting with this reservoir of eggs, this program will hatch those eggs while simultaneously fetching more eggs. Newly fetched can be hatched within the same run of the program. Thus with just 3 boxes of eggs, you can keep hatching until you run out of box space.

As with the previous version of this program, hatch and fetch rates will rarely be perfectly synced. Thus the reservoir of eggs will slowly increase or decrease as the program runs. So every once in a while, you will need to adjust the number of eggs with EggFetcher2 or [EggHatcher](EggHatcher.md). Advanced users can adjust the fetch rates in this program to keep the reservoir of eggs at the desired size.

Be aware that the complexity of this program makes it inherently less reliable than the regular EggHatcher. Unlike EggHatcher, it does not tolerate early hatching eggs and requires all eggs to hatch at the same time at the specified step count. If you need to clean up a bunch of eggs of unknown remaining step count, use EggHatcher.

<img src="images/EggCombined2.png" width="800">

## Instructions:
- Casual mode is off.
- Your text speed must be set to fast. 
- The “Send to Boxes” option must be set to “Automatic”.
- Nicknaming needs to be off.
- Your bike must be fully upgraded.
- The parents are already deposited at the Route 5 daycare center.
- Your party must have exactly 1 Pokémon.
- The one Pokémon in your party MUST be a flame body (or similar) Pokémon.
- The menu icons are in their default locations:
  - The Town Map must be in the 2nd row on the far left.
  - The Pokémon option must be in the 1st row, 2nd from the left.
- The cursor in the menu is over the "Pokémon" option.
- You must be on Route 5.
- You must be on your bike.
- You must be in the overworld. (not in the menu)
- There is nothing in front of you that can be interacted with.
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

*If you are playing in Japanese or Italian, you need to [set a flag](../Appendix/GlobalSettings.md#japanese-egg-fetching) or this program will not work.*

## Box Setup:
- Place entire boxes filled with eggs consecutively*.
- You must be on the first box of eggs.
- All the eggs that you are hatching MUST hatch at the same time and at the specified # of steps. Eggs are not allowed to hatch early**.

*It is okay to have non-eggs mixed in with eggs. But all boxes that you intend to hatch must be completely filled.

***Do not use this program on partially hatched eggs. Even a single early hatching egg can break the program.*

## Required Parameters:
- `BOXES_TO_HATCH`: You MUST set this to the # of boxes you wish to hatch. Otherwise, you either won't hatch all the eggs you want, or the program goes crazy if you run out of eggs.
- `STEPS_TO_HATCH`: You MUST set this to the correct step-count for the Pokémon you are hatching. If this is set too small, the program will fail and may unintentionally start a trade. (see Precautions)

The program will hatch eggs in batches of 5 (one column at a time). Once a box is complete, it moves to the next box. It will continue until it has hatched N boxes where N is specified by `BOXES_TO_HATCH`.

Newly fetched eggs will be dropped one box ahead of the one that's being hatched. These will spill forward to later boxes as necessary, thus it is possible to set `BOXES_TO_HATCH` to more than what you have. But you will need to monitor the program to make sure it fetches eggs quickly enough to keep up with the hatching.

## Safety Recommendations:
- As a precaution, it is strongly recommended to be offline. In the event that the eggs do not finish hatching before the program enters the storage system, there is a high chance that it will go into YCOMM and start a trade.

## Failure Cases:
- It is safe to run out of box space. If the egg-fetching wraps around and occupies the current column, the program will fail safely by "re-hatching" the same party over and over again until it's done.
- It is NOT safe to hatch an incomplete column due to running out of eggs. This will lead to an incomplete party being loaded which will swallow up newly fetched eggs. These eggs will not hatch at the correct time which will completely break the program.
- It is NOT safe for eggs to hatch early. If an egg hatches during a fetch attempt, it can put the program into an unexpected state.

## Usage Tips:
Coming soon as this program becomes better tested and better documented.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

In addition to the main options below, there are more [global options](../Appendix/GlobalSettings.md) that can be configured if you encounter problems.

### Boxes of Eggs to Hatch:
```
const uint8_t   BOXES_TO_HATCH      =   3;
```
Hatch this many boxes of eggs.

### Egg Step-Count:
```
const uint16_t  STEPS_TO_HATCH      =   5120;
```
The number of steps needed to hatch the eggs. Look up the value on Serebii.

### Fetches per Batch:
```
const float FETCHES_PER_BATCH       =   6.0;
```
For each batch of eggs, attempt this many egg fetches. If this is a non-integer, the program will vary the # of fetches across batches so that they average out to the specified number.

By changing this number you can adjust the fetch rate of eggs. Thus with careful tuning, you can make egg fetching nearly the same speed as hatching.

Since there are 5 eggs per batch, you will need to set this value to more than 5.0 to match the hatch rate since some fetches will fail. The optimal value will depend on the step count and the compatibility of the parents.
Since this program is new, the exact fetch rates that lead to fetch/hatch equilibriums are not yet known. But they are believed to all be between 5.1 and 6.5.

## Advanced Settings:

These are advanced settings. You shouldn’t need to touch these unless something isn’t working and you’re trying to debug it yourself.

### Safety Time:
```
const uint16_t SAFETY_TIME      =   8 * TICKS_PER_SECOND;
```
Additional time added to the spinning. If any shinies are hatched, they will eat into this safety buffer along with any other unexpected slowdowns. Hatching a shiny takes 2 seconds longer than a non-shiny.

If you see that the program is going into Y-COMM or there is less than 5 seconds of extra spinning after the last egg in the batch, please report this as a bug. As a temporary work-around, you can increase this number.

### Early Hatch Safety:
```
const uint16_t EARLY_HATCH_SAFETY   =   5 * TICKS_PER_SECOND;
```
Eggs will not hatch early by more than this period.

### Hatch Delay:
```
const uint16_t HATCH_DELAY      =   88 * TICKS_PER_SECOND;
```
Total animation time for hatching 5 eggs when there are no shinies.

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
