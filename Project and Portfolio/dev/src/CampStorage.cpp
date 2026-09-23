#include "CampStorage.h"
#include <iostream>

int CampStorage::AddItem(const Item& newItem, int amount) {

	int remaining = amount;

	if (amount <= 0) {

		return 0;

	}

	for (InventorySlot& slot : campStorageSlots) {

		if (slot.GetItem().GetID() == newItem.GetID()) {

			remaining = slot.AddQuantity(newItem, remaining);

		}

		if (remaining == 0) {

			return 0;

		}

	}

	for (InventorySlot& slot : campStorageSlots) {

		if (slot.IsEmpty()) {

			remaining = slot.AddQuantity(newItem, remaining);

		}

		if (remaining == 0) {

			return 0;

		}

	}

	return remaining;

}

int CampStorage::RemoveItem(const Item& newItem, int amount) {

	int remaining = amount;

	if (remaining <= 0) {

		return 0;

	}

	for (InventorySlot& slot : campStorageSlots) {

		if (slot.GetItem().GetID() == newItem.GetID()) {

			remaining = slot.RemoveQuantity(remaining);

		}

		if (remaining == 0) {

			return 0;

		}

	}

	return remaining;

}

int CampStorage::GetItemCount(ItemID itemID) const {

	int amount = 0;

	for (const InventorySlot& slot : campStorageSlots) {

		if (itemID == slot.GetItem().GetID()) {

			amount += slot.GetQuantity();

		}

	}

	return amount;

}

void CampStorage::DisplayCampStorage() const{

	int slotNumber = 1;

	std::cout << "\n\n=== Camp Storage ===\n\n";

	for (const InventorySlot& slot : campStorageSlots) {

		if (slot.IsEmpty()) {

			std::cout << slotNumber << ": Empty\n";

		} else {

			std::cout << slotNumber << ": " << slot.GetItem().GetName() << "\tAmount: " << slot.GetQuantity() << '\n';

		}

		slotNumber++;

	}

}

const std::array<InventorySlot, 20>& CampStorage::GetCampStorageSlots() const {

	return campStorageSlots;

}

bool CampStorage::Save(std::ostream& output) const {

	for (const InventorySlot& slot : campStorageSlots) {

		if (!slot.Save(output)) {

			return false;

		}

	}

	return static_cast<bool>(output);

}

bool CampStorage::Load(std::istream& input) {

	CampStorage loadedStorage;

	for (InventorySlot& loadedSlot : loadedStorage.campStorageSlots) {

		if (!loadedSlot.Load(input)) {

			return false;

		}

	}

	campStorageSlots = loadedStorage.campStorageSlots;
	return true;

}
