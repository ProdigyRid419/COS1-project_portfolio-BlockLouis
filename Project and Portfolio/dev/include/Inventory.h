#pragma once
#include "InventorySlot.h"
#include "DedicatedInventorySlot.h"
#include <array>

class Inventory {

public:

	void DisplayInventory() const;
	int AddItem(const Item& newItem, int amount);
	int RemoveItem(const Item& newItem, int);
	int GetItemCount(ItemID itemID) const;

private:

	std::array<InventorySlot, 10> inventorySlots;
	std::array<DedicatedInventorySlot, 7> dedicatedInventorySlots{

		DedicatedInventorySlot(DedicatedSlotType::LeatherGear),
		DedicatedInventorySlot(DedicatedSlotType::VineGear),
		DedicatedInventorySlot(DedicatedSlotType::Spear),
		DedicatedInventorySlot(DedicatedSlotType::Bow),
		DedicatedInventorySlot(DedicatedSlotType::Arrow),
		DedicatedInventorySlot(DedicatedSlotType::Axe),
		DedicatedInventorySlot(DedicatedSlotType::Pickaxe)

	};

};

