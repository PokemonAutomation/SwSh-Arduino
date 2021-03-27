# AutoHost-Rolling

This is the all-in-one autohost that can host all of the following:
- Rolling autohosts: Roll a den and host a random Pokémon.
- Hard-locked Dens
- Soft-locked Dens

Functionally, all this program does is repeat the following sequence forever:
1. Roll the den forward by N days.
2. Host the Pokémon.
3. Reset the game.

So to break it down:
- To host a rolling den: Set N to 3 (or more).
- To host a hard-locked den: Set N to zero.
- To host a soft-locked den: Set N to zero and set “BACKUP_SAVE” to true. (see below.)

**Hosting a Soft-lock:**

For auto-hosting we no longer use the method of disconnecting from the raid. Instead we use a safe method involving backup saves. Here’s how it works:

1. Save 3 (or more) frames before the shiny frame.
2. Roll to the shiny and repeat until you get the desired Pokémon.
3. While still in front of the den, enter the Pokémon Camp and leave it. This establishes a backup save on the shiny frame with the current Pokémon.
4. Host as if you are hardlocked. But when you reset, load backup save instead of regular save.
5. When you are done hosting and you want to clear the softlock, just load the game normally. It will load back on the original saved frame that is 3 (or more) frames before the shiny.

This method is safe because it doesn’t do any actual saving. If the backup save is lost, you simply lose the soft-lock. This method also works offline, but it will freeze the raid for about a minute before the raiders can start the battle.

To configure the program to load backup save instead of the regular save, set “BACKUP_SAVE” to true.

*For water dens, you will not be able to camp. However, here are some alternatives:*
1. *Go into Y-COMM, then join and clear a random raid. This will establish a backup save.*
2. *Manually host one raid online and disconnect. When you return to the overworld, it will establish a backup save.*

**Optional Features:**
- Host offline using local communication instead of online.
- Automatically accept friend requests.
- Add a delay between raids to make farming more efficient when you can't clear a raid before the next one starts.
- Select a first move for the hosting Pokémon.
- Troll host and attack your allies for more challenge.

**Important Warning:**

*All auto-hosts carry a risk of destroying the den that is being hosted. The failure case is an error that causes the program to clear the raid and drop a new wishing piece. Dropping a wishing piece is a hard-save and cannot be reversed via backup save.*

If you care about your den, get rid of all your wishing pieces. They are easy to get back later with watt farming.

## Instructions:
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- Make sure you have a strong internet connection. (if hosting online)
- You must be disconnected from internet.
- You must be standing in front of a wishing piece den with watts collected.
- Your location should be safe from getting attacked by wild Pokémon.
- You must be in the overworld.
- You must be saved in the above position.
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

*If starting the game requires checking the internet (because it is digital on a non-primary Switch), you will need to open up `PokemonSettings.c` and change `START_GAME_REQUIRES_INTERNET` to true.*

By default, the program will start the raid at 2:00. Everybody needs to be ready by then or the raid may fail. This can be changed by modifying `LOBBY_WAIT_DELAY`.

The serial version of this program utilizes video feedback to:
1. Start the raid early when the lobby is full and all players are ready.
2. Wait for any players who don't ready up by the start time.

## Serial Output:

More on: [Serial Communication](../SerialCommunication.md)

This program outputs the number of raids hosted. This can be read by the serial programs.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_SLOW`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-slow) to bypass the system update window.

In addition to the main options below, there are more [global options](../Appendix/GlobalSettings.md) that can be configured if you encounter problems.

### Raid Code:
```
const uint8_t RANDOM_DIGITS     =   0;
const char* RAID_CODE           =   "1280 0000";
```
See [Raid Code Entry](../Appendix/RaidCode.md).

### Frame Skips:
```
const uint8_t SKIPS             =   3;
```
This option sets how many frames to skip before hosting. Set to 0 if either hard-locked or backup save soft-locked on the Pokémon to host. Otherwise, set this to the # of frames behind the target you are saved. In most cases, this will be 3 frames. But sometimes people will save further back on high-value dens as a safety against accidental roll-over.

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

### Backup Save:
```
const bool BACKUP_SAVE      =   false;
```
If set to true, the game will load backup save upon soft-reset.

The idea here is to roll forward from the save frame to the shiny frame. Once on the shiny frame (with the desired softlock), you enter and exit the camp to setup a backup save on the shiny frame. That way, you can load the backup save on the shiny frame while leaving the real save safely 3 or more frames before.

This option only makes sense when `SKIPS = 0`.

### Catchability:
```
//  ALWAYS_CATCHABLE    All pokemon in this den are catchable.
//  MAYBE_UNCATCHABLE   There may be uncatchable pokemon.
const Catchability CATCHABILITY     =   ALWAYS_CATCHABLE;
```
Some dens have uncatchable Pokémon (i.e. Mewtwo or Zeraora). If the den has any such uncatchable Pokémon, you must this to MAYBE_UNCATCHABLE. If the den has uncatchable Pokémon, but it is hard-locked in a way that prevents any of them from showing up while rolling or hosting, then it is safe to leave this as ALWAYS_CATCHABLE.

### Accept Friend Requests:
```
const uint8_t FRIEND_ACCEPT_USER_SLOT       =   0;
```
If set to zero, do not accept friend requests. Otherwise, this is the [user profile](../Appendix/UserSlotNumber.md) to accept friend requests for.

Once enabled, the program will automatically accept friend-requests while waiting in the lobby. It will do this multiple times to avoid getting disconnected and to give people more chances to see the code when streaming.

### Additional Raid Delay:
```
const uint16_t EXTRA_DELAY_BETWEEN_RAIDS    =   0 * TICKS_PER_SECOND;
```
If you are farming a Pokémon and the time between raids is too short to join consecutive raids, use this to add time between raids. This extra wait time is done after entering the den, but before entering the code.

### First Move Select:
```
const uint8_t MOVE_SLOT     =   0;
const bool DYNAMAX          =   true;   //  Must set to false if you cannot dmax.
const uint8_t TROLL_HOSTING =   0;      //  0 disables the troll hosting option, 1 attacks the first ally, 2 attacks the second one, 3 attacks the third one. Dynamaxing will disable this option.
```
This is a silly feature that lets you choose a first move before resetting the game.

If `MOVE_SLOT`is 0, no first move is selected and the program resets as usual.

Otherwise, the move slot if the slot # for the move (1 = first move). The flag “DYNAMAX” will let you dmax/gmax the Pokémon as well. 

### Alternate Games:
```
const bool ALTERNATE_GAMES  =   false;
```
If you are able to play both Sword and Shield on the Switch without changing cartridges, this option will let you host both Sword and Shield dens on the same user using the same settings. When set to true, the auto-host will soft-reset into the other game instead of the same game.

Needless to say, Sword and Shield must be the 1st and 2nd game slots in the Switch Home menu.

### Rollover Prevention:
```
const uint32_t TOUCH_DATE_INTERVAL = (uint32_t)4 * 3600 * TICKS_PER_SECOND;  //  4 hours
```
If the den is not rolling (`SKIPS = 0`), the date will advance naturally. This means that the den being hosted will eventually roll over. To prevent this, the auto-host will periodically touch the date at the specified interval.

Set this value to zero to disable the feature. This option is ignored if (SKIPS > 0) since it is unnecessary.

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
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
