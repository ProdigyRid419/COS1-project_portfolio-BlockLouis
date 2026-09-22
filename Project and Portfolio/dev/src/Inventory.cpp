#include "Inventory.h"
#include <iostream>

void Inventory::DisplayInventory() const {
	
	std::cout << "\n=== Dedicated Inventory Slots ===\n\n";

	for (int i = 0; i < dedicatedInventorySlots.size(); i++) {

		switch (dedicatedInventorySlots[i].GetSlotType()) {

		case DedicatedSlotType::VineGear:

			std::cout << "Vine Gear: ";
			break;

		case DedicatedSlotType::LeatherGear:

			std::cout << "Leather Gear: ";
			break;

		case DedicatedSlotType::Spear:

			std::cout << "Spear: ";
			break;

		case DedicatedSlotType::Bow:

			std::cout << "Bow: ";
			break;

		case DedicatedSlotType::FlintArrow:

			std::cout << "Flint arrows: ";
			break;

		case DedicatedSlotType::StoneArrow:

			std::cout << "Stone arrows: ";
			break;
		
		case DedicatedSlotType::MetalArrow:

			std::cout << "Metal arrows: ";
			break;

		case DedicatedSlotType::Axe:

			std::cout << "Axe: ";
			break;

		case DedicatedSlotType::Pickaxe:

			std::cout << "Pickaxe: ";
			break;

		case DedicatedSlotType::WaterContainer:

			std::cout << "Waterskin: ";
			break;

		}

		if (dedicatedInventorySlots[i].IsEmpty()) {

			std::cout << dedicatedInventorySlots[i].GetItem().GetName() << '\n';

		} else {

			std::cout << dedicatedInventorySlots[i].GetItem().GetName() << " x" << dedicatedInventorySlots[i].GetQuantity() << '\n';

		}

	}

	std::cout << "\n=== Inventory Slots ===\n\n";

	for (int i = 0; i < inventorySlots.size(); i++) {

		if (inventorySlots[i].IsEmpty()) {

			std::cout << "Slot " << i + 1 << ": " << inventorySlots[i].GetItem().GetName() << '\n';
			
		} else {

			std::cout << "Slot " << i + 1 << ": " << inventorySlots[i].GetItem().GetName() << " x" << inventorySlots[i].GetQuantity() << '\n';

		}

	}

	std::cout << '\n';

}

int Inventory::AddItem(const Item& newItem, int amount) {

	int remaining = amount;

	bool dedicatedItemSlotCheck = true;
	if (newItem.GetCategory() != ItemCategory::Tool && newItem.GetCategory() != ItemCategory::Weapon && newItem.GetCategory() != ItemCategory::Ammo && newItem.GetCategory() != ItemCategory::Gear && newItem.GetCategory() != ItemCategory::WaterContainer) {

		dedicatedItemSlotCheck = false;

	}

	if (dedicatedItemSlotCheck) {

		for (int i = 0; i < dedicatedInventorySlots.size(); i++) {

			if (dedicatedInventorySlots[i].CanAcceptItem(newItem)) {

				remaining = dedicatedInventorySlots[i].AddQuantity(newItem, remaining);

			}
			if (remaining == 0) {

				break;

			}

		}

		return remaining;

	}

	for (int i = 0; i < inventorySlots.size(); i++) {

		if (inventorySlots[i].GetItem().GetID() == newItem.GetID()) {

			remaining = inventorySlots[i].AddQuantity(newItem, remaining);

		} 
		if (remaining == 0) {

			break;

		}

	}


	if (remaining > 0) {

		for (int i = 0; i < inventorySlots.size(); i++) {

			if (inventorySlots[i].IsEmpty()) {

				remaining = inventorySlots[i].AddQuantity(newItem, remaining);
				
				if (remaining == 0) {

					break;

				}

			}

		}

	}

	return remaining;

}

int Inventory::RemoveItem(const Item& newItem, int amount) {

	int remaining = amount;
	
	bool dedicatedItemSlotCheck = true;
	
	if (newItem.GetCategory() != ItemCategory::Tool && newItem.GetCategory() != ItemCategory::Weapon && newItem.GetCategory() != ItemCategory::Ammo && newItem.GetCategory() != ItemCategory::Gear && newItem.GetCategory() != ItemCategory::WaterContainer) {

		dedicatedItemSlotCheck = false;

	}

	if (dedicatedItemSlotCheck) {

		for (int i = 0; i < dedicatedInventorySlots.size(); i++) {

			if (dedicatedInventorySlots[i].GetItem().GetID() == newItem.GetID()) {

				remaining = dedicatedInventorySlots[i].RemoveQuantity(remaining);

			}

			if (remaining == 0) {

				break;

			}

		}

		return remaining;

	}

	for (int i = 0; i < inventorySlots.size(); i++) {

		if (inventorySlots[i].GetItem().GetID() == newItem.GetID()) {

			remaining = inventorySlots[i].RemoveQuantity(remaining);

		}

		if (remaining == 0) {

			break;

		}

		

	}

	return remaining;

}

int Inventory::GetItemCount(ItemID itemID) const {

	int total = 0;

	for (const InventorySlot& inventorySlot : inventorySlots) {

		if (inventorySlot.GetItem().GetID() == itemID) {

			total += inventorySlot.GetQuantity();

		} 

	}

	for (const DedicatedInventorySlot& dedicatedSlot : dedicatedInventorySlots) {

		if (dedicatedSlot.GetItem().GetID() == itemID) {

			total += dedicatedSlot.GetQuantity();

		}

	}

	return total;

}

int Inventory::GetStoredWater() const {

	return storedWater;

}

int Inventory::GetWaterCapacity() const {

	if (GetItemCount(ItemID::SmallWaterskin) > 0) {

		return 1;

	} else if (GetItemCount(ItemID::MediumWaterskin) > 0) {

		return 3;

	} else if (GetItemCount(ItemID::LargeWaterskin) > 0) {

		return 8;

	}

	return 0;

}

int Inventory::FillWaterContainer() {

	int capacity = GetWaterCapacity();
	if (storedWater < capacity && capacity > 0) {

		int waterAdded = capacity - storedWater;

		storedWater = capacity;

		return waterAdded;

	}

	return 0;

}

bool Inventory::ConsumeWater() {

	if (storedWater <= 0) {

		return false;

	}

	storedWater -= 1;
	return true;

}

const std::array<InventorySlot, 10>& Inventory::GetInventorySlots() const {

	return inventorySlots;

}