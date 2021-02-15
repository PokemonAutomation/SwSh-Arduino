# Friend Code Adder

Quickly and easily add friend codes. Copy paste friend codes to the program and let it enter them for you.

Demo Video: https://cdn.discordapp.com/attachments/755635697737531544/810360426784227348/FriendCodeAdder.mov

## Instructions

1. Copy paste one or more friend codes into the text box. One per line only. The codes do not need to be formatted in a particular way. Any line with exactly 12 numbers will be considered a friend code. So you can realistically copy-paste entire Discord raid posts and the program will automatically pick out the friend code(s) for ultimate laziness.

<img src="images/friend-code-adder-0.png" height="600">

2. Click away from the text box. The program will automatically remove all the invalid lines and leave behind only the ones that it thinks are friend codes. These friend codes are what the program will attempt to add when it you run it.

<img src="images/friend-code-adder-1.png" height="600">

3. Select the [user slot](../Appendix/UserSlotNumber.md) for the user you wish to add the friend codes to.
4. Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md). If the device is the primary or the only controller attached to the Switch, you can also start the program in the Home menu with the cursor over the first game.

## Notes:

After each friend code, the program will back out to the Switch Home before re-entering the profile for the next code. The purpose of this is to make the program tolerant to all of the following 3 scenarios.

- If the friend code has not been added, it will be requested. The program will then back out the Switch Home.
- If the friend code is already a friend, nothing bad will happen. The program will toggle the best friend status twice and then back out - thus leaving everything unchanged.
- If the friend code has already been requested but not accepted, nothing happens. The program will safely back out and move on to the next code.
