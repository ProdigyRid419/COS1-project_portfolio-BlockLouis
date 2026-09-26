#pragma once
#include "InventorySlot.h"
#include "DedicatedInventorySlot.h"
#include <array>
#include <iosfwd>

class Inventory {

public:

	void DisplayInventory() const;
	int AddItem(const Item& newItem, int amount);
	int RemoveItem(const Item& newItem, int);
	int GetItemCount(ItemID itemID) const;

	const std::array<InventorySlot, 10>& GetInventorySlots() const;

	int GetStoredWater() const;
	int GetWaterCapacity() const;
	int FillWaterContainer();
	int RemoveWater(int amount);

	bool ConsumeWater();

	bool Save(std::ostream& output) const;
	bool Load(std::istream& input);

private:

	std::array<InventorySlot, 10> inventorySlots;
	std::array<DedicatedInventorySlot, 10> dedicatedInventorySlots{

		DedicatedInventorySlot(DedicatedSlotType::LeatherGear),
		DedicatedInventorySlot(DedicatedSlotType::VineGear),
		DedicatedInventorySlot(DedicatedSlotType::Spear),
		DedicatedInventorySlot(DedicatedSlotType::Bow),
		DedicatedInventorySlot(DedicatedSlotType::FlintArrow),
		DedicatedInventorySlot(DedicatedSlotType::StoneArrow),
		DedicatedInventorySlot(DedicatedSlotType::MetalArrow),
		DedicatedInventorySlot(DedicatedSlotType::Axe),
		DedicatedInventorySlot(DedicatedSlotType::Pickaxe),
		DedicatedInventorySlot(DedicatedSlotType::WaterContainer)

	};

	int storedWater = 0;

};

