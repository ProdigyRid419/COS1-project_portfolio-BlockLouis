#pragma once
#include "Item.h"
#include <iosfwd>

class Raft {

public:

	bool IsBuilt() const;
	bool IsReadyToEscape() const;
	int GetRemainingRequirement(ItemID item) const;
	int ContributeItem(ItemID item, int amount);
	int GetRemainingWaterRequirement() const;
	int ContributeWater(int amount);
	void DisplayProgress() const;
	
	bool Save(std::ostream& output) const;
	bool Load(std::istream& input);

private:

	int hardwoodContributed = 0;
	int silkRopeContributed = 0;
	int reinforcedLeatherContributed = 0;
	int metalContributed = 0;
	int cookedMeatStored = 0;
	int waterStored = 0;

	static constexpr int requiredHardwood = 300;
	static constexpr int requiredSilkRope = 60;
	static constexpr int requiredReinforcedLeather = 50;
	static constexpr int requiredMetal = 500;
	static constexpr int requiredCookedMeat = 100;
	static constexpr int requiredWater = 50;

};



