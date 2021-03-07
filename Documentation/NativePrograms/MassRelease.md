# MassRelease

MassRelease will release entire boxes of Pokémon. The main use case is getting rid of breedjects and non-shiny fossils.

## Instructions

- Casual mode is off.
- Your text speed must be set to fast.
- You must in the box system.
- The cursor must be over the 1st Pokémon in the box. (top-left corner)
- The cursor must be red. (not blue or green)
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

Once started, this program will release the specified number of boxes consecutively starting from the current box.

## Box Setup:
- Place entire boxes filled with Pokémon to be released consecutively.
- The last box must be full. This program does not tolerate partial boxes.

## Required Parameters:
- `BOXES_TO_RELEASE`: You must specify the number of boxes to release.

## Safety Recommendations:
See [Maximizing Switch Stability](../Appendix/MaximizingSwitchStability.md).

## Options:
This program does not use the global setting to bypassing the system update window. It has its own setting for that. (See below.)

### # of Boxes to Release:
```
const uint8_t BOXES_TO_RELEASE  =   2;
```
This is the number of boxes to release.

### Dodge the System Update Window:
```
const bool DODGE_SYSTEM_UPDATE_WINDOW   =   false;
```
When set to true, the program will dodge the system update window. Do not set this option if the system update window is not present. Unlike other programs, MassRelease will not be able to tolerate the extra button presses if they land in the box system.



<hr>

**Back to:**
- [Project Home](/README.md)
- [Documentation Home](/Documentation/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
