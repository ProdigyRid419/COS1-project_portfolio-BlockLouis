#pragma once
#include "Player.h"
#include "Location.h"
#include "GameClock.h"
#include "SurvivalDrain.h"
#include <optional>
#include <array>
#include "Crafting.h"

class Game {

public:

	void Run();

private:

	void StartGame();
	void ViewStatus();
	void Sleep();
	void ShowInventory();
	void Explore();
	void ProcessTime(int fifteenMinuteIntervals, ActivityLevel activityLevel);
	void OpenCraftingMenu();

	void TravelToLocation(Location& location);
	void GatherFromLocation(Location& location);
	void VisitLocation(Location& location);
	void VisitBoarField(Location& location);
	void HuntAtBoarField(Location& location);
	void ProcessBoarCarcassAtField(Location& location);
	
	void DisplayLocationInfo(const Location& location);
	void DisplayLocationInfoDiscovery(const Location& location);
	void RefreshKnownLocations();
	
	int GetLocationIndex(LocationType locationType);
	std::string GetLocationName(int locationIndex);
	LocationType GenerateDiscoverableLocationType();
	int GetGatherAmount(ItemID resourceType);

	Player Player1;
	GameClock gameClock;
	SurvivalDrain playerDrain;
	std::array<std::optional<Location>, 6> knownLocations{};
	Crafting craftingSystem;

};


