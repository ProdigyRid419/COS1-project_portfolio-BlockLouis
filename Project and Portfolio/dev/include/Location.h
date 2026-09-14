#pragma once
#include "Item.h"

enum class LocationType {

	Forest, Cave

};

enum class LocationSize {

	Small, Medium, Large

};

class Location {

public:

	LocationType GetLocType() const;
	LocationSize GetLocSize() const;
	int GetTravelTime() const;

	ItemID GetResourceType() const;
	int GetResourceAmount() const;

	int GatherResource();

	void RestoreResource(int amount);
	
	Location();

	void MarkVisited();
	bool HasBeenVisited() const;

private:

	LocationType locType;
	LocationSize locSize;
	int travelTime;

	ItemID resourceType;
	int resourceAmount;
	
	bool hasBeenVisited = false;

};