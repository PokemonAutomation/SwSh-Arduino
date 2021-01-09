# BeamReset

Automatically reset a den beam. The purpose is for finding purple beams.

Drop a wishing piece in, check if it’s red or purple. Pause, then reset.

## Instructions:
- Casual mode is off.
- Your text speed must be set to SLOW.
- You must stand in front of an empty den with watts collected.
- You must be facing the center of the den.
- You must be saved in the above position.
-	Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

On each beam, the program will go in-and-out of the game several times to flash the beam and grab your attention. Then it will wait in the Home menu for 5 seconds before it resets the game. If you like the beam, you must stop the program during these 5 seconds.

Depending on your Switch, the weather, the type of beam (red or purple), and your alignment with the den, you may not see a beam immediately. In some cases, you may not see a beam for several in-and-outs.

Red beams will show up faster. Purple beams are slower and will appear after the text starts showing up. If you see no beam before the program returns to the home menu the last time, it is likely a purple beam.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Delay Before Reset:
```
const uint16_t DELAY_BEFORE_RESET = 5 * TICKS_PER_SECOND;
```
Wait in the Home menu for this long before resetting the game.

### Extra Line
```
const bool EXTRA_LINE   =   false;
```
Talking to the den has an extra line in German. Set this to true if this is the case.


