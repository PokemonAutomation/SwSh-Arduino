# EggFetcher2

Fetch eggs into your boxes without hatching them.

This program is used with [EggHatcher](EggHatcher.md) to fetch and hatch eggs. Thus you first fetch a bunch of eggs with EggFetcher, then you hatch them with EggHatcher.

This program is also used to build a reservoir of eggs for running the faster [EggCombined2](EggCombined2.md) and [EggSuperCombined2](EggSuperCombined2.md) programs.

## Instructions:
- Casual mode is off.
- Your text speed must be set to fast.
- The “Send to Boxes” option must be set to “Automatic”.
- Your bike must be fully upgraded.
- The parents are already deposited at the Route 5 daycare center.
- Your party is full and none are eggs.
- The cursor in the menu is over the Town Map.
- You must be on Route 5.
- You must be on your bike.
- You must be in the overworld. (not in the menu)
- There is nothing in front of you that can be interacted with.
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

*If you are playing in Japanese or Italian, you need to [set a flag](../Appendix/GlobalSettings.md#japanese-egg-fetching) or this program will not work.*

## Strongly Recommended:
- Masuda Method: The Pokémon in the daycare are of different languages.
- Have the Oval Charm.
- Have the Shiny Charm.

For parents with neutral compatibility (same species or different OT), this program will fetch a box of eggs every ~15 min. or so.

It is okay to let this program fill all your boxes. If there's no room, you simply will not receive any more eggs. No harm is done.

## Serial Output:

More on: [Serial Communication](../SerialCommunication.md)

This program outputs the number of fetch attempts. This can be read by the serial programs.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

In addition to the main options below, there are more [global options](../Appendix/GlobalSettings.md) that can be configured if you encounter problems.

### Fetch Attempts:
```
const uint16_t MAX_FETCH_ATTEMPTS = 2000;
```
Make this many attempts to fetch an egg. The only reason to set this option is to avoid over-fetching of eggs and clogging up all your boxes.





<hr>

**Back to:**
- [Project Home](/README.md)
- [Documentation Home](/Documentation/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
