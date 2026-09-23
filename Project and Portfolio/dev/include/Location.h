#pragma once
#include "Item.h"
#include <vector>
#include <iosfwd>

enum class LocationType {

	Forest, Cave, HerbalGrove,
	BoarField, WaterSpring, SpiderNest

};

enum class LocationSize {

	Small, Medium, Large

};

struct LocationResource {

	ItemID resourceType = ItemID::Empty;
	int dailyLimit = 0;
	int resourceAmount = dailyLimit;


};

class Location {

public:

	LocationType GetLocType() const;
	LocationSize GetLocSize() const;
	int GetTravelTime() const;
	
	int GetRemainingBoars() const;
	int GetUnprocessedBoars() const;
	int HuntBoars();
	bool ProcessBoarCarcass();

	int GetRemainingSpiders() const;
	bool DefeatSpider();

	const std::vector<LocationResource>& GetLocationResources() const;

	int GatherResource(ItemID item, int amount);

	void RestoreResource(ItemID item, int amount);
	void RefreshDailyState();
	
	Location();
	Location(LocationType newLocType);

	void MarkVisited();
	bool HasBeenVisited() const;

	bool Save(std::ostream& output) const;
	bool Load(std::istream& input);

private:

	LocationType locType;
	LocationSize locSize;
	int travelTime;

	bool hasBeenVisited = false;

	std::vector<LocationResource> locationResources;

	int boarDailyLimit = 0;
	int remainingBoars = 0;
	int unprocessedBoars = 0;

	int spiderDailyLimit = 0;
	int remainingSpiders = 0;

};