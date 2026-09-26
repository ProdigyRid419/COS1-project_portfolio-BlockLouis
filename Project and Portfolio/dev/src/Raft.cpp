#include "Raft.h"
#include <iostream>


bool Raft::IsBuilt() const {

	if ((hardwoodContributed < requiredHardwood) || (reinforcedLeatherContributed < requiredReinforcedLeather) || (silkRopeContributed < requiredSilkRope) || (metalContributed < requiredMetal)) {

		return false;

	}

	return true;

}

bool Raft::IsReadyToEscape() const {

	if (!IsBuilt()) {

		return false;

	}

	if ((cookedMeatStored < requiredCookedMeat) || (waterStored < requiredWater)) {

		return false;

	}

	return true;

}

int Raft::GetRemainingRequirement(ItemID item) const {

	switch (item) {

	case ItemID::Hardwood:

		return requiredHardwood - hardwoodContributed;
		
	case ItemID::SilkRope:

		return requiredSilkRope - silkRopeContributed;
		
	case ItemID::SapReinforcedLeather:

		return requiredReinforcedLeather - reinforcedLeatherContributed;
		
	case ItemID::Metal:

		return requiredMetal - metalContributed;
		
	case ItemID::CookedMeat:

		return requiredCookedMeat - cookedMeatStored;

	}

	return 0;

}

int Raft::ContributeItem(ItemID item, int amount) {

	if (amount <= 0) {

		return 0;

	}

	int remainingRequired = GetRemainingRequirement(item);

	if (remainingRequired <= 0) {

		return 0;

	}

	int acceptedAmount = amount;

	if (acceptedAmount > remainingRequired) {

		acceptedAmount = remainingRequired;

	}

	switch (item) {

	case ItemID::Hardwood:

		hardwoodContributed += acceptedAmount;
		break;

	case ItemID::SilkRope:

		silkRopeContributed += acceptedAmount;
		break;

	case ItemID::SapReinforcedLeather:

		reinforcedLeatherContributed += acceptedAmount;
		break;

	case ItemID::Metal:

		metalContributed += acceptedAmount;
		break;

	case ItemID::CookedMeat:

		cookedMeatStored += acceptedAmount;
		break;

	}

	return acceptedAmount;

}

int Raft::GetRemainingWaterRequirement() const {

	return requiredWater - waterStored;

}

int Raft::ContributeWater(int amount) {

	if (amount <= 0) {

		return 0;

	}

	int remainingRequired = GetRemainingWaterRequirement();

	if (remainingRequired <= 0) {

		return 0;

	}

	int acceptedAmount = amount;

	if (remainingRequired < acceptedAmount) {

		acceptedAmount = remainingRequired;

	}

	waterStored += acceptedAmount;
	
	return acceptedAmount;

}

void Raft::DisplayProgress() const {

	std::cout << "\n\n=== Raft ===\n\n";

	if (!IsBuilt()) {

		std::cout << "Raft has not yet been built.\nYou have contributed the following materials.\nHardwood: " << hardwoodContributed << '/' << requiredHardwood << "\nMetal: " << metalContributed << '/' << requiredMetal << "\nReinforced Leather: " << reinforcedLeatherContributed << '/' << requiredReinforcedLeather << "\nSilk Rope: " << silkRopeContributed << '/' << requiredSilkRope << '\n';
		return;

	}

	if (!IsReadyToEscape()) {

		std::cout << "Raft does not currently have enough resources to survive escape.\nYou have contributed the following resources.\nCooked Meat: " << cookedMeatStored << '/' << requiredCookedMeat << "\nWater: " << waterStored << '/' << requiredWater << '\n';
		return;

	}

	std::cout << "Raft is ready for escape.\nIt's time to leave The Long Lost Isle.\n\n";

}

bool Raft::Save(std::ostream& output) const {

	output << hardwoodContributed << ' ' << silkRopeContributed << ' ' << reinforcedLeatherContributed << ' ' << metalContributed << ' ' << cookedMeatStored << ' ' << waterStored << '\n';
	if (!static_cast<bool>(output)) {

		return false;

	}

	return true;

}

bool Raft::Load(std::istream& input) {

	Raft loadedRaft;

	input >> loadedRaft.hardwoodContributed >> loadedRaft.silkRopeContributed >> loadedRaft.reinforcedLeatherContributed >> loadedRaft.metalContributed >> loadedRaft.cookedMeatStored >> loadedRaft.waterStored;
	if (!static_cast<bool>(input)) {

		return false;

	}

	if (loadedRaft.hardwoodContributed < 0 || (loadedRaft.hardwoodContributed > loadedRaft.requiredHardwood) || loadedRaft.silkRopeContributed < 0 || (loadedRaft.silkRopeContributed > loadedRaft.requiredSilkRope) || loadedRaft.reinforcedLeatherContributed < 0 || (loadedRaft.reinforcedLeatherContributed > loadedRaft.requiredReinforcedLeather) || loadedRaft.metalContributed < 0 || (loadedRaft.metalContributed > loadedRaft.requiredMetal) || loadedRaft.cookedMeatStored < 0 || (loadedRaft.cookedMeatStored > loadedRaft.requiredCookedMeat) || loadedRaft.waterStored < 0 || (loadedRaft.waterStored > loadedRaft.requiredWater)) {

		return false;

	}

	*this = loadedRaft;
	return true;

}