#pragma once
#include "Player.h"
#include "Location.h"
#include "GameClock.h"
#include "SurvivalDrain.h"
#include <optional>
#include <array>
#include "Crafting.h"
#include "Campfire.h"
#include "CampStorage.h"
#include "DailyCheckpoint.h"

class Game {

public:

	void Run();

private:

	void StartGame();
	void Sleep();
	void ShowInventory();
	void Explore();
	void OpenCraftingMenu();
	void OpenCampfireMenu();
	void Rest();

	
	Player Player1;
	void ViewStatus();
	bool CanPerformStrenuousAction() const;
	void UseBandage(ItemID item);

	GameClock gameClock;
	void ProcessTime(int fifteenMinuteIntervals, ActivityLevel activityLevel);
	void RefreshKnownLocations();

	SurvivalDrain playerDrain;
	void ConsumeFood(ItemID item);
	void ConsumeWater();
	
	std::array<std::optional<Location>, 6> knownLocations{};
	void TravelToLocation(Location& location);
	void GatherFromLocation(Location& location);
	void VisitLocation(Location& location);
	void VisitBoarField(Location& location);
	void HuntAtBoarField(Location& location);
	void ProcessBoarCarcassAtField(Location& location);
	void VisitWaterSpring(Location& location);
	void FillAtWaterSpring();
	void DisplayLocationInfo(const Location& location);
	void DisplayLocationInfoDiscovery(const Location& location);
	int GetLocationIndex(LocationType locationType);
	std::string GetLocationName(int locationIndex);
	LocationType GenerateDiscoverableLocationType();
	int GetGatherAmount(ItemID resourceType);
	void VisitSpiderNest(Location& location);
	void FightSpiderAtNest(Location& location);
	
	Crafting craftingSystem;
	
	
	
	Campfire campfire;
	void BuildCampfire();
	void AddFuelToCampfire();
	void CookMeatAtCampfire();

	CampStorage campStorage;
	void OpenCampStorageMenu();
	void DepositItemToStorage();
	void WithdrawItemFromStorage();

	std::optional<DailyCheckpoint> dailyCheckpoint;
	void CaptureDailyCheckpoint();
	bool RestoreDailyCheckpoint();

};


