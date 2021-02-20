# AutoHost-MultiGame

This is a multi-game version of [AutoHost-Rolling](AutoHost-Rolling.md).

*Don’t use this program until you have used AutoHost-Rolling and are familiar with all its options. This program is significantly more complicated to setup.*

This program will auto-host across multiple game saves with different user profiles. In short, you specify a list of user profiles and auto-host settings. The program will then run down this list and auto-host each game accordingly. Once it has finished hosting everything on the list, it starts from the beginning again.

Other than that, this program has all the same features as AutoHost-Rolling. Some settings can be customized per game save, others are global and apply to everything.

If you have 8 user profiles and the ability to play both Sword and Shield without changing cartridges, you can theoretically host up to 16 dens with this program.

**Important Warning:**

*All auto-hosts carry a risk of destroying the den that is being hosted. The failure case is an error that causes the program to clear the raid and drop a new wishing piece. Dropping a wishing piece is a hard-save and cannot be reversed via backup save.*

If you care about your den, get rid of all your wishing pieces. They are easy to get back later with watt farming.

**Instructions:**
- You must have system time unsynced.
- All participating saves must have casual mode off.
- All participating saves must have their text speed set to fast.
- Make sure you have a strong internet connection. (if hosting online)
- All participating saves must be saved in front of a wishing piece den with watts collected.
- All participating saves should be in a location that is safe from getting attacked by wild Pokémon.
- If you are hosting from one game version only (Sword or Shield), it must be the 1st slot in the games list.
- If you are hosting from both Sword and Shield, they must be in slots 1 and 2 of the games list.
- You must have no games running.
-	Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

*If starting the game requires checking the internet (because it is digital on a non-primary Switch), you will need to open up `PokemonSettings.c` and change `START_GAME_REQUIRES_INTERNET` to true.*

*If any den has uncatchable Pokémon (like Mewtwo or Zeraora), you need to set a flag to bypass that extra prompt. See Uncatchable Pokémon Prompt.*


## Serial Output:

More on: [Serial Communication](../SerialCommunication.md)

This program outputs the number of raids hosted. This can be read using the Device Logger.

## Game List:

This is the important part of the multi-game autohost since it is where you specify the list of games and what settings to host within each game.

![](images/AutoHost-MultiGame-0.png)

This example shows 2 games running with different settings. The 1st game runs on user #2 with the usual 3-day roll. The 2nd game runs on user #3 as a hard-locked den with a 1st turn move select with dynamax.

In other words, there is a quite a bit of customization that can be done for each game.

## Per-Game Options:
These options can be customized per game.

### Game Slot Position:
```
.game_slot      =   1,      //  Game slot at start of program. (must be 1 or 2)
```
If you are hosting from one game version only, set this to 1. You don’t need to read any further.
If you are hosting from both Sword and Shield, set this to the game slot of the version when the program starts.

For example:
- If you want to host on Sword and Sword is the 1st slot in the game list when the program starts, set to 1.
- If you want to host on Shield and Shield is the 2nd slot in the game list when the program starts, set to 2.

When hosting from both Sword and Shield, the games will swap position each time the program starts the 2nd game. This program knows this and will keep track of their positions. Thus, the slot that you specify is when the program starts, not the slot it will be at when the auto-host reaches that point.

### User Slot Position:
```
.user_slot      =   1,      //  User # to host from.
```
This is the [user profile](../Appendix/UserSlotNumber.md) for the user that will be hosted.

### Backup Save:
```
.backup_save    =   false,  //  Load backup save instead of normal reset.
```
If set to true, the game will load backup save upon soft-reset.

The idea here is to roll forward from the save frame to the shiny frame. Once on the shiny frame (with the desired softlock), you enter and exit the camp to setup a backup save on the shiny frame. That way, you can load the backup save on the shiny frame while leaving the real save safely 3 or more frames before
.
This option only makes sense when `SKIPS = 0`.

### Catchability:
```
.always_catchable   =   true,   //  Pokemon in this den are always catchable.
```
Some dens have uncatchable Pokémon (i.e. Mewtwo or Zeraora). If the den has any such uncatchable Pokémon, you must this to false. If the den has uncatchable Pokémon, but it is hard-locked in a way that prevents any of them from showing up while rolling or hosting, then it is safe to leave this as true.

### Frame Skips:
```
.skips          =   3,      //  # of frame skips to roll before hosting.
```
This option sets how many frames to skip before hosting. Set to 0 if either hard-locked or backup save soft-locked on the Pokémon to host. Otherwise, set this to the # of frames behind the target you are saved. In most cases, this will be 3 frames. But sometimes people will save further back on high-value dens as a safety against accidental roll-over.

### Accept Friend Requests:
```
.accept_FRs     =   true,   //  Accept friend requests.
```
Set to true if you wish to accept friend requests for the user for this den.

### First Move Select:
```
.move_slot  =   0,      //  If 0, don't select a move. Otherwise select this move slot.
.dynamax    =   true,   //  If 1st move select is enabled, dynamax as well.
```
This is a silly feature that lets you choose a first move before resetting the game.

If `.move_slot` is 0, no first move is selected and the program resets as usual.

Otherwise, the move slot if the slot # for the move (1 = first move). The flag `.dynamax` will let you dmax/gmax the Pokémon as well.

### Additional Raid Delay:
```
.post_raid_delay    =   0 * TICKS_PER_SECOND,   //  Extra wait time after each raid.
```
If you are farming a Pokémon and the time between raids is too short to join consecutive raids, use this to add time between raids. This extra wait time is done in the Switch Home after closing the game after a raid.

## Global Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_SLOW`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-slow) to bypass the system update window.

In addition to the main options below, there are more [global options](../Appendix/GlobalSettings.md) that can be configured if you encounter problems.

All options here are global and will be applied to all the participating save files.

### Raid Code:
```
const uint8_t RANDOM_DIGITS     =   0;
const char* RAID_CODE           =   "1280 0000";
```
See [Raid Code Entry](../Appendix/RaidCode.md).

### Host Online:
```
const bool HOST_ONLINE          =   true;
```
Set this to true if you want to host online and false if you want to host locally.

### Start Time:
```
const uint16_t LOBBY_WAIT_DELAY =   60 * TICKS_PER_SECOND;
```
Wait this long in the lobby before starting the raid. Thus the start time is 3:00 minus this value. The default is to wait 60 seconds which starts the raid at 2:00.

### Accept Friend Requests for Future Games:
```
const uint8_t FR_FORWARD_ACCEPT =   1;
```
While hosting the current den, accept friend requests for a future den.
- If 0, accept friend requests for the current den.
- If 1, accept friend requests for the next den to be hosted.
- If 2, accept friend requests for the den that will be hosted 2 dens later.
- ...

The motivation here is that there is a significant delay from when you accept a friend requests to when the person can see the stamp. If you are accepting FRs for the den that’s currently being hosted, the user that just got accepted may need to wait until the auto-host loops around the entire list of dens and returns the current one. This can take a very long time if you are hosting a lot of dens.

This option lets you shift the order of the FR accepts so that the accepted FRs become relevant much sooner.

### Rollover Prevention:
```
const uint32_t TOUCH_DATE_INTERVAL = (uint32_t)4 * 3600 * TICKS_PER_SECOND;  //  4 hours
```
If none of the dens are rolling (`SKIPS = 0`), the date will advance naturally. This means that the dens being hosted will eventually roll over. To prevent this, the auto-host will periodically touch the date at the specified interval.

Set this value to zero to disable the feature. This option is ignored if at least one den has (SKIPS > 0).

### Internet Connection Delays:
```
//  Time from "Connect to Internet" to when you're ready to enter den.
const uint16_t CONNECT_TO_INTERNET_DELAY    =   20 * TICKS_PER_SECOND;

//  "Communicating" when entering den while online.
const uint16_t COMMUNICATING_STANDBY_DELAY  =   8 * TICKS_PER_SECOND;

//  Delay from "Invite Others" to when the clock starts ticking.
const uint16_t OPEN_ONLINE_DEN_LOBBY_DELAY  =   8 * TICKS_PER_SECOND;

//  Time from start raid to reset. (when not selecting move)
const uint16_t RAID_START_TO_EXIT_DELAY     =   14 * TICKS_PER_SECOND;

//  This + RAID_START_TO_EXIT_DELAY = time from start raid to select move.
const uint16_t DELAY_TO_SELECT_MOVE         =   32 * TICKS_PER_SECOND;
```
These are all delays related to your internet connection. You may need to adjust these to ensure the auto-host works correctly.

Try with the defaults first. If things don’t work, then try increasing these timings. Likewise, if your internet connection is very fast, feel free to reduce some of these delays.




<hr>

**Back to:**
- [Project Home](/README.md)
- [Documentation Home](/Documentation/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
