#pragma once
#include "InventorySlot.h"
#include <array>

class CampStorage {

public:

	int AddItem(const Item& newItem, int amount);
	int RemoveItem(const Item& newItem, int amount);
	int GetItemCount(ItemID itemID) const;
	void DisplayCampStorage() const;
	const std::array<InventorySlot, 20>& GetCampStorageSlots() const;

private:

	std::array<InventorySlot, 20> campStorageSlots;


};



