#pragma once
#include <string>

enum class ItemID {

	Empty,
	CrudeWood, RegularWood, Hardwood,
	Flint, Stone, Metal,
	Vine, TreeSap, Leather,
	Silk, SapReinforcedLeather, SilkRope,
	SapReinforcedVine, MedicinalHerbs, Berries,
	RawMeat, CookedMeat, PurifiedWaterBottle,
	SmallWaterskin, MediumWaterskin, LargeWaterskin,
	FlintAxe, StoneAxe, CrudeMetalAxe,
	FlintPickaxe, StonePickaxe, MetalPickaxe,
	Spear, Bow, FlintArrow,
	StoneArrow, MetalArrow, VineGear,
	LeatherGear, BasicBandage, ImprovedBandage

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

private:

	ItemID itemID;

};



