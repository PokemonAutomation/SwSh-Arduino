# PABotBase

Pokémon Automation Bot Base (PABotBase) is not a regular program that you just run on your Arduino or Teensy. It is a server that listens to and executes commands sent over serial connection.

More on: [Serial Communication](../SerialCommunication.md)

PABotBase allows a computer to control your Switch. So you can write programs on a computer to run your Switch. This has several advantages:
- A computer is not restricted by the limited hardware capability of an Arduino or Teensy.
- A computer has easy access to input such as video and sound from a capture device.
- A computer can control multiple devices (and thus Switches) at once.

Thus, PABotBase will facilitate the development of feedback automation that will allow the automation of things that are otherwise difficult or impossible to do with just blind automation.

As of this writing, PABotBase itself is usable and production-ready. But the client-side applications that utilize it are still in development. Thus, there isn’t much to see right now.

If you are interested in the development of the client-side applications, please join [our Discord server](https://discord.gg/cQ4gWxN) and head over to the #development-chat channel.

## Instructions:

None. Once you have flashed PABotBase into your Arduino/Teensy, just plug it into the your Switch and it will begin listening to serial commands. Where you should be on the Switch will be whatever the client-side program needs.
