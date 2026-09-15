#pragma once
#include "GameClock.h"

class Location;
class Crafting;
class Inventory;

enum class MenuType {

	Main, Camp, Exploration,
	KnownLocations,	Location, YesNo, Resources

};

class Menu {

public:

	static int DisplayCraftingMenu(const Crafting& craftingSystem, const Inventory& inventory);
	static int DisplayMenu(MenuType menuType, const GameClock& gameClock);
	static int DisplayResourceMenu(const Location& location);
	
private:

	static int GetValidatedChoice(int minimum, int maximum);

};

