#include "Location.h"
#include <cstdlib>

Location::Location() {

	int randomLocType = rand() % 2;
	locType = static_cast<LocationType>(randomLocType);
	int randomLocSize = rand() % 3;
	locSize = static_cast<LocationSize>(randomLocSize);
	int randomLocTime = (rand() % 3) + 1;
	travelTime = randomLocTime;
	int dailyResourceAmount = 0;

	switch (locSize) {

	case LocationSize::Small:

		dailyResourceAmount = 15;
		break;

	case LocationSize::Medium:

		dailyResourceAmount = 40;
		break;

	case LocationSize::Large:

		dailyResourceAmount = 70;
		break;

	}
	if (locType == LocationType::Forest) {

		locationResources.push_back({ ItemID::CrudeWood, dailyResourceAmount, dailyResourceAmount });
		locationResources.push_back({ ItemID::Hardwood, dailyResourceAmount, dailyResourceAmount });
		locationResources.push_back({ ItemID::TreeSap, dailyResourceAmount, dailyResourceAmount });
		locationResources.push_back({ ItemID::Vine, dailyResourceAmount, dailyResourceAmount });

	}
	else if (locType == LocationType::Cave) {

		locationResources.push_back({ ItemID::Flint, dailyResourceAmount, dailyResourceAmount });
		locationResources.push_back({ ItemID::Stone, dailyResourceAmount, dailyResourceAmount });
		locationResources.push_back({ ItemID::Metal, dailyResourceAmount, dailyResourceAmount });

	}

}

LocationType Location::GetLocType() const {

	return locType;

}

LocationSize Location::GetLocSize() const {

	return locSize;

}

int Location::GetTravelTime() const {

	return travelTime;

}

const std::vector<LocationResource>& Location::GetLocationResources() const {

	return locationResources;

}

ItemID Location::GetResourceType() const {

	if (!locationResources.empty()) {

		return locationResources[0].resourceType;

	}

	return ItemID::Empty;

}

int Location::GatherResource(ItemID item, int amount) {

	if (amount <= 0) {

		return 0;

	}

	for (LocationResource& resource : locationResources) {

		if (resource.resourceType == item) {

			if (resource.resourceAmount >= amount) {

				resource.resourceAmount -= amount;
				return amount;

			}
			else if (resource.resourceAmount > 0) {

				int result = resource.resourceAmount;
				resource.resourceAmount = 0;
				return result;

			}

		}

	}

	return 0;

}

void Location::RestoreResource(ItemID item, int amount) {

	if (amount <= 0) {

		return;

	}

	for (LocationResource& resource : locationResources) {

		if (resource.resourceType == item) {
				
			if (resource.resourceAmount + amount >= resource.dailyLimit) {

				resource.resourceAmount = resource.dailyLimit;

			} else {

				resource.resourceAmount += amount;

			}

			return;

		}

	}

}

void Location::RefreshResources() {

	for (LocationResource& resource : locationResources) {

		resource.resourceAmount = resource.dailyLimit;

	}

}

void Location::MarkVisited() {

	hasBeenVisited = true;

}

bool Location::HasBeenVisited() const {

	return hasBeenVisited;

}


