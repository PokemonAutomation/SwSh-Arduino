# MultiGameFossil

MultiGameFossil is a more advanced fossil reviving program that can revive fossils across multiple game saves. Nevertheless, this program can still be used for a single game only.

<img src="images/MultiGameFossil.png" width="800">

## Motivation:

The purpose of a multi-game fossil program is to allow you to go afk for a longer period of time.

Reviving fossils runs at approximately one revive/18.7 seconds. This comes out to about 5 hours for a full game of 960. Unfortunately, 5 hours is not enough to last overnight or a work day. Thus in order to prevent idling and to increase the efficiency of fossils reviving, you must use multiple game saves to get past the 32 box limit of 960 revives.

Thus with 2 games with empty boxes, you can run fossils for 10 hours continuously without needing any attention. This will be enough to last overnight and maybe a day of work. Using even more games will give more flexibility when you aren’t able to revive 960 fossils at a time.

## Instructions:
- All participating saves must have casual mode off.
- All participating saves must have their text speed set to fast. 
- All participating saves must have “Send to Boxes” set to “Automatic”.
- All participating saves must have nicknaming off.
- All participating saves must have at least one of every fossil.
- All participating saves must have the Pokédex entry for the Pokémon they are reviving.
- All participating saves must have spoken to the professor before.
- All participating saves must be saved in front of the professor.
- Each participating save must have enough fossils to run its specified batch.
- If you are reviving from one game version only (Sword or Shield), it must be the 1st slot in the games list.
- If you are reviving from both Sword and Shield, they must be in slots 1 and 2 of the games list.
- You must have no games running.
-	Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

*If starting the game requires checking the internet (because it is digital on a non-primary Switch), you will need to open up `PokemonSettings.c` and change [`START_GAME_REQUIRES_INTERNET`](../Appendix/GlobalSettings.md#start-game-requires-internet) to true.*

Once started, the program will iterate the list specified by “BATCH” in the order they are listed. For each entry, it will enter the game and revive the specified fossil the specified number of times. Once it has finished reviving in that game, it will save the game and move on to the next game. If it is the last entry in the list, it will not save the same and will return to the Switch Home to idle.

## Required Parameters:
- BATCH: You must set `BATCH` to the desired list of games that you wish to use along with which fossil to revive and how many.

## Safety Recommendations:
- Because this program involves entering games, there is a chance that an error can cause it to enter the wrong game. If any of the games are holding dens, it is recommended to save them facing away from the den. The button presses for reviving fossils can easily destroy a den.

## Single Game Usage:
This is the simplest use case and is what is recommended for first-time users.

Example:
```
const Batch BATCH[] = {
    {1, 3, Arctozolt, 960},

    //  DO NOT DELETE THIS
    {0},
};
```
In the example above, the program will enter the 1st game using the 3rd user profile and revive 960 Arctozolts.
More about user profile #’s.

Once it is done, the program will return to the Switch Home to idle. The game will not be saved. Check if you have a shiny (see below), and reset accordingly if not.


## Multi-Game Usage:
This is the more complicated usage scenario. It will require the use of backup saves.
```
const Batch BATCH[] = {
    {1, 3, Arctozolt, 960},
    {2, 6, Dracovish, 960},

    //  DO NOT DELETE THIS
    {0},
};
```
In this example, the program will:
1. Enter the 1st game as user #3, revive 960 Arctozolts, and save the game.
2. Enter the 2nd game as user #6, revive 960 Dracovishes, and return home without saving.

This program will take about 10 hours to run.

The 1st parameter is the game slot position at the start of the program. It must be 1 or 2. If you are only using one version of the game (Sword or Shield, but not both), then set these all to 1.

When reviving from both Sword and Shield, the games will swap position each time the program starts the 2nd game. This program knows this and will keep track of their positions. Thus, the slot that you specify is when the program starts, not the slot it will be at when the program reaches that point.

## Checking if you have Revived a Shiny:

Once you have revived a ton of fossils, you need to check if there are any shinies. There are generally 3 ways to do this:
1. Manually check them one-by-one.
2. Check your Pokédex for the shiny sprite.
3. Save the game, enter Pokémon Home, and filter by shiny.

#1 is pretty self-explanatory. Seriously, don’t do this. It’s time-consuming and error-prone. You won’t want to miss a shiny because you’re impatient and were checking them too quickly.

#2 is a very fast way to check if you have a shiny, but it only works if you don’t already have the Pokédex entry for it. Thus it’s only good for the 1st time you revive the shiny. If you don’t have the shiny sprite in the Pokédex before running the program, but you do afterwards, then you have revived a shiny!

#3 will always work, but requires Pokémon Home and the use of backup saves. Save the game if you haven’t already, then immediately enter Pokémon Home. Pokémon Home lets you filter by shiny – thus you can quickly check if you have revived any shinies. If not, you need to close Home without saving and reload the backup save to recover the fossils. 

## Managing Backup Saves:

When reviving over multiple game saves, all but the last game will be saved. This means that the fossils will have been consumed. In order to recover them, you must use backup saves.

If you don’t know what backup saves or how to use them, look it up online. We won’t re-iterate it here. But as a reminder, you can load a backup save by pressing UP+X+B on the title screen.

The idea here is to hard-save in front of the professor before running the program. That way when you reload a backup save, you will reload the game from just before the reviving began. If you don’t hard-save, you will reload further back – most likely the fly point in front of the Route 6 tent since flying will overwrite the backup save. This is fine too so hard-saving isn’t really necessary.

Hard-saving can be done either by trading, or saving the game through Pokémon Home.

**Common Pitfalls:**
- If you forgot to load the backup save and thus have a game full of non-shiny fossils, DO NOT fly! Flying will overwrite the backup save causing you to lose all the fossils that were used.
- When exiting Pokémon Home, you MUST select “exit without saving changes”. If you exit saving changes, it will hard-save and wipe the backup save even if you made no changes!

## Options:
This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Game List:
```
const Batch BATCH[] = {
    {1, 3, Arctozolt, 960},
    {1, 6, Dracovish, 960},


    //  DO NOT DELETE THIS
    {0},
};
```
This is the list of games to use as described above.

