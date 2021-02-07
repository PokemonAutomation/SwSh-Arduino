# GodEggItemDupe

Duplicate items using the God Egg/MissingNo.

*Keep in mind that the God Egg is considered a form of hacking since there is no known way to obtain it without someone having a hacked Switch.*

## Instructions:
- Casual mode is off.
- Your text speed must be set to fast.
- The “Send to Boxes” option must be set to “Manual”.
- Your bike must be fully upgraded.
- You must have the God Egg and a Ditto deposited at the Route 5 daycare center.
- Your party is full.
- Everything in your party is releasable. (no eggs or fused Pokémon)
- The cursor in the menu is over the Town Map.
- You must be on Route 5.
- You must be on your bike.
- You must be in the overworld. (not in the menu)
- There is nothing in front of you that can be interacted with.
-	Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

*If you are playing in Japanese or Italian, you need to [set a flag](../Appendix/GlobalSettings.md#japanese-egg-fetching) or this program will not work.*

The program will clone each Pokémon in your party, take its item, and release it. Then it repeats the process forever.

## Box Setup:
- The entire 1st column of the current box must be empty.
- Your party has 6 throw-away Pokémon* - each holding an item you wish to duplicate.
- All 6 Pokémon* in your party are releasable. (not an egg, not a fused mon)

*If you don't want to clone items on all 6 Pokémon in your party, you can set `PARTY_ROUND_ROBIN` to cycle through fewer Pokémon/items.

## Strongly Recommended:
- Have the Oval Charm.
- The Ditto and the God Egg should have different OTs.

## Safety Recommendations:
- Don't leave any Pokémon you care about in the game. This program releases Pokémon and has been observed to fail in a way that saves the game.
- If you do need to leave Pokémon you care about, keep them out of the 1st column of any box.

## Serial Output:

More on: [Serial Communication](../SerialCommunication.md)

This program outputs the number of fetch attempts. This can be read using the Device Logger.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

In addition to the main options below, there are more [global options](../Appendix/GlobalSettings.md) that can be configured if you encounter problems.

### Fetch Attempts:
```
const uint16_t MAX_FETCH_ATTEMPTS = 10000;
```
Make this many attempts to fetch and duplicate an item.

### Party Round Robin:
```
const uint8_t PARTY_ROUND_ROBIN     =   6;
```
Round-robin through this many party Pokémon. By attaching different items to different Pokémon in your party, you can duplicate different items in the same run. Thus it can clone up to 6 different items in each run.

Examples:
- If set to 1, it will only clone the item held by the 1st party member.
- If set to 2, it will alternate cloning items held by the 1st and 2nd party members.
- If set to N, it will clone the items held by the 1st N members in your party in a round-robin fashion.
This option doesn't increase the speed of the item duplication. It merely gives you more variety. If you run the program unattended overnight, you may get around 300 of the same item. By setting this parameter, you can instead get 50 of 6 different items.

### Detach Item:
```
const bool DETACH_BEFORE_RELEASE    =   false;
```
When you release a Pokémon, the item automatically detaches and goes to your inventory. But certain items (like Rusted Sword/Shield) will prevent you from releasing the Pokémon.

If you are duplicating such items, you must set this to true.





