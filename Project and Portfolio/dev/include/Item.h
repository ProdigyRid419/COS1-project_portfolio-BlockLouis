#pragma once
#include <string>
#include <iosfwd>

enum class ItemID {

	Empty, CrudeWood, Hardwood,
	Flint, Stone, Metal,
	Vine, TreeSap, Leather,
	Silk, SapReinforcedLeather, SilkRope,
	SapReinforcedVine, MedicinalHerbs, RawMeat,
	CookedMeat,	SmallWaterskin, MediumWaterskin,
	LargeWaterskin,	FlintAxe, StoneAxe,
	MetalAxe, FlintPickaxe, StonePickaxe,
	MetalPickaxe, Spear, Bow,
	FlintArrow,	StoneArrow, MetalArrow,
	VineGear, LeatherGear, BasicBandage,
	ImprovedBandage, Count

};

enum class ItemCategory {

	None, WaterContainer,
	Resource, CraftedMaterial, Food,
	Water, Medicine, Tool,
	Weapon, Ammo, Gear


};

enum class SpearHeadTier {

	Flint, Stone, Metal

};

enum class SpearHandleTier {

	Vine, SapReinforcedVine, Leather

};

enum class BowStringTier {

	Vine, Silk

};

class Item {

public:

	Item();
	Item(ItemID item);

	ItemID GetID() const;
	std::string GetName() const;
	ItemCategory GetCategory() const;

	bool IsStackable() const;
	int GetMaxStack() const;

	bool Save(std::ostream& output) const;
	bool Load(std::istream& input);

private:

	ItemID itemID;

};



