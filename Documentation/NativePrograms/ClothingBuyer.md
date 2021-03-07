# ClothingBuyer

As its name implies, this program will automatically buy clothing.

Note that this program is not particularly efficient. But it will properly handle items that have already been purchased and will eventually clear an entire store regardless of how many items there are in each category.

Preliminary testing suggests that this program takes an hour to buy out the entire Wedgehurst clothing store.

*Be aware that this program will change your clothing. So you may need to fix it when you’re done.*

## Instructions:
- Casual mode is off.
- Your text speed must be set to fast.
- You are in the menu for buying clothing. (Anywhere is fine.)
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

Note that this program does not stop since it does not know when it is done. Therefore you must stop it manually and check to see if it there is anything left to buy.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

### Rotate Categories:
```
const bool CATEGORY_ROTATION    =   true;
```
When set to true, the program will change categories. This allows the program to eventually buy out the entire store, but will make it less efficient when there are categories that are already bought out.



<hr>

**Back to:**
- [Project Home](/README.md)
- [Documentation Home](/Documentation/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
