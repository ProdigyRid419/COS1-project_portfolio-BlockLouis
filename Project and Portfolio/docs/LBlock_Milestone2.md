# The Long Lost Isle - Milestone 2 Changelog

## Features Added

- Item and inventory systems:	Created the items needed for inventory interaction and allowed the inventory to store those items.

- Exploration and locations:	Added randomly generated locations and stored them in an array of known locations for future travel.

- Resource gathering:	Allowed the player to gather resources from locations, laying the foundation for the future crafting system.

- Time progression:	Added game-time progression based on actions performed by the player.

- Survival-stat drain:	Allowed survival stats to drain at either a base rate or an accelerated rate based on the player's activity level.

- Integration with the camp menu:	Added the necessary options to the relevant menus so the player can access the new systems.

## Code Structure Updates

- New classes:	Created Item, InventorySlot, DedicatedInventorySlot, Inventory, Location, GameClock, SurvivalDrain, and Menu classes. Each class handles its own responsibility, while the Game class coordinates the systems.

- Game integration:	Updated the Game class to coordinate the player, locations, inventory, time progression, survival-stat drain, and menus. The class now calls the appropriate systems when the player selects an action.

- Player updates:	Updated the Player class to manage the player's survival stats and provide access to the player's inventory. This allows time-based drain to affect the player and gathered resources to be added to the correct inventory.

- Menu organization:	Created Menu.h and Menu.cpp to separate menu display and input-validation logic from the rest of the game. This reduced the amount of menu-related code handled by the Game class and made menu behavior more consistent.

- Inventory structure:	Used std::array to create a fixed inventory containing 10 basic slots and seven dedicated slots for gear and weapons. The inventory system also manages item stacking and limits how many resources the player can carry.

## Usability Improvements

- Clearer feedback:	Added messages that show exactly how many resources the player collected. The game also explains whether the inventory became partially or completely full and how many resources could not be collected.

- Input validation:	Added menu input validation that rejects invalid selections and prompts the player to enter a valid choice. This prevents invalid input from causing incorrect menu behavior.

- Inventory overflow handling:	Updated resource gathering so resources that cannot fit in the inventory are returned to the location. This prevents resources from being permanently lost when the player's inventory is full.

- Menu navigation:	Added consistent options to the main, camp, exploration, and inventory menus. This makes the new systems easier for the player to find and use.