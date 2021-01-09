# Pokémon Automation Sword/Shield Scripts

**Version:** 2021-01-09

**GitHub Repo:** https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)

This is the manual for Pokémon Automation’s in-house Arduino programs for Pokémon Sword/Shield. 

This manual assumes that you are familiar with the mechanics of:
  1. **Den Exploits:** frame-skipping, VS-glitch (aka Y-COMM glitch), hosting, etc...
  2. **Breeding:** step-counts, Masuda Method, flame-body, parent compatibility, etc…

If this is your first time using Arduino for Nintendo Switch, watch this [video by brianuuuSonic](https://www.youtube.com/watch?v=y2xFf7e_KSU). The video is quite outdated, but will still provide a lot of background information to get started. Regardless, this manual will also walk you through the entire process from what to purchase to how to set everything up.

If you have questions, feel free to join our Discord server (linked above) for help. Whether you are a beginner figuring out how to get started or an expert, we have plenty of people to help.

<img src="images/server-banner.png" width="800">

## Table of Contents

**General:**
- [Table of Contents](#table-of-contents)
- [What are these Programs?](#what-are-these-programs)
- [**Program List**](ProgramList.md)
- [Version History](VersionHistory.md)

[**Hardware and Recommendations:**](Hardware.md)
- [Arduino or Teensy?](Hardware.md#arduino-or-teensy)

[**How to Use:**](HowToUse.md)
- [Configuring the Programs](HowToUse.md#configuring-the-programs)
- [Building the Hex Files](HowToUse.md#building-the-hex-files)
  - [Method 1: Use the hex generator UI. (Windows only)](HowToUse.md#method-1-use-the-hex-generator-ui-windows-only)
  - [Method 2: Run the BuildAll-xxxx.cmd file. (Windows only)](HowToUse.md#method-2-run-the-buildall-xxxxcmd-file-windows-only)
  - [Method 3: Run the !BuildAllUnix.sh file. (Mac and Linux)](HowToUse.md#method-3-run-the-buildallunixsh-file-mac-and-linux)
  - [Method 4: Run the !FlashUnix.sh file. (Mac and Linux)](HowToUse.md#method-4-run-the-flashunixsh-file-mac-and-linux)
  - [Method 5: Use the makefile.](HowToUse.md#method-5-use-the-makefile)
- [Load the Program](HowToUse.md#load-the-program)
- [Run the Program](HowToUse.md#run-the-program)
- [While a Program is Running](HowToUse.md#while-a-program-is-running)
  
[**Serial Communication:**](SerialCommunication.md)
- [Application Examples](SerialCommunication.md#application-examples)
- [Hardware and Setup](SerialCommunication.md#hardware-and-setup)
  - [Arduino Uno R3](SerialCommunication.md#arduino-uno-r3)
  - [Teensy 2.0](SerialCommunication.md#teensy-20)
  - [Teensy++ 2.0](SerialCommunication.md#teensy-20-1)
- [Software Setup](SerialCommunication.md#software-setup)

**Appendix:**
- [Change Grip/Order Menu](Appendix/ChangeGripOrderMenu.md)
- [Raid Code](Appendix/RaidCode.md)
- [User Slot Number](Appendix/UserSlotNumber.md)
- [Maximizing Switch Stability](Appendix/MaximizingSwitchStability.md)
- [Unattended Shiny-Hunting Programs](Appendix/UnattendedShinyHuntingPrograms.md)
  - [Calibration](Appendix/UnattendedShinyHuntingPrograms.md#calibration)
- [Day Skippers](Appendix/DaySkippers.md)
  - [Common Usage Errors](Appendix/DaySkippers.md#common-usage-errors)
  - [How Many Skips are Remaining?](Appendix/DaySkippers.md#how-many-skips-are-remaining)
  - [Errors and Auto-Corrections](Appendix/DaySkippers.md#errors-and-auto-corrections)
- [Global Settings](Appendix/GlobalSettings.md)


## What are these Programs?

Pokémon Automation (PA)'s programs are a large set of Arduino programs for Pokémon Sword/Shield.

The categories which these programs cover are:
- Date-spam farming: watts, berries, loto ID.
- Den-hunting: date skipping
- Auto-hosting
- Egg hatching
- Other misc. tools

Functionally, there is a lot of overlap with brianuuuSonic's AutoController programs. While the AutoController programs are more user-friendly for beginners, the programs here (by PA) are focused on speed, reliability, and ease of large-scale unattended automation.

| **Program** | **PA's SwSh Scripts (this package)** | **brianuuuSonic's Autocontroller** |
| --- | --- | --- |
| [Day Skipper (JPN)](Programs/DaySkipperJPN-7.8k.md) | 7827 skips/hour (7.8k)<br>7619 skips/hour (original) | 6500 skips/hour (fast mode)<br>6134 skips/hour (default mode) |
| [Day Skipper (EU)](Programs/DaySkipperEU.md) | 7541 skips/hour (year 2020)<br>7533 skips/hour (year 2021) | 5006 skips/hour (fast mode)<br>4786 skips/hour (default mode) |
| [Day Skipper (US)](Programs/DaySkipperUS.md) | 7180 skips/hour (year 2020)<br>7173 skips/hour (year 2021) | 5006 skips/hour (fast mode)<br>4786 skips/hour (default mode) | 
| [Watt Farming](Programs/DateSpam-WattFarmer.md) | 6.9 seconds/fetch | 9.1 seconds/fetch|
| [Berry Farming](Programs/DateSpam-BerryFarmer.md) | 13.1 seconds/fetch | 16.0 seconds/fetch|
| [Loto ID](Programs/DateSpam-LotoFarmer.md) | 18.4 seconds/attempt | 20.5 seconds/ attempt|
| [Den Rolling](Programs/DenRoller.md) | 16.4 seconds/skip | 18.0 seconds/skip|
| [Sustained Egg Hatching<br>(5120 step)](Programs/EggCombined2.md) | 1700 eggs/day<br>(2-3 touches/day) | 1300 eggs/day<br>(~6 touches/day)
| [8-Digit Code Entry](Programs/FastCodeEntry.md) | ~0.5 seconds | up to 6.3 seconds |

Performance and efficiency goes beyond the raw benchmarks shown above. For example:
- [PA's fossil program](Programs/MultiGameFossil.md) can revive fossils across multiple game saves to allow overnight runs without the program finishing and the Switch idling. This allows fossils to be run 24/7.
- PA has combined egg fetching+hatching that is almost as fast as manual hatching. More importantly, it can be run 24/7 with little user planning and intervention.

The programs here also emphasize reliability. For example:
- The 7k day skippers are self-correcting and will recover from errors that would normally cause other day skippers to stop working.
- The auto-hosts have multiple safeguards in place to minimize the chances of several catastrophic failure scenarios which have been observed in other programs:
  - Hard-locking or destroying the den.
  - Unintentional link trading or surprise trading.





## History

This project was originally started by Mysticial back in March 2020 as a stand-alone project to add a bunch of functionality that was missing from v3.1.0 of brianuuuSonic's AutoController programs. Since then, the project has been handed over to the Pokémon Automation discord server which now continues its development. Mysticial, the author of first few programs remains part of the development team – but only as a secondary/advisory role.

As of this writing, Pokémon Automation's Arduino programs have been developed independently. With the exception of the LUFA library and the low-level USB descriptors, this project shares no code with and bears no resemblance to any other Arduino Switch programs.

## License

You are free to use and distribute this original package for personal use only.

Do not try to profit off of these programs. It's just a game; keep the money out of it and have fun.

For all other uses, please reach out to the administrators of the Pokémon Automation discord server.

This software is provided "as is" and the developers disclaim all warranties with regard to this software including all implied warranties of merchantability and fitness. In no event shall the developers be liable for any special, direct, indirect, or consequential damages, or any damages whatsoever resulting from loss of use, data or profits, whether in an action of contract, negligence or other tortious action, arising out of or in connection with the use or performance of this software.


