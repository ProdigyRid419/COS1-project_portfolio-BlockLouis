#include "DedicatedInventorySlot.h"

DedicatedInventorySlot::DedicatedInventorySlot(DedicatedSlotType newSlotType) {

	slotType = newSlotType;

}

bool DedicatedInventorySlot::CanAcceptItem(const Item& newItem) const {

	switch (slotType) {

	case DedicatedSlotType::VineGear:

		if (newItem.GetID() != ItemID::VineGear) {

			return false;

		}

		return InventorySlot::CanAcceptItem(newItem);

	case DedicatedSlotType::LeatherGear:

		if (newItem.GetID() != ItemID::LeatherGear) {

			return false;

		}

		return InventorySlot::CanAcceptItem(newItem);

	case DedicatedSlotType::Spear:

		if (newItem.GetID() != ItemID::Spear) {

			return false;

		}
		
		return InventorySlot::CanAcceptItem(newItem);

	case DedicatedSlotType::Bow:

		if (newItem.GetID() != ItemID::Bow) {

			return false;

		}

		return InventorySlot::CanAcceptItem(newItem);

	case DedicatedSlotType::FlintArrow:

		if (newItem.GetID() != ItemID::FlintArrow) {

			return false;

		}

		return InventorySlot::CanAcceptItem(newItem);

	case DedicatedSlotType::StoneArrow:

		if (newItem.GetID() != ItemID::StoneArrow) {

			return false;

		}

		return InventorySlot::CanAcceptItem(newItem);

	case DedicatedSlotType::MetalArrow:

		if (newItem.GetID() != ItemID::MetalArrow) {

			return false;

		}

		return InventorySlot::CanAcceptItem(newItem);

	case DedicatedSlotType::Axe:

		if (newItem.GetID() != ItemID::FlintAxe && newItem.GetID() != ItemID::StoneAxe && newItem.GetID() != ItemID::MetalAxe) {

			return false;

		}

		return InventorySlot::CanAcceptItem(newItem);

	case DedicatedSlotType::Pickaxe:

		if (newItem.GetID() != ItemID::FlintPickaxe && newItem.GetID() != ItemID::StonePickaxe && newItem.GetID() != ItemID::MetalPickaxe) {

			return false;

		}

		return InventorySlot::CanAcceptItem(newItem);

	case DedicatedSlotType::WaterContainer:

		if (newItem.GetID() != ItemID::SmallWaterskin && newItem.GetID() != ItemID::MediumWaterskin && newItem.GetID() != ItemID::LargeWaterskin) {

			return false;

		}

		return InventorySlot::CanAcceptItem(newItem);

	}

	return false;
	
}

DedicatedSlotType DedicatedInventorySlot::GetSlotType() const {

	return slotType;

}

bool DedicatedInventorySlot::Load(std::istream& input) {

	InventorySlot loadedSlot;
	if (!loadedSlot.Load(input)) {

		return false;

	}

	DedicatedInventorySlot validationSlot(slotType);

	if (!loadedSlot.IsEmpty() && !validationSlot.CanAcceptItem(loadedSlot.GetItem())) {

		return false;

	}

	InventorySlot::operator=(loadedSlot);
	return true;

}
