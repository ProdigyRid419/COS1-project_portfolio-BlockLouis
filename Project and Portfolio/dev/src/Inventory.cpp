#include "Inventory.h"
#include <iostream>

void Inventory::DisplayInventory() const {
	
	std::cout << "=== Dedicated Inventory Slots ===\n\n";

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

		case DedicatedSlotType::Arrow:

			std::cout << "Arrows: ";
			break;

		case DedicatedSlotType::Axe:

			std::cout << "Axe: ";
			break;

		case DedicatedSlotType::Pickaxe:

			std::cout << "Pickaxe: ";
			break;

		}

		if (dedicatedInventorySlots[i].IsEmpty()) {

			std::cout << dedicatedInventorySlots[i].GetItem().GetName() << '\n';

		} else {

			std::cout << dedicatedInventorySlots[i].GetItem().GetName() << " x" << dedicatedInventorySlots[i].GetQuantity() << '\n';

		}

	}

	std::cout << "\n\n=== Inventory Slots ===\n\n";

	for (int i = 0; i < inventorySlots.size(); i++) {

		if (inventorySlots[i].IsEmpty()) {

			std::cout << "Slot " << i + 1 << ": " << inventorySlots[i].GetItem().GetName() << '\n';
			
		} else {

			std::cout << "Slot " << i + 1 << ": " << inventorySlots[i].GetItem().GetName() << " x" << inventorySlots[i].GetQuantity() << '\n';

		}

	}

}

int Inventory::AddItem(const Item& newItem, int amount) {

	int remaining = amount;

	bool dedicatedItemSlotCheck = true;
	if (newItem.GetCategory() != ItemCategory::Tool && newItem.GetCategory() != ItemCategory::Weapon && newItem.GetCategory() != ItemCategory::Ammo && newItem.GetCategory() != ItemCategory::Gear) {

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
	
	if (newItem.GetCategory() != ItemCategory::Tool && newItem.GetCategory() != ItemCategory::Weapon && newItem.GetCategory() != ItemCategory::Ammo && newItem.GetCategory() != ItemCategory::Gear) {

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

