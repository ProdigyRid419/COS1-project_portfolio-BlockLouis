#pragma once
#include "InventorySlot.h"
#include <array>
#include <iosfwd>

class CampStorage {

public:

	int AddItem(const Item& newItem, int amount);
	int RemoveItem(const Item& newItem, int amount);
	int GetItemCount(ItemID itemID) const;
	void DisplayCampStorage() const;
	const std::array<InventorySlot, 20>& GetCampStorageSlots() const;

	bool Save(std::ostream& output) const;
	bool Load(std::istream& input);

private:

	std::array<InventorySlot, 20> campStorageSlots;


};



