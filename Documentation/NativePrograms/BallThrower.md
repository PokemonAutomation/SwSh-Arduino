# BallThrower

As its name implies, this program automatically throws balls to catch a Pokémon.

This program is intended for a very specific use case - to Beast Ball catch legendaries. It requires a tremendous amount of setup as well as a large supply of Beast Balls (900+).

*Obtaining that many Beast Balls by fully legitimate means is difficult even with automation. Therefore, this program is really only useful to those who have access to God Egg duplication or have joined a hacked 999x raid.*

<img src="images/BallThrower.png" width="800">

## Setup:

This program blindly throws balls without context. Thus the only way it can work is to setup the following:

1. You need to have enough balls to ensure a catch with high probability. (900+ Beast Balls)
2. You need to be able to reduce the opposing Pokémon down to 1 HP with paralysis.
3. The opposing Pokémon can never run out of PP.
4. Your current Pokémon can never get knocked out. (a perfect wall)

### You are sufficiently stocked on balls.

This one is pretty self-explanatory. For a legendary that is paralyzed at 1 HP, a Beast Ball has a 0.86% chance of success. Thus it will take on average 120 balls to catch.

The probability of failing to catch after 999 Beast Balls is about 1 in 4000.

As mentioned before, acquiring that many Beast Balls will difficult without God Egg or CFW.

### Reduce Opposing Pokémon down to 1 HP with Paralysis.

Reducing down to 1 HP will require something with False Swipe. If the opposing Pokémon is a ghost type, you will need to change its type with a move such as Soak or Magic Powder.

Most electric Pokémon can learn Thunder Wave to induce Paralysis. Note that Regieleki is an electric type and therefore cannot be paralyzed until you change its type with Soak or Magic Powder as described above.

### Prevent the Opposing Pokémon from running out of PP.

To do this, you need to trick a Leppa Berry and Skill Swap an item recovering ability onto the opposing Pokémon. This can be done using a Trevenant with the Harvest ability that is holding a Leppa Berry.

<img src="images/BallThrower-0.png" width="400"> <img src="images/BallThrower-1.png" width="400">

Early in the battle, you should send out Trevenant and use both Skill Swap and Trick. This moves the PP-restoring Leppa Berry onto the opposing Pokémon and changes its ability to Harvest so that the berry is restored after use. This prevents it from ever running out of PP.

### Your Current Pokémon can never get knocked out.

Since the program will only be throwing balls, your in-battle Pokémon will never use any moves or any items. Thus it must be able to wall the opposing Pokémon without using moves or items.

How you do this will depend on what you are battling. But generally speaking, this falls into two categories:
1. Completely disable all of the opposing Pokémon’s damaging moves (type immunity + Imprison).
2. Reduce the damage that you take such that passive healing (from Leftovers) is sufficient to stay alive.

Methods to reduce damage taken:
- Train your Pokémon to tank. (level 100, correct nature, EVs in relevant defensive stats)
- The move Soak will change type to remove STAB and enable False Swipe to hit ghost types.
- X Defend and X Sp. Def (whichever is applicable including both)
- Reduce opposing Pokémon attack and/or special attack. (Charm, Eerie Impulse)
- Accuracy/Evasion: Sand Attack, Double Team
- Non-expiring healing moves: Aqua Ring, Ingrain

Noteworthy Support Pokémon:
- Lanturn: Soak, Eerie Impulse, and Thunder Wave
- Gardevoir: Charm, Thunder Wave, Double Team

### Recommended Walls

With the exception of Zapdos, every single legendary in Sword/Shield has a wall that is completely immune to it.

| **Opposing Pokemon** | **Recommended Wall** | **Requirements** |
| --- | --- | --- |
| Zacian | Zacian | Imprison, Sacred Sword, Iron Head, Crunch<br>Item: Rusted Sword |
| Zamazenta | Zamazenta | Imprison, Slash, Iron Head, Crunch<br>Item: Rusted Shield |
| Beldum/Metang/Metagross<br>(not legendary, but catch rate 3) | Shedinja |  |
| Regirock | Golurk, Runnerigus, or Alolan Marowak | Imprison, Stone Edge |
| Regice | Shedinja |  |
| Registeel | Shedinja |  |
| Regieleki | Shedinja |  |
| Regidrago | Shedinja or Mimikyu |  |
| Cobalion | Shedinja |  |
| Terrakion | Golurk, Runnerigus, or Alolan Marowak | Imprison, Stone Edge |
| Virizion | Shedinja |  |
| Keldeo | Shedinja |  |
| Articuno (Galar) | Articuno (Galar) | Imprison, Freezing Glare, Hurricane, Psycho Cut |
| Zapdos  (Galar) | Zapdos  (Galar) | Nature: +Def<br>IVs: 31 HP, 31 Def<br>EVs: 252 HP, 252 Def<br>Item: Leftovers |
| Moltres  (Galar) | Moltres  (Galar) | Imprison, Fiery Wrath, Hurricane<br>(Requires support to remove dark type from Moltres.) |
| Calyrex (Ice) | Shedinja |  |
| Calyrex (Ghost) | Calyrex (Ghost) | Imprison, Astral Barrage, Giga Drain, Psychic |

## Instructions:
- Casual mode is off.
- Your text speed must be set to fast.
- The “Send to Boxes” option must be set to “Automatic”.
- If any Pokémon in your party is not level 100, make sure they cannot level up or learn any abilities should they level up after catching the opposing Pokémon.
- Your cursor in the menu must be on the Pokédex. This needs to be done before the battle. For Sword of Justice encounters, the cursor will be over the Pokémon Camp which should still work (but is currently untested).
- You are fully stocked on Beast Balls or whatever ball you intend use.
- Set everything up: (previous section)
  1. Opposing Pokémon is paralyzed at 1 HP.
  2. Opposing Pokémon is holding a Leppa Berry and has the Harvest ability.
  3. Your walling Pokémon is out and properly setup to wall the opposing Pokémon.
- The last used ball is the one you are trying to catch with.
- Your cursor in battle needs to be over "Pokémon".
- Start the program in the Change Grip/Order Menu.

The program will keep throwing balls until it catches, you run out of balls, or you die. Once it catches, it will return to the overworld. Then it will either trap itself inside the Pokédex or enter and exit the Pokémon Camp.

## Options:

This program does not support avoiding the system update window.

This program has no program-specific configuration options.




<hr>

**Back to:**
- [Project Home](/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
