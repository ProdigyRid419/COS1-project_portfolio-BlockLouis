#pragma once
#include "GameClock.h"
#include "Campfire.h"

class Location;
class Crafting;
class Inventory;
class Item;
class CampStorage;

enum class MenuType {

	Main, Camp, Exploration,
	KnownLocations,	Location, YesNo,
	Resources, BoarField, BoarCarcass,
	WaterSpring, CampStorage, SpiderNest

};

class Menu {

public:

	static int DisplayCraftingMenu(const Crafting& craftingSystem, const Inventory& inventory);
	static int DisplayMenu(MenuType menuType, const GameClock& gameClock);
	static int DisplayResourceMenu(const Location& location);
	static int DisplayCampfireMenu(const Campfire& campfire, const GameClock& gameClock);
	static int DisplayFuelAmountMenu(int playerWood, int fuelFireCanAccept);
	static int DisplayCookingMenu(int playerMeat);
	static int DisplayConsumableMenu(const Inventory& inventory);
	static int DisplayInventorySlotSelection(const Inventory& inventory);
	static int DisplayQuantityMenu(const Item& item, int availableQuantity);
	static int DisplayStorageSlotSelection(const CampStorage& campStorage);

private:

	static int GetValidatedChoice(int minimum, int maximum);

};

