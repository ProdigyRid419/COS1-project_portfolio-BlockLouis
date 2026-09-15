#pragma once
#include "Item.h"
#include <vector>

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

	const std::vector<LocationResource>& GetLocationResources() const;

	int GatherResource(ItemID item, int amount);

	void RestoreResource(ItemID item, int amount);
	void RefreshResources();
	
	Location();
	Location(LocationType newLocType);

	void MarkVisited();
	bool HasBeenVisited() const;

private:

	LocationType locType;
	LocationSize locSize;
	int travelTime;

	bool hasBeenVisited = false;

	std::vector<LocationResource> locationResources;

};