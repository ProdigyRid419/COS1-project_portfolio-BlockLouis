\# Milestone 4 Changelog



\## Features Added



\-	Health damage from starvation, dehydration, and spider attacks.

\-	Basic and Improved Bandage crafting and healing.

\-	Spider combat with spear attacks, selectable arrow types, arrow consumption, misses, and retaliation.

\-	Beginning-of-day checkpoints and death recovery.

\-	A single save-game system preserving current progress and the daily checkpoint.

\-	Silk Rope crafting and raft construction, provisioning, and island escape.

\-	Tool and waterskin upgrades that require the previous equipment tier.

\-	Vine and Leather gear crafting and protection against temperature-related survival penalties.

\-	Five weather types that change randomly between day periods.

\-	Sanity loss from prolonged wakefulness and restoration through sleep.

\-	Low-sanity hallucination messages and misleading status displays that leave actual stats unchanged.



\## Refactoring and Design Improvements



\-	Created DailyCheckpoint to group player and world state for death recovery and saving.

\-	Extracted RunCampLoop() so new and loaded games share the same gameplay loop.

\-	Added class-specific Save() and Load() methods, coordinated through SaveSystem.

\-	Used temporary objects to validate loaded data before replacing active game state.

\-	Separated raft construction and weather behavior into dedicated Raft and Weather classes.

\-	Expanded dedicated arrow storage into separate Flint, Stone, and Metal Arrow slots.

\-	Extended ProcessTime() to coordinate weather changes, temperature penalties, awake time, and daily checkpoints.

\-	Used local stat copies for misleading sanity displays without changing the player's actual values.



\## Bug Fixes and Usability Updates



\-	Fixed location menus continuing after the player's health reached zero.

\-	Added health checks after travel, sleep, and rest to stop actions after death.

\-	Corrected a reversed save-result check that prevented saving discovered locations.

\-	Added silk-capacity checks before spider combat.

\-	Prevented displayed spider health from dropping below zero.

\-	Corrected temperature labels to match cold, comfortable, and hot thresholds.

\-	Added clear raft contribution totals, supply requirements, and departure messages.

\-	Added validation for loaded Item IDs, quantities, stats, weather, and resource counts.

\-	Added temporary save files and backup handling to help preserve the previous save if replacement fails.





\## Testing and Validation



\-	Successfully built the project throughout development.

\-	Confirmed health decreases when hunger or hydration reaches zero.

\-	Verified bandage healing and inventory-menu integration.

\-	Confirmed death recovery returns the player to the saved daily checkpoint.

\-	Tested saving, loading, and overwriting a save during initial save-system development.

\-	Verified equipment upgrades and waterskin water preservation.

\-	Confirmed all five weather types appear.

\-	Observed sanity decrease after prolonged wakefulness.





