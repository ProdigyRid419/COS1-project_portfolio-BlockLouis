#pragma once
#include "Item.h"
#include <vector>

enum class LocationType {

	Forest, Cave

};

enum class LocationSize {

	Small, Medium, Large

};

struct LocationResource {

	ItemID resourceType = ItemID::Empty;
	int resourceAmount = dailyLimit;
	int dailyLimit = 0;


};

class Location {

public:

	LocationType GetLocType() const;
	LocationSize GetLocSize() const;
	int GetTravelTime() const;

	const std::vector<LocationResource>& GetLocationResources() const;

	ItemID GetResourceType() const;
	
	int GatherResource(ItemID item, int amount);

	void RestoreResource(ItemID item, int amount);
	void RefreshResources();
	
	Location();

	void MarkVisited();
	bool HasBeenVisited() const;

private:

	LocationType locType;
	LocationSize locSize;
	int travelTime;

	bool hasBeenVisited = false;

	std::vector<LocationResource> locationResources;

};