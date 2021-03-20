# Global Settings

This section covers all the common global settings in `FrameworkSettings.c` and `PokemonSettings.c`. There are many more advanced settings not documented here which you should not need to touch. They exist mainly for debugging purposes.

## Start Game Requires Internet
```
const bool START_GAME_REQUIRES_INTERNET   =   false;
```
Set this to true if starting the game requires checking the internet. Otherwise, programs that require soft-resetting may not work properly.

If the game is not a physical cartridge and the Switch is not the primary Switch, starting the game will require checking the internet to see if it can be played. If this is the case, set this to true.

Setting this option to true will slow down soft-resetting by about 3 seconds. 

## Tolerate System Update Menu (Fast)
```
const bool TOLERATE_SYSTEM_UPDATE_MENU_FAST =   true;
```
Some programs can bypass the system update menu at little performance cost. Setting this to true enables this.

## Tolerate System Update Menu (Slow)
```
const bool TOLERATE_SYSTEM_UPDATE_MENU_SLOW =   false;
```
Some programs can bypass the system update menu, but will take a noticeable performance hit. Setting this to true enables this.

## Automatic Deposit
```
const bool AUTO_DEPOSIT             =   true;
```
When set to true, all programs will assume that “Send to Boxes” is set to “Automatic”. This slightly improves the speed of the relevant programs.

## Japanese Egg Fetching
```
const bool EGG_FETCH_EXTRA_LINE     =   false;
```
For some languages (namely Japanese and Italian), fetching an egg from the daycare lady has an extra line of text which will normally break the egg programs. If this applies to you, set this to true to make the program bypass that extra line of text.

## Uncatchable Pokémon Prompt Avoidance Method
```
const bool DODGE_UNCATCHABLE_PROMPT_FAST    =   false;
```
Some den Pokémon are uncatchable (example, Mewtwo and Zeraora). When these Pokémon show up in den, there is an extra prompt that is needs to be cleared before you can enter the lobby.

This package provides two methods to clear the extra prompt.
- **Fast Method:** Attempt to avoid the prompt using the fast method of quickly pressing A again.
- **Slow Method:** Attempt to avoid the prompt using a slower method that’s more reliable.

This setting allows you to choose which method to use.

Intuitively, this seems more complicated than it needs to be. Most other programs will avoid the prompt using the 2nd method – quickly pressing A again. However, this method is not reliable.

Some Switches are really fast and some are really slow.
- If the 2nd A press is too early, it may not be able to clear the uncatchable prompt on slow Switches.
- If the 2nd A press is too late, it may enter Switch Pokémon if the Pokémon is catchable on fast Switches.

Empirical evidence has shown that there is no window of time where it is safe to press A that would work on all Switches, or even the majority of Switches.

Therefore, the recommendation is:
1. If you won’t want to deal with this, leave the setting set to false.
2. If you want to make den rolling and lobby entry fast, you try setting this option to true.

If you want to get fancy, you can experiment with `UNCATCHABLE_PROMPT_DELAY` as well.




<hr>

**Back to:**
- [Project Home](/README.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
