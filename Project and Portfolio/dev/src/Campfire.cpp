#include "Campfire.h"

bool Campfire::IsBuilt() const {

	return isBuilt;

}

bool Campfire::IsLit() const {

	return fuelMinutes > 0;

}

int Campfire::GetFuelMinutes() const {

	return fuelMinutes;

}

void Campfire::Build() {

	isBuilt = true;

}

int Campfire::AddFuel(int woodAmount) {

	if (woodAmount <= 0) {

		return 0;

	}

	if (!isBuilt) {

		return 0;

	}

	int woodToAdd = GetAvailableFuelCap();

	if (woodAmount < woodToAdd) {

		woodToAdd = woodAmount;

	} 

	fuelMinutes += (woodToAdd * 60);

	return woodToAdd;

}

void Campfire::BurnForMinutes(int minutes) {

	if (minutes <= 0) {

		return;

	}

	if (!IsLit()) {

		return;

	}
	
	if (minutes >= fuelMinutes) {

		fuelMinutes = 0;

	} else {

		fuelMinutes -= minutes;

	}

}

int Campfire::GetAvailableFuelCap() const {

	int remainingMinutes = maximumBurnTime - fuelMinutes;

	int acceptableFuelAmount = remainingMinutes / 60;

	return acceptableFuelAmount;

}
