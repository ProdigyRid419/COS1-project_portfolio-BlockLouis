#include "Location.h"
#include <cstdlib>
#include <iostream>

Location::Location() : Location(static_cast<LocationType>(rand() % 2)) {



}

Location::Location(LocationType newLocType) {

	locType = newLocType;
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

	} else if (locType == LocationType::Cave) {

		locationResources.push_back({ ItemID::Flint, dailyResourceAmount, dailyResourceAmount });
		locationResources.push_back({ ItemID::Stone, dailyResourceAmount, dailyResourceAmount });
		locationResources.push_back({ ItemID::Metal, dailyResourceAmount, dailyResourceAmount });

	} else if (locType == LocationType::HerbalGrove) {

		int herbDailyResourceAmount = 0;
		if (locSize == LocationSize::Small) {

			herbDailyResourceAmount = 20;

		} else if (locSize == LocationSize::Medium) {

			herbDailyResourceAmount = 50;

		} else if (locSize == LocationSize::Large) {

			herbDailyResourceAmount = 80;

		}

		locationResources.push_back({ ItemID::MedicinalHerbs, herbDailyResourceAmount, herbDailyResourceAmount });

	} else if (locType == LocationType::BoarField) {

		if (locSize == LocationSize::Small) {

			boarDailyLimit = 6;

		} else if (locSize == LocationSize::Medium) {

			boarDailyLimit = 10;

		} else if (locSize == LocationSize::Large) {

			boarDailyLimit = 20;

		}

		remainingBoars = boarDailyLimit;

	}
	else if (locType == LocationType::SpiderNest) {

		if (locSize == LocationSize::Small) {

			spiderDailyLimit = 5;

		} else if (locSize == LocationSize::Medium) {

			spiderDailyLimit = 9;

		}
		else if (locSize == LocationSize::Large) {

			spiderDailyLimit = 15;

		}

		remainingSpiders = spiderDailyLimit;

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

void Location::RefreshDailyState() {

	for (LocationResource& resource : locationResources) {

		resource.resourceAmount = resource.dailyLimit;

	}

	if (locType == LocationType::BoarField) {

		remainingBoars = boarDailyLimit;
		unprocessedBoars = 0;

	}

	if (locType == LocationType::SpiderNest) {

		remainingSpiders = spiderDailyLimit;

	}

}

void Location::MarkVisited() {

	hasBeenVisited = true;

}

bool Location::HasBeenVisited() const {

	return hasBeenVisited;

}

int Location::GetRemainingBoars() const {

	return remainingBoars;

}

int Location::GetUnprocessedBoars() const {

	return unprocessedBoars;

}

int Location::HuntBoars() {

	if (remainingBoars <= 0) {

		return 0;

	}

	int randomBoarAmount = (rand() % 3) + 1;
	
	if (randomBoarAmount > remainingBoars) {

		randomBoarAmount = remainingBoars;

	}

	remainingBoars -= randomBoarAmount;
	unprocessedBoars += randomBoarAmount;

	return randomBoarAmount;

}

bool Location::ProcessBoarCarcass() {

	if (unprocessedBoars <= 0) {

		return false; 

	}

	unprocessedBoars -= 1;
	return true;

}

int Location::GetRemainingSpiders() const {

	return remainingSpiders;

}

bool Location::DefeatSpider() {

	if (remainingSpiders <= 0) {

		remainingSpiders = 0;
		return false;

	}

	remainingSpiders -= 1;
	return true;

}

bool Location::Save(std::ostream& output) const {

	output << static_cast<int>(locType) << ' ' << static_cast<int>(locSize) << ' ' << travelTime << ' ' << hasBeenVisited << '\n';
	output << locationResources.size() << '\n';

	for (const LocationResource& resource : locationResources) {

		output << static_cast<int>(resource.resourceType) << ' ' << resource.dailyLimit << ' ' << resource.resourceAmount << '\n';

	}

	output << boarDailyLimit << ' ' << remainingBoars << ' ' << unprocessedBoars << ' ' << spiderDailyLimit << ' ' << remainingSpiders << '\n';

	return static_cast<bool>(output);

}

bool Location::Load(std::istream& input) {

	int loadedType = 0;
	int loadedSize = 0;
	int loadedTravelTime = 0;
	bool loadedVisited = false;

	input >> loadedType >> loadedSize >> loadedTravelTime >> loadedVisited;
	if (!static_cast<bool>(input)) {

		return false;

	}

	if ((loadedType < 0 || loadedType > static_cast<int>(LocationType::SpiderNest) || (loadedSize < 0 || loadedSize > static_cast<int>(LocationSize::Large) || (loadedTravelTime <= 0 || loadedTravelTime > 3)))) {

		return false;

	}

	int loadedResourceCount = 0;
	input >> loadedResourceCount;
	if (!static_cast<bool>(input)) {

		return false;

	}
	if (loadedResourceCount < 0 || loadedResourceCount > 4) {

		return false;

	}

	std::vector<LocationResource> loadedResources;

	for (int i = 0; i < loadedResourceCount; i++) {

		int loadedResourceType = 0;
		LocationResource loadedResource;

		input >> loadedResourceType >> loadedResource.dailyLimit >> loadedResource.resourceAmount;
		if (!static_cast<bool>(input)) {

			return false;

		}

		if (loadedResourceType <= static_cast<int>(ItemID::Empty) || loadedResourceType >= static_cast<int>(ItemID::Count)) {

			return false;

		}

		if (loadedResource.dailyLimit < 0 || loadedResource.resourceAmount < 0 || loadedResource.resourceAmount > loadedResource.dailyLimit) {

			return false;

		}

		loadedResource.resourceType = static_cast<ItemID>(loadedResourceType);
		loadedResources.push_back(loadedResource);

	}

	int loadedBoarDailyLimit = 0;
	int loadedRemainingBoars = 0;
	int loadedUnprocessedBoars = 0;
	int loadedSpiderDailyLimit = 0;
	int loadedRemainingSpiders = 0;

	input >> loadedBoarDailyLimit >> loadedRemainingBoars >> loadedUnprocessedBoars >> loadedSpiderDailyLimit >> loadedRemainingSpiders;
	if (!input) {

		return false;

	}

	if (loadedBoarDailyLimit < 0 || loadedRemainingBoars < 0 || loadedUnprocessedBoars < 0 || loadedSpiderDailyLimit < 0 || loadedRemainingSpiders < 0 || loadedRemainingBoars > loadedBoarDailyLimit || loadedRemainingSpiders > loadedSpiderDailyLimit || loadedUnprocessedBoars > (loadedBoarDailyLimit - loadedRemainingBoars)) {

		return false;

	}

	locType = static_cast<LocationType>(loadedType);
	locSize = static_cast<LocationSize>(loadedSize);
	travelTime = loadedTravelTime;
	hasBeenVisited = loadedVisited;
	locationResources = loadedResources;
	boarDailyLimit = loadedBoarDailyLimit;
	remainingBoars = loadedRemainingBoars;
	unprocessedBoars = loadedUnprocessedBoars;
	spiderDailyLimit = loadedSpiderDailyLimit;
	remainingSpiders = loadedRemainingSpiders;
	
	return true;

}
