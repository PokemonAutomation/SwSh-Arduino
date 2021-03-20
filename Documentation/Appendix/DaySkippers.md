# Day Skippers

Back to:
- [DaySkipperJPN](../Programs/DaySkipperJPN.md)
- [DaySkipperEU](../Programs/DaySkipperEU.md)
- [DaySkipperUS](../Programs/DaySkipperUS.md)
- [DaySkipperJPN-7.8k](../Programs/DaySkipperJPN-7.8k.md)

## Common Usage Errors

Be careful when setting the starting date after you activate the Y-COMM glitch. Skipping forward will cause an extra skip to happen. This does not apply to the EU and US skippers since they override the date anyway.

Do not run this day skipper in the Wild Area even if it is for very few skips where you don't expect to crash the game. Skipping in the Wild Area has been observed to miss LOTs of frames.

Do not run this day skipper in the Isle of Armor Dojo. Apparently, it is not "indoor enough" and may miss skips on some Switches.

## How Many Skips are Remaining?

All the day skippers in this package will flash the LEDs on the Arduino/Teensy to indicate roughly how many skips are left. This can give you an idea of how much longer you need to wait. It can also tell you if there are obvious misconfigurations. (For example, you want to do 10,000 skips, but the lights indicate over 100,000.)

The table below tells you how quickly the lights turn on and off for each bracket of remaining skips. For example, if you have 15,000 skips remaining, the lights will turn on for 5 seconds, then turn off for 5 seconds.

| **Skips Remaining** | **Flash Interval (seconds)** |
| --- | --- |
| 0 | LEDs always on |
| 1 - 20 | 1/32 |
| 21 - 50 | 1/16 |
| 51 - 100 | 1/8 |
| 101 - 200 | 1/4 |
| 201 - 500 | 1/2 |
| 501 - 1,000 | 1 |
| 1,001 - 2,000 | 2 |
| 2,001 - 5,000 | 3 |
| 5,001 - 10,000 | 4 |
| 10,001 - 20,000 | 5 |
| 20,001 - 50,000 | 6 |
| 50,001 - 100,000 | 7 |
| 100,001 - 200,000 | 8 |
| 200,001 - 500,000 | 9 |
| > 500,000 | 10 |

## Errors and Auto-Corrections

This package has 4 high-speed date skippers – one for each of the 3 different date formats. There is also a 2nd Japanese date skipper that is faster.
- [**DaySkipperJPN:**](../Programs/DaySkipperJPN.md) YYYY/MM/DD – hh:mm
- [**DaySkipperEU:**](../Programs/DaySkipperEU.md) DD/MM/YYYY – hh:mm
- [**DaySkipperUS:**](../Programs/DaySkipperUS.md) MM/DD/YYYY – hh:mm – AM/PM
- [**DaySkipperJPN-7.8k:**](../Programs/DaySkipperJPN-7.8k.md) YYYY/MM/DD – hh:mm

Like other fast day skipper implementations, these skippers are not 100% reliable. They can make errors. In stable environments, these skippers can run flawlessly for many days straight. But in unstable environments they can make multiple errors in a day or have bursts of many errors in just an hour.

The JPN and EU day skippers are the fastest and most reliable. The US skipper is slower and has been observed to be significantly less stable possibly due to its longer scrolling sequence.

Day skipper errors fall into two categories:
1. **Missed Skip:** A single skip is missed, but the program continues to normally.
2. **Trapping: The** program gets stuck toggling the time-sync.

Missed skips are harmless besides missing the skip. The program continues normally as if nothing happened. But when it finishes, it will finish short of the target number of skips. These are the most common errors.

However, trapping errors are the more severe since they prevent any further skipping from being done. These happen when an error causes the program to break out of its normal skipping routine and get stuck toggling the time-sync. Thus they are not self-correcting and you can go away for a long time and come back having completed very few skips.

The skippers in this package are different from other day skippers. First, they are more resilient to errors. Minor errors that cause other day skippers to trap will not cause these skippers to trap. Secondly, if a trapping error still manages to happen, the skippers here will self-recover with a periodic routine that puts the program back into the normal skipping state. Needless to say, all the skips that were supposed to happen while being trapped will have been dropped.

While errors will still cause the skipper to fall short of the target, they will not stop the program from skipping. Rest assured that if you leave one of these day skippers running for hours or days, it will still complete the vast majority of skips even if the environment is unstable.

**Notes:**
- **All Skippers:** If the program is stuck toggling the time-sync, it has encountered a trapping error, but has not recovered from it yet. Wait a bit and it will recover when the auto-recovery routine runs.
- **JPN Skipper:** If the hour has changed, it means the program has missed at least one skip.
- **JPN Skipper:** If the month and/or time zone have changed for the JPN skipper, it means that the program has encountered and recovered from a trapping error.
- **JPN Skipper:** If the month has been changed to the current month (due to a trapping error) and is not a 31-day month, the amount of efficiency you lose is negligible. (0.1% for 30-day month, 0.3% for February) So it’s fine to just let it continue unless you have an OCD to fix it or something.






<hr>

**Back to:**
- [Project Home](/README.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
