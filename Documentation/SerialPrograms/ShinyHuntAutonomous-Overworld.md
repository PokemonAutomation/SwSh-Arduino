# Shiny Hunt Autonomous - Overworld

This is the "overworld encounter bot". It is the fastest and most advanced of the autonomous encounter bots that this package currently has.

This program will randomly seek out and encounter overworld Pokémon until it finds a shiny.

- No calibration is needed. This program will detect a shiny from its animation.
- When a shiny is encountered, this program will save a video of the encounter.
- This program will keep track of encounter statistics.

This program is still in development. All features are subject to change. The program currently does not work in Glimwood Tangle. If you want to hunt authentic Sinistea, go to the Old Cemetery in the Crown Tundra.

**Demo Video (Ralts):** https://cdn.discordapp.com/attachments/755635697737531544/828071762595807282/2021-04-03_19-50-51.mp4 <br>
**Demo Video (Authentic Sinistea):** https://cdn.discordapp.com/attachments/780505858613837835/842199538440732672/Shiny_Authentic_Sinistea.mp4

<img src="images/ShinyHuntAutonomous-Overworld.jpg" width="800">
<img src="images/ShinyHuntAutonomous-Overworld-1.jpg" width="800">

## Instructions:
- Video resolution is 1280 x 720 or higher. Shiny detection is not reliable at low resolutions.
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- Your lead Pokémon is not following you around. (Applies to Isle of Armor and Crown Tundra)
- Your lead Pokémon must not be shiny. (this will cause false positive detections)
- You are standing in a grassy area with overworld spawns.
- You must be zoomed out to maximize the view. (needed for accurate trajectory calculation)
- You are not on your bike. (needed for correct trajectory movement)
- You must be saved in the above position. The program will reset if it gets stuck.
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

**Recommended for Performance:**
- Have the Shiny Charm. This triples the chance to find a shiny.
- Your lead Pokémon does not have high happiness.
- Your lead Pokémon does not have an ability that activates upon entry to battle.
- Get rid of all the nearby strong spawns. They tend to pull you away from the grassy area.

When a shiny is found, the program will save a video of the encounter.

## Encounter Type Recommendations:

By default, the program is configured to randomly target everything. Here are some recommendations if you are trying to hunt something specific.

**Grass (Random) Encounters:**

- Mark Priority: `Exclamation Marks Only (Ignore Question Marks)`
- Trigger Method: `Circle 3 times, then whistle 3 times.`

**Overworld Encounters (non-fleeing):**

- Mark Priority: `Question Marks Only (Ignore Exclamation Marks)`
- Trigger Method: `Whistle 3 times, then circle once.` or `Circle 3 times, then whistle 3 times.`

**Overworld Encounters (fleeing):**

Example: Ralts - reacts with exclamation mark, then flees.
- Mark Priority: `Prioritize Exclamation Marks`
- Trigger Method: `Whistle 3 times, then circle once.`

**Overworld Encounters (non-reacting):**

Example: Hattrem - walks up to you, but never reacts with a mark.

- Mark Priority: `Question Marks Only (Ignore Exclamation Marks)`
- Trigger Method: `Circle 3 times, then whistle 3 times.`

**Sinistea (Old Cemetery):**

- Mark Priority: `No Preference`
- Trigger Method: `Circle 3 times, then whistle 3 times.`

**Notes:**

Trigger Methods `Whistle Only` and `Circle Only` are generally not recommended. Though the options are there if you want to experiment.
- `Whistle Only` will get stuck in a large grassy area if there are no Pokémon near you.
- `Whistle Only` combined with `Exclamation Marks Only (Ignore Question Marks)` will get stuck if the Pokémon walk up to you, but don't attack.
- `Circle Only` will get stuck if you manage to get just outside of the grassy area. Normally, whistling will trigger a mark reaction to pull you back to the grass.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

There is no option to search only for a square shiny. Nearly all shinies are square and only 15/65536 are star. Therefore it is infeasible to hunt for star shiny.

### Go Home when Done:

After finding a shiny, go to the Switch Home to idle. Turn this off for unattended streaming so that your viewers can see the shiny.

### Mark Priority:

Prefer exclamation marks or question marks?
- Exclamation Marks Only (Ignore Question Marks)
- Prioritize Exclamation Marks
- No Preference
- Prioritize Question Marks
- Question Marks Only (Ignore Exclamation Marks)

### Trigger Method:

How do you want to trigger Pokémon to react?
- Whistle Only
- Whistle 3 times, then circle once.
- Circle 3 times, then whistle once.
- Circle Only

### Maximum Move Duration:

Do not move in the same direction for more than this long. If you set this too high, you may wander too far from the grassy area.

### Watchdog Timer:

Reset the game if you go this long without any encounters. This allows the program to recover if it gets stuck.

Be aware that upon reset, all existing spawned overworld Pokémon will have the same stats from before. Thus they will be repeat encounters.

### Time Rollback:

Every this many hours, rollback the time by this many hours. This keeps the time constant to prevent the weather from changing. It also allows you to target time-specific marks. Set this to zero to disable this feature.


## Advanced Settings:
These are advanced settings. You shouldn’t need to touch these unless something isn’t working and you’re trying to debug it yourself.


### Exit Battle Timeout:

After running, wait this long to return to the overworld. The program will resume before this time if it detects that that the battle has ended.

### Target Circling:

After moving towards a Pokémon, make a circle. This increases the chance of encountering the Pokémon if it has moved or if the trajectory missed.


<hr>

**Back to:**
- [Project Home](/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)




