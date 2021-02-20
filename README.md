# Pokemon Automation Sword/Shield Arduino Scripts
This is a public distribution mirror for the Pokemon Automation discord server's in-house Arduino programs for Pokemon Sword/Shield.

 - **Latest Native Programs:** [PASwShNativePrograms-20210206.zip](PASwShScripts-20210206.zip?raw=true)
 - **Latest Serial Programs:** coming soon...
 - **Documentation:** [Online Manual](Documentation/README.md), [pdf](User%20Manual.pdf)
 - **Support Discord:**

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)

The latest releases and betas are in the discord server. This repo is merely a mirror that isn't always up-to-date.

-----

These programs for the Arduino can automate various different things in Pokemon Sword/Shield.

These programs are similar to brianuuuSonic's Autocontroller programs. But they are generally faster, more reliable, and have a much smaller risk of killing dens.

## Demo Videos:
 - [7800/hour JPN Date Skipper](https://cdn.discordapp.com/attachments/755635697737531544/755637307167735888/DaySkipperJPN-7.8k.mov)
 - [7500/hour EU Date Skipper](https://cdn.discordapp.com/attachments/755635697737531544/755638422558736434/DaySkipperEU-7.5k.mov)
 - [Unattended SoftReset - Automatically stop on a shiny.](https://cdn.discordapp.com/attachments/755635697737531544/772244388109090817/ShinyTerrakion.mp4)
 - [1 million watts/hour Watt Farmer](https://cdn.discordapp.com/attachments/755635697737531544/755640509376233522/WattFarmer.mov)
 - [Fast Code Entry - Enter any 8-digit code in half a second.](https://cdn.discordapp.com/attachments/755635697737531544/755642709183561789/FastCodeEntry.mov)
 - [Rolling Auto-Host](https://cdn.discordapp.com/attachments/755635697737531544/755891856172253194/RollingAutoHost.mov)

## Program List:

**General Tools:**
- [**TurboA**](Documentation/Programs/TurboA.md) - Endlessly mash A.
- [**MassRelease**](Documentation/Programs/MassRelease.md) - Mass release boxes of Pokémon.
- [**SurpriseTrade**](Documentation/Programs/SurpriseTrade.md) - Surprise trade away boxes of Pokémon.
- [**TradeBot**](Documentation/Programs/TradeBot.md) - Surprise trade with a code for hosting giveaways.
- [**ClothingBuyer**](Documentation/Programs/ClothingBuyer.md) - Buy out all the clothing in a store.
- [**BallThrower**](Documentation/Programs/BallThrower.md) - Blindly throw balls at the opposing Pokémon until it catches.

**Date-Spam Farmers:**
- [**DateSpam-WattFarmer**](Documentation/Programs/DateSpam-WattFarmer.md) - Farm watts. (6.9 seconds/fetch, 1 million watts/hour)
- [**DateSpam-BerryFarmer**](Documentation/Programs/DateSpam-BerryFarmer.md) - Farm berries.
- [**DateSpam-LotoFarmer**](Documentation/Programs/DateSpam-LotoFarmer.md) - Farm the Loto ID.
- [**DateSpam-StowOnSideFarmer**](Documentation/Programs/DateSpam-StowOnSideFarmer.md) - Farm the Stow-on-Side items dealer.
- [**DateSpam-DailyHighlightFarmer**](Documentation/Programs/DateSpam-DailyHighlightFarmer.md) - Farm the daily highlight watt trader in Crown Tundra.

**Shiny Hunting:**
- [**MultiGameFossil**](Documentation/Programs/MultiGameFossil.md) - Revive fossils. Supports multiple saves so you can go afk for longer than 5 hours.
- [**ShinyHunt-Regi**](Documentation/Programs/ShinyHunt-Regi.md) - Hunt for shiny Regi golem legendaries.
- [**ShinyHunt-SwordsOfJustice**](Documentation/Programs/ShinyHunt-SwordsOfJustice.md) - Hunt for shiny Swords of Justice legendaries.
- [**ShinyHuntUnattended-Regi**](Documentation/Programs/ShinyHuntUnattended-Regi.md) - Hunt for shiny Regis. Stop when a shiny is found.
- [**ShinyHuntUnattended-SwordsOfJustice**](Documentation/Programs/ShinyHuntUnattended-SwordsOfJustice.md) - Hunt for shiny SOJs. Stop when a shiny is found.
- [**ShinyHuntUnattended-StrongSpawn**](Documentation/Programs/ShinyHuntUnattended-StrongSpawn.md) - Hunt for shiny strong spawns. Stop when a shiny is found.
- [**ShinyHuntUnattended-Regigigas**](Documentation/Programs/ShinyHuntUnattended-Regigigas.md) - Hunt for shiny Regigigas. Stop when a shiny is found.
- [**ShinyHuntUnattended-Regigigas2**](Documentation/Programs/ShinyHuntUnattended-Regigigas2.md) - A new version of the Regigigas program that is faster.
- [**ShinyHuntUnattended-IoATrade**](Documentation/Programs/ShinyHuntUnattended-IoATrade.md) - Hunt for shiny Isle of Armor trade. Stop when a shiny is found.

**Den Hunting:**
- [**BeamReset**](Documentation/Programs/BeamReset.md) - Reset a beam until you see a purple beam.
- [**EventBeamFinder**](Documentation/Programs/EventBeamFinder.md) - Drop wishing pieces until you find an event den.
- [**DaySkipperJPN**](Documentation/Programs/DaySkipperJPN.md) - A day skipper for Japanese date format. (7600 skips/hour)
- [**DaySkipperEU**](Documentation/Programs/DaySkipperEU.md) - A day skipper for EU date format that.  (~7500 skips/hour)
- [**DaySkipperUS**](Documentation/Programs/DaySkipperUS.md) - A day skipper for US date format that.  (~7100 skips/hour)
- [**DaySkipperJPN-7.8k**](Documentation/Programs/DaySkipperJPN-7.8k.md) - A faster, but less reliable Japanese date skipper. (7800 skips/hour) 

**Hosting:**
- [**DenRoller**](Documentation/Programs/DenRoller.md) - Roll den to the N'th day, SR and repeat.
- [**AutoHost-Rolling**](Documentation/Programs/AutoHost-Rolling.md) - Roll N days, host, SR and repeat. Also supports hard-locks and soft-locks.
- [**AutoHost-MultiGame**](Documentation/Programs/AutoHost-MultiGame.md) - Run AutoHost-Rolling across multiple game saves. (Up to 16 dens!)
- [**FriendDelete**](Documentation/Programs/FriendDelete.md) - Mass delete/block all those unwanted friends from the above.

**Egg Hatching:**
- [**EggFetcher2**](Documentation/Programs/EggFetcher2.md) - Fetch eggs without hatching them.
- [**EggHatcher**](Documentation/Programs/EggHatcher.md) - Hatch eggs from boxes.
- [**EggCombined2**](Documentation/Programs/EggCombined2.md) - Fetch and hatch eggs at the same time. (fastest – 1700 eggs/day for 5120-step)
- [**EggSuperCombined2**](Documentation/Programs/EggSuperCombined2.md) - Mass release breedjects, then run EggCombined2.

**The Forbidden Programs:**
- [**FastCodeEntry**](Documentation/Programs/FastCodeEntry.md) - Force your way into raids by entering 8-digit codes in under 1 second.
- [**GodEggItemDupe**](Documentation/Programs/GodEggItemDupe.md) - Mass duplicate items with the God Egg.

**Other:**
- [**PABotBase**](Documentation/Programs/PABotBase.md) - Control your Arduino/Teensy (and therefore your Switch) from a computer.

