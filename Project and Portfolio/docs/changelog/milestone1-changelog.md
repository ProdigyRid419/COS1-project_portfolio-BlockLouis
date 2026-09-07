</> Markdown



\# Milestone 1 Changelog



\## Project Structure

\-	Created separate dev/src, dev/include, and dev/support folders.

\-	Created docs/validation and docs/changelog folders.

\-	Added an images folder for development and testing screenshots



\## Core Code Structure

\-	Created main.cpp as the program entry point.

\-	Created the Game class with separate header and source files.

\-	Created the Player class with separate header and source files.

\-	Configured the project so source files can include headers from dev/include.



\## Main Menu and Program Flow

\-	Added main menu with Start Game and Exit options.

\-	Added input validation for main menu selections.

\-	Added a StartGame() function to separate game startup logic from the main menu.

\-	Added character naming and stored the name in the Player object.

\-	Added the opening island-survival narrative.

\-	Added a looping Camp menu that returns after actions unless Exit Game is selected.



\## Player State and Survival Stats

\-	Added starting values for Temperature, Health, Hunger, Hydration, Stamina, and Sanity.

\-	Added getter functions for each survival stat.

\-	Added a ViewStatus() function to display the current player stats.

\-	Added temperature labels for Cold, comfortable, and Hot conditions.



\## Sleep Functionality

\-	Added a Sleep() function to the Camp menu.

\-	Added player functions to decrease Hunger and Hydration during sleep.

\-	Sleep currently lowers Hunger and Hydration by 10.

\-	Added checks to prevent Hunger and Hydration from dropping below 0.

\-	Added critical-state warning messages when Hunger or Hydration reaches 0.



\## Testing and Validation

\-	Tested successful compilation in Debug x64.

\-	Tested main menu Start Game and Exit branches.

\-	Tested invalid menu input handling.

\-	Tested character naming, including names with spaces.

\-	Tested Camp menu looping and exit behavior.

\-	Tested View Status output.

\-	Tested Sleep updating Hunger and Hydration values.

\-	Saved progression and validation screenshots in the images folder.



\## Design Decisions and Changes

\-	Moved character naming into the Start Game flow instead of keeping it as a separate main menu option.

\-	Kept main.cpp minimal by moving program flow into the Game class.

\-	Stored player data inside the Player class and accessed it through getters and setters.

\-	Defined Temperature on a 0-100 scale with 50 as the normal baseline.

\-	Kept Sleep simple for Milestone 1 by decreasing Hunger and Hydration by 10.

\-	Kept critical Hunger and Hydration consistent with planned survival system: reaching 0 does not directly kill the player but will later cause Health loss.



\## Next Steps

\-	Continue expanding the Camp menu and survival systems.

\-	Begin implementing the inventory system.

\-	Add the fixed 10-slot personal inventory.

\-	Add dedicated equipment slots for Gear, Spear, Bow, Arrows, Axe, and Pickaxe.

\-	Begin building the location and exploration structure.

\-	Add time progression and additional survival-stat changes in a later milestone.

\-	Continue testing features as they are implemented.

