> Use this worksheet to plan the next phase of your project \*\*before you begin coding\*\*
> Be clear, specific, and intentional—this will guide your development this week.

\---

## 📌 Project Overview

**Project Name:**	
→ 	**The Long Lost Isle**

**What does your program currently do? (1–3 sentences)**   
→	

&#x09;The Long Lost Isle is a text-based survival game. 

&#x09;The program currently Displays the story, accepts player input, and allows the player to move between locations or quit the game.

&#x09;Its main game loop and basic command-processing system are working.



## 🔍 Current Progress Check

**What is working right now?**   
→ 	

\-	Story introduction displayed.

\-	Player input is accepted.

\-	Main game loop runs.

\-	Player can move between locations.

\-	Quit option works.

\-	Basic command processing works.

&#x09;

**What is NOT working or incomplete?**   
→ 

\-	Survival-stat behavior.

\-	Inventory and items.

\-	Resource gathering.

\-	Time progression and stat draining.

\-	Menu usability.

&#x09;

**What feels confusing or messy in your code?**   
→

\-	I am unsure how to connect the inventory, resource-gathering, time, and player-stat systems while keeping each class responsible for the correct behavior.



\---

## 🚀 Feature Planning

List the features you plan to add or improve this week.

### Feature 1

**Name:**   
→ 	

\-	Survival Stats and Time Progression



**What does this feature do?**   
→

\-	The survival-stat system will decrease hunger and hydration, as well as stamina and sanity eventually.

\-	Time progression will occur when the player performs actions, allowing the game to determine how much stat drain should occur during each period.



**Why is this feature important?**   
→ 

\-	Survival-stat drain gives the player needs that must be managed throughout the game.

\-	Time progression allows actions to consume time and makes the survival-stat changes occur naturally as the game progresses.



\---

### Feature 2

**Name:**   
→ 

\-	Inventory and Resource Gathering



**What does this feature do?**   
→

\-	The inventory system will contain ten basic inventory slots and seven designated inventory slots for gear, weapons, and other equipment.

\-	The resource-gathering system will remove resources from locations, and add the collected resources to the player's inventory.



**Why is this feature important?**   
→ 

\-	Limited inventory space gives the player a reason to manage which items they carry.

\-	Gathering resources will support future crafting and fire-management systems.



\---

### Feature 3 (optional)

**Name:**   
→ 

\-	Menu and Prompt Improvements	



**What does this feature do?**   
→ 

**-	The program will provide clearer messages that explain how many resources the player collected and whether the inventory became full.**

**-	If some or all resources cannot fit, the program will tell the player how many were not collected.**



**Why is this feature important?**   
→ 

\-	Clear feedback will help the player understand the result of each action.

\-	It will prevent confusion when inventory space limits how many resources can be collected.



\---

## 🧩 System Design Updates

**Will you need to create any new classes? If so, which ones?**   
→ 

&#x09;Yes

\-	Item

\-	Inventory

\-	InventorySlot

\-	DedicatedInventorySlot

\-	Location

\-	GameClock

\-	SurvivalDrain

\-	Menu



**Will you modify any existing classes? How?**   
→ 	

\-	I will modify the Game class to integrate exploration, resource gathering, inventory interaction, time progression, survival-stat drain, and menus after updating them.

\-	I will modify the Player class to manage the player's survival stats and provide access to the player's inventory.



**What data structures will you use (vectors, 2D vectors, etc.)?**   
→ 

\-	I will use std::array to store 10 basic inventory slots and seven dedicated inventory slots.

\-	Fixed-size arrays are appropriate because the inventory will have a limited number of slots that should not automatically expand.



\---

## 🔄 Program Flow

**Describe how a user interacts with your program:**

1. Program starts → Display Main Menu.
2. User chooses → 1. Start game or 2. Exit.
3. Program responds → If Start game is selected calls StartGame() function.
4. Loop/next step → Displays introduction story, Displays starting time, day, and day part, Displays Camp Menu. Loops Camp Menu while it should be running.



\---

## 🎯 Usability Improvements

How will you make your program easier to use this week?

* Clearer prompts:   
→ 

\-	I will display how many resources the player successfully collected. The program will also clearly explain whether the inventory is completely full or only partially full and how many resources could not be collected.



* Better error handling:   
→ 

\-	I will add input validation to the menus so invalid selections are rejected and the player is prompted to enter a valid choice.

\-	I will prevent resource loss by returning resources to the location when they cannot fit in the player's inventory.



* Improved menu/navigation:   
→

\-	I will organize the menu-display and input-handling functions in dedicated Menu.h and Menu.cpp files.

\-	I will provide consistent menu options that allow the player to navigate between the camp, exploration, and inventory systems more easily.



\---

## ⚠️ Potential Challenges

**What do you think will be the hardest part this week?**   
→ 

\-	I expect it to be very difficult to connect every separate system to work together



**What is your plan if you get stuck?**   
→

\-	I will do independent research to achieve my goals.

 

\---

## 📈 Level Up Goal

**What skill are you focusing on improving this week?**   
→

\-	My focus this week is to keep my code structure organized and ensure each class handles only its intended responsibilities.

**What will you do to improve it?**   
(e.g., tutorial, practice, debugging, office hours)   
→

\-	I will separate responsibilities across multiple classes so that my Game class can coordinate the systems without containing all of their internal logic.

 

\---

## 🗓️ Task Breakdown (GitHub Issues Planning)

List the tasks you plan to create as GitHub Issues:

* \[ ] Create Basic Inventory
* \[ ] Create Initial Exploration System
* \[ ] Create Resource Gathering
* \[ ] Implement basic time and survival drain
* \[ ] Integrate new systems into Menus
* \[ ] Test Milestone 2 Prototype

\---

## 🔥 Final Check

Before you start coding, ask yourself:

* \[x] Do I know what I’m building this week? 
* \[x] Do I know where to start? 
* \[x] Did I break my work into small tasks? 

If yes → start coding 🚀   
If no → refine your plan first 

\---

## 😈 Final Thought

> Plan it now… or debug it later.

