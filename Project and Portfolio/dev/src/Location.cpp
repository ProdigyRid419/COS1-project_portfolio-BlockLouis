#include "Location.h"
#include <cstdlib>

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
