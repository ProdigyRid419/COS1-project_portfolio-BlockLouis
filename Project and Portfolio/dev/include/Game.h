#pragma once
#include "Player.h"
#include "Location.h"
#include <optional>
#include <array>

class Game {

public:

	void Run();

private:

	void StartGame();
	void ViewStatus();
	void Sleep();
	void ShowInventory();
	void GatherFromLocation(Location& location);
	void Explore();
	void VisitLocation(Location& location);
	void DisplayLocationInfo(const Location& location);
	void DisplayLocationInfoDiscovery(const Location& location);
	int GetLocationIndex(LocationType locationType);
	std::string GetLocationName(int locationIndex);

	Player Player1;
	std::array<std::optional<Location>, 2> knownLocations{};

};


