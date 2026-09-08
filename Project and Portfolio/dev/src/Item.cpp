#include "Item.h"


Item::Item() {

	itemID = ItemID::Empty;

}

Item::Item(ItemID item) {

	itemID = item;

}

ItemID Item::GetID() const {

	return itemID;

}

std::string Item::GetName() const {

	switch (itemID) {

	case ItemID::Empty: 

		return "Empty";

	case ItemID::CrudeWood:

		return "Crude Wood";

	case ItemID::RegularWood:

		return "Regular Wood";

	case ItemID::Hardwood:

		return "Hardwood";

	case ItemID::Flint:

		return "Flint";

	case ItemID::Stone:

		return "Stone";

	case ItemID::Metal:

		return "Metal";

	case ItemID::Vine:

		return "Vine";

	case ItemID::TreeSap:

		return "Tree Sap";

	case ItemID::Leather:

		return "Leather";

	case ItemID::Silk:

		return "Silk";

	case ItemID::SapReinforcedLeather:

		return "Sap Reinforced Leather";

	case ItemID::SilkRope:

		return "Silk Rope";

	case ItemID::SapReinforcedVine:

		return "Sap Reinforced Vine";

	case ItemID::MedicinalHerbs:

		return "Medicinal Herbs";

	case ItemID::Berries:

		return "Berries";

	case ItemID::RawMeat:

		return "Raw Meat";

	case ItemID::CookedMeat:

		return "Cooked Meat";

	case ItemID::PurifiedWaterBottle:

		return "Purified Water Bottle";

	case ItemID::SmallWaterskin:

		return "Small Waterskin";

	case ItemID::MediumWaterskin:

		return "Medium Waterskin";

	case ItemID::LargeWaterskin:

		return "Large Waterskin";

	case ItemID::FlintAxe:

		return "Flint Axe";

	case ItemID::StoneAxe:

		return "Stone Axe";

	case ItemID::CrudeMetalAxe:

		return "Crude Metal Axe";

	case ItemID::FlintPickaxe:

		return "Flint Pickaxe";

	case ItemID::StonePickaxe:

		return "Stone Pickaxe";

	case ItemID::MetalPickaxe:

		return "Metal Pickaxe";

	case ItemID::Spear:

		return "Spear";

	case ItemID::Bow:

		return "Bow";

	case ItemID::FlintArrow:

		return "Flint Arrow";

	case ItemID::StoneArrow:

		return "Stone Arrow";

	case ItemID::MetalArrow:

		return "Metal Arrow";

	case ItemID::VineGear:

		return "Vine Gear";

	case ItemID::LeatherGear:

		return "Leather Gear";

	case ItemID::BasicBandage:

		return "Basic Bandage";

	case ItemID::ImprovedBandage:

		return "Improved Bandage";

	}

	return "Unknown Item!!";

}

ItemCategory Item::GetCategory() const {

	switch (itemID) {

	case ItemID::Empty:
		return ItemCategory::None;

	case ItemID::CrudeWood:

		return ItemCategory::Resource;

	case ItemID::RegularWood:

		return ItemCategory::Resource;

	case ItemID::Hardwood:

		return ItemCategory::Resource;

	case ItemID::Flint:

		return ItemCategory::Resource;

	case ItemID::Stone:

		return ItemCategory::Resource;

	case ItemID::Metal:

		return ItemCategory::Resource;

	case ItemID::Vine:

		return ItemCategory::Resource;

	case ItemID::TreeSap:

		return ItemCategory::Resource;

	case ItemID::Leather:

		return ItemCategory::Resource;

	case ItemID::Silk:

		return ItemCategory::Resource;

	case ItemID::SapReinforcedLeather:

		return ItemCategory::CraftedMaterial;

	case ItemID::SilkRope:

		return ItemCategory::CraftedMaterial;

	case ItemID::SapReinforcedVine:

		return ItemCategory::CraftedMaterial;

	case ItemID::MedicinalHerbs:

		return ItemCategory::Resource;

	case ItemID::Berries:

		return ItemCategory::Food;

	case ItemID::RawMeat:

		return ItemCategory::Food;

	case ItemID::CookedMeat:

		return ItemCategory::Food;

	case ItemID::PurifiedWaterBottle:

		return ItemCategory::Water;

	case ItemID::SmallWaterskin:

		return ItemCategory::WaterContainer;

	case ItemID::MediumWaterskin:

		return ItemCategory::WaterContainer;

	case ItemID::LargeWaterskin:

		return ItemCategory::WaterContainer;

	case ItemID::FlintAxe:

		return ItemCategory::Tool;

	case ItemID::StoneAxe:

		return ItemCategory::Tool;

	case ItemID::CrudeMetalAxe:

		return ItemCategory::Tool;

	case ItemID::FlintPickaxe:

		return ItemCategory::Tool;

	case ItemID::StonePickaxe:

		return ItemCategory::Tool;

	case ItemID::MetalPickaxe:

		return ItemCategory::Tool;

	case ItemID::Spear:

		return ItemCategory::Weapon;

	case ItemID::Bow:

		return ItemCategory::Weapon;

	case ItemID::FlintArrow:

		return ItemCategory::Ammo;

	case ItemID::StoneArrow:

		return ItemCategory::Ammo;

	case ItemID::MetalArrow:

		return ItemCategory::Ammo;

	case ItemID::VineGear:

		return ItemCategory::Gear;

	case ItemID::LeatherGear:

		return ItemCategory::Gear;

	case ItemID::BasicBandage:

		return ItemCategory::Medicine;

	case ItemID::ImprovedBandage:

		return ItemCategory::Medicine;

	}

	return ItemCategory::None;

}
