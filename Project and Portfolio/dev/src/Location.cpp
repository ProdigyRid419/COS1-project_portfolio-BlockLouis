#include "Location.h"
#include <cstdlib>

Location::Location() {

	int randomLocType = rand() % 2;
	locType = static_cast<LocationType>(randomLocType);
	int randomLocSize = rand() % 3;
	locSize = static_cast<LocationSize>(randomLocSize);
	int randomLocTime = (rand() % 3) + 1;
	travelTime = randomLocTime;

	switch (locType) {

	case LocationType::Forest:

		resourceType = ItemID::CrudeWood;
		break;

	case LocationType::Cave:

		resourceType = ItemID::Flint;
		break;

	}

	switch (locSize) {

	case LocationSize::Small:

		resourceAmount = 15;
		break;

	case LocationSize::Medium:

		resourceAmount = 40;
		break;

	case LocationSize::Large:

		resourceAmount = 70;
		break;

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

ItemID Location::GetResourceType() const {

	return resourceType;

}

int Location::GetResourceAmount() const {

	return resourceAmount;

}

int Location::GatherResource() {

	if (resourceAmount >= 5) {

		resourceAmount -= 5;
		return 5;

	} else {

		return 0;

	}

}

void Location::RestoreResource(int amount) {

	resourceAmount += amount;

}


