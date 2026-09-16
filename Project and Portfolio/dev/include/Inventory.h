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

	int GetStoredWater() const;
	int GetWaterCapacity() const;
	int FillWaterContainer();

private:

	std::array<InventorySlot, 10> inventorySlots;
	std::array<DedicatedInventorySlot, 8> dedicatedInventorySlots{

		DedicatedInventorySlot(DedicatedSlotType::LeatherGear),
		DedicatedInventorySlot(DedicatedSlotType::VineGear),
		DedicatedInventorySlot(DedicatedSlotType::Spear),
		DedicatedInventorySlot(DedicatedSlotType::Bow),
		DedicatedInventorySlot(DedicatedSlotType::Arrow),
		DedicatedInventorySlot(DedicatedSlotType::Axe),
		DedicatedInventorySlot(DedicatedSlotType::Pickaxe),
		DedicatedInventorySlot(DedicatedSlotType::WaterContainer)

	};

	int storedWater = 0;

};

