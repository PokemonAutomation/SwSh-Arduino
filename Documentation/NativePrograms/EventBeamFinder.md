# EventBeamFinder

Drop wishing pieces between two dens until you find an event den.

## Instructions:
- Casual mode is off.
- Your text speed must be set to fast.
- Airplane mode must be enabled*. To run docked, undock the Switch, turn on airplane mode, then redock. The Switch will remain in airplane mode after redocking.
- The two dens closest to the Bridge Field daycare must not have any natural beams. Wishing piece beams are okay since they will be despawned.
- The cursor in the menu is over the Town Map.
- You must be in Bridge Field.
- You must be on your bike.
- You must be in the overworld. (not in the menu)
- There is nothing in front of you that can be interacted with.
-	Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

The program will travel back-and-forth between the two dens closest to the Bridge Field daycare center. Each time, it will drop a wishing piece and enter the den to let you view it.

*Airplane mode is required to avoid getting stuck inside a den as well as slowdowns from network traffic/interference.

This program goes back-and-forth between the following two dens:
- **Den 5/46 (Shedinja):** By the trees near the Obstagoon.
- **Den 4/92 (Gmax Orbeetle):** To the right of the Digging Duo.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Delay Before Reset:
```
const uint16_t WAIT_TIME_IN_DEN = 5 * TICKS_PER_SECOND;
```
View the den for this duration before moving on.



<hr>

**Back to:**
- [Project Home](/README.md)
- [Documentation Home](/Documentation/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
