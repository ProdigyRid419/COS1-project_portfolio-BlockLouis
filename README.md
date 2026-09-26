
<br>

# Project & Portfolio 1

### Student First & Last Name

Hello my name is Louis Block. I am a student from Florida. The purpose of this repository is to practice development using version control. This work will help me begin to build a portfolio of skills and accomplishment that can be shared in the future.

<br>

## 📢 &nbsp; Weekly Stand Up

Each week I will summarize my milestone activity and progress by writing a stand-up. A stand-up is meant to be a succinct update on how things are going. Use these prompts as a guide on what to write about:

⚙️ Overview - What I worked on this past week
<br>
🌵 Challenges - What problems did I have & how I'm addressing them
<br>
🏆 Accomplishments - What is something I "leveled up" on this week
<br>
🔮 Next Steps - What I plan to prioritize and do next

<br>

### Week 1

This week I worked on getting my Main menu started, and my initial character creation as well as my initial storyline beginning and character control menu interactions. I also created each survival stat and have the beginning game loop set up to show progress.
I found myself only truly struggling with my spelling in logic error areas such as in the middle of output strings. as well as remembering some includes and usings.
This week I absolutely nailed my game loops and menu interactions as well as my class creation and file organization. I remembered exactly how to validate user input and use switch statements for menu interaction. I also remembered exactly how to create class specific functions and used .h and .cpp properly to separate function declarations and function definitions.
Next I plan to prioritize expansion of Camp and survival systems, implementation of inventory and exploration systems, adding time progression and survival stat changes.

### Week 2

This past week I worked on multiple key systems including Inventory and items, Exploration and resource gathering, Time progression and survival-stat drain, Menu integration and usability improvements, I also completed Regression testing and debugging across the program.
My biggest challenge was connecting the systems. Each system worked separately, but the Game class needed to connect the player, inventory, locations, gathering, time, survival drain, and menus correctly.
Regression testing revealed a problem in the loop responsible for processing time and survival-stat drain. I also had to ensure inventory overflow returned uncollected resources to the location.
I tested the program action, by action, traced how values moved between classes, corrected the loop, and retested the full program.
I successfully added several connected gameplay systems rather than one isolated feature.
I improved at organizing classes by responsibility and allowing the Game class to coordinate them.
The inventory, gathering, time, stat-drain, exploration, and menu systems now work together and passed regression testing.
For week 3, I plan to prioritize basic crafting and fire-management systems that build on the inventory and resource-gathering features completed this week. I will also adding ways for the player to restore hunger and hydration. I will continue improving inventory interaction, integrating new features with the camp menu, and testing each system before connecting them. 

### Week 3

This week, I expanded The Long Lost Isle from a basic exploration and gathering system into a more complete survival gameplay loop. I added multiple-resource locations, tool-gated gathering, crafting progression, new discoverable locations, wildlife interaction, water collection, campfire cooking, survival-stat restoration, camp storage, and basic Spider encounters.
I refactored Location to support multiple resource types through a vector instead of storing only one resource. I centralized menu validation, reduced duplicated crafting setup with AddRecipe(), and separated Boar Field, Water Spring, and Spider Nest interactions into specialized functions. I also used temporary copies during crafting, cooking, carcass processing, and storage transfers to prevent partial updates or item loss when an action fails.
One of the main challenges was connecting the growing number of systems without making Game or Location too difficult to manage. Inventory capacity, dedicated equipment slots, crafting upgrades, location-specific menus, time progression, and survival-stat changes all needed to work together. I addressed these challenges by implementing one feature at a time, building frequently, and performing regression tests after each major system was completed.
I improved my understanding of class responsibilities, vectors, arrays, const references, transactional inventory changes, and reusable menu functions. I also completed nine regression-testing groups that covered navigation, exploration, discovery gates, gathering, crafting, specialized locations, survival stats, camp storage, spider encounters, and daily rollover behavior.
Before completing milestone 4, I plan to expand spider encounters with spear and bow attacks, arrow consumption, misses, and retaliation. I also plan to implement Health damage and restoration, Basic and Improved bandages, death and game-over behavior, a beginning-of-day checkpoint system, and a single save-game system. Gear effects, storage upgrades, and Silk Rope mechanics will remain optional stretch goals.

### Week 4

This week, I expanded The Long Lost Isle into a survival game with an escape objective. I implemented spider combat, health damage, bandage healing, death recovery, and a single save-game system. I also added raft construction, weather changes, temperature protection from equipment, and sanity effects caused by prolonged wakefulness.
I connected raft construction and supply contributions to the island escape ending. I improved equipment progression by requiring the previous tool or waterskin tier for upgrades. I added clearer prompts, corrected menu behavior after death, and organized saving and checkpoint recovery around a shared state structure. Final gameplay regression testing and screenshots remain pending my final playthrough.
My biggest challenge was making the growing number of systems work together without losing items or leaving the game in an inconsistent state. Saving required each class to write and validate its own data, while death recovery required nested menus and actions to stop before restoring the checkpoint. I addressed these problems by breaking features into smaller steps, using temporary object copies, building frequently, and reviewing the flow between functions.
The most valuable thing I learned was how class responsibilities and data structures affect an entire program. I became more comfortable using objects, references, vectors, arrays, and file input/output to connect gameplay systems. I also learned how smaller tasks, meaningful commits, and GitHub Issues make a large project easier to manage.
After the course, I would like to improve game balance through longer playthroughs and player feedback. I would also like to explore item durability, more varied encounters, and stronger presentation. My main goal is to keep improving my C++ design and debugging skills while building games that other people enjoy playing.
