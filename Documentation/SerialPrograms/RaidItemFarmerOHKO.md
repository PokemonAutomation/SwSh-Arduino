# Raid Item Farmer (OHKO)

Farm items from max raids that can be one-hit-KO'ed. ***This program requires at least 2 Switches each with serial connections.***

Use Cases:
- Farm Exp Candies off of a Shedinja raid.
- Farm Dynite Ore off of a baby Crown Tundra or promo den.

This program is not restricted to raids that can be OHKO'ed. By adjusting the appropriate timings, it can be used to farm any raid that can be finished in one turn. For example, 3-star Delibird can be one-turned using a team of Zacians for a faster method of farming Dynite Ore.

Demo Video: https://cdn.discordapp.com/attachments/755635697737531544/814164114305581106/Candy_Farmer.mov

<img src="images/CandyFarmer.png" height="600">

## Instructions

- Casual mode is off.
- The hosting Switch is the upper-left Switch.
- There are no other Switches nearby that can produce stamps. (watch out for auto-hosts!)
- Hosting Switch: The first move of the lead Pokémon must be faster than the raid Pokémon.
- Hosting Switch: The first move of the lead Pokémon must OHKO the raid Pokémon.
- Hosting Switch: You are standing in front of a den containing Shedinja or something that can be OHKO'ed.
- Hosting Switch: There are no watts in the den.
- Hosting Switch: You are either saved in this position, or softlocked using the backup save method.
- Raiding Switches: The cursor is over the Pokédex. (safeguard in case it fails to join the raid)
- Raiding Switches: Send to Boxes is set to Automatic. (safeguard in case it catches the Pokémon)
- Raiding Switches: The default Poké Ball is a low value ball. (safeguard in case it tries to catch the Pokémon)
- Raiding Switches: You are in the overworld and safe from being attacked.
- Raiding Switches: There is nothing in front of you that can be interacted with.
- All Switches: Whoever attacks first must be able to one-hit-KO (OHKO) the Pokémon.
- All Switches: Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

Additional Recommendations:
- Avoid using any Pokémon that have activating abilities. This adds delay and may require adjusting the default timings.


## Options

Most of the options are self-explanatory timings which we won't cover. The program already provides descriptions for them.

### Load Backup Save:

Set to false if the host is saved on the Pokémon that is to be farmed. If the host is softlocked (using the backup save method), set this to true.

See [AutoHost-Rolling](../NativePrograms/AutoHost-Rolling.md) for more details on backup softlocks.

### Raid Start to Attack Delay:

Increase this if you need to use Pokémon that have activating abilities. For example: Using Zacian against Delibird.

### Attack to Catch Delay:

Increase this if you are farming something that cannot be OHKO'ed, but can still be one-turned. For example: Using multiple Zacians against Delibird.

### Rollover Prevention:

This program does not touch the date, but requires that the host stay on the current date frame. Thus after 24 hours, the day will rollover and change the Pokémon that is being hosted. To prevent this, the hosting Switch will periodically touch the date at the specified interval.

Set this value to zero to disable the feature.


<hr>

**Back to:**
- [Project Home](/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
