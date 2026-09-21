\# Milestone 3 Changelog



\## Features Added



\-	Multiple resources per location with player resource selection.

\-	Tool-gated Hardwood, Tree Sap, Stone, and Metal gathering.

\-	Herbal Grove, Boar Field, Water Spring, and Spider Nest locations.

\-	Spear and Bow based discovery gates.

\-	Crafting recipes for tools, weapons, arrows, reinforced materials, and waterskins.

\-	Boar hunting, carcass processing, meat, and leather rewards.

\-	Water collection and waterskin capacities.

\-	Campfire construction, fuel, and meat cooking.

\-	Hunger, hydration, and stamina restoration.

\-	Resting and zero-stamina action restrictions.

\-	Twenty-slot camp storage with deposit and withdrawal.

\-	Basic Spider encounters with silk rewards.



\## System Design Updates



\-	Location now stores multiple resource objects in a vector.

\-	Location tracks size-based Boar and Spider populations and daily limits.

\-	Crafting stores reusable recipes and ingredients in vectors.

\-	CampStorage was added as a separate class with a fixed 20-slot array.

\-	Inventory now tracks stored water and provides read-only slot access for transfers.

\-	Game routes Boar Fields, Water Springs, and Spider Nests to specialized interaction functions.

\-	Menu now provides reusable crafting, resource, quantity, storage, and location menus.

\-	ProcessTime() coordinates clock advancement, survival drain, campfire fuel, and daily refresh.



\## Refactoring Improvements



\-	Replaced single-resource Location design with a resource vector, allowing one location to manage multiple resource types.

\-	Centralized menu input validation in GetValidatedChoice() to remove duplicated validation logic.

\-	Created AddRecipe() to reduce repetitive crafting-recipe setup.

\-	Centralized time-driven updates in ProcessTime() while leaving time, drain calculations, stat state, fuel, and location state in their appropriate classes.

\-	Split specialized location behavior into VisitBoarField(), VisitWaterSpring(), and VisitSpiderNest() to keep VisitLocation() manageable.

\-	Used temporary object copies for crafting, carcass processing, cooking, and storage transfers to prevent partial updates or item loss.

\-	Used const references when reading vectors, arrays, items, and slots to avoid unnecessary copies.



\## Testing and Validation



\-	Rebuilt the complete Visual Studio solution with zero errors.

\-	Completed nine regression-test groups covering: Menus, Exploration, Discovery Gates, Gathering, Crafting, Specialized Locations, Survival Stats, Camp Storage, Spider encounters, and Daily rollover.

\-	Verified missing tools, insufficient materials, full inventory, empty slots, depleted resources, and zero stamina are handled safely.

\-	Confirmed time costs, survival-stat changes, campfire fuel usage, and daily refresh behavior.

\-	Saved successful build and feature screenshots as images\\milestone3-run.png and images\\milestone3-features.png



\## Next Steps



\-	Expand Spider encounters with spear attacks, bow attacks, arrow consumption, misses, and retaliation.

\-	Create Health damage and restoration.

\-	Create Basic and Improved bandage crafting and healing.

\-	Create Death and game-over behavior.

\-	Create the beginning-of-day checkpoint/reset system.

\-	Create a single save-game system.

\-	Complete final regression testing, documentation, and submission preparation.

\-	Treat gear effects, storage upgrades, and silk rope mechanics as optional stretch goals.





