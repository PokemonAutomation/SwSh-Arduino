# Shiny Hunt Autonomous - Overworld

This is the "overworld encounter bot". It is the fastest and most advanced of the autonomous encounter bots that this package currently has.

This program will randomly seek out and encounter overworld Pokémon until it finds a shiny.

- No calibration is needed. This program will detect a shiny from its animation.
- When a shiny is encountered, this program will save a video of the encounter.
- This program will keep track of encounter statistics.

This program is still in development. All features are subject to change. The program currently does not work in Glimwood Tangle. If you want to hunt authentic Sinistea, do to the Old Cemetery in the Crown Tundra.

**Demo Video:** https://cdn.discordapp.com/attachments/755635697737531544/828071762595807282/2021-04-03_19-50-51.mp4

<img src="images/ShinyHuntAutonomous-Overworld.jpg" width="800">

## Instructions:
- Video resolution is 1280 x 720 or higher. Shiny detection is not reliable at low resolutions.
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- Your lead Pokémon is not following you around. (Applies to Isle of Armor and Crown Tundra)
- You are standing in a grassy area with overworld spawns.
- You must be zoomed out to maximize the view.
- You are not on your bike.
- You must be saved in the above position. The program will reset if it gets stuck.
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

**Recommended for Performance:**
- Have the Shiny Charm. This triples the chance to find a shiny.
- Your lead Pokémon does not have high happiness.
- Your lead Pokémon does not have an ability that activates upon entry to battle.

When the a shiny is found, the program will save a video of the encounter. Then it will go to the Switch home to idle.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

There is no option to search only for a square shiny. Nearly all shinies are square and only 15/65536 are star. Therefore it is infeasible to hunt for star shiny.

### Go Home when Done:

After finding a shiny, go to the Switch Home to idle. Turn this off for unattended streaming so that your viewers can see the shiny.

### Prioritize Exclamation Points:

Given multiple options, prefer those with exclamation points. This prioritizes random grass encounters and Pokémon that flee.

### Enable Circling:

After moving towards a Pokémon, make a circle. This increases the chance of encountering the Pokémon if it has moved or if the trajectory missed.

### Maximum Move Duration:

Maximum Move Duration:</b><br>Do not move in the same direction for more than this long. If you set this too high, you may wander too far from the grassy area.

### Watchdog Timer:

Reset the game if you go this long without any encounters. This allows the program to recover if it gets stuck.

Be aware that open reset, all existing spawned overworld Pokémon will have the same stats from before. Thus they will be repeat encounters.

### Exit Battle Time:

After running, wait this long to return to the overworld.

### Time Rollback:

Every this many hours, rollback the time by this many hours. This keeps the time constant to prevent the weather from changing. It also allows you to target time-specific marks. Set this to zero to disable this feature.

<hr>

**Back to:**
- [Project Home](/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)




