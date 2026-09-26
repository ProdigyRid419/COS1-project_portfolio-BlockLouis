#pragma once
#include "InventorySlot.h"
#include <iosfwd>

enum class DedicatedSlotType {

	VineGear, LeatherGear, Spear, Bow,
	FlintArrow, StoneArrow, MetalArrow,
	Axe, Pickaxe, WaterContainer

};

class DedicatedInventorySlot : public InventorySlot {

public:
	
	DedicatedInventorySlot(DedicatedSlotType newSlotType);
	bool CanAcceptItem(const Item& newItem) const override;
	DedicatedSlotType GetSlotType() const;
	bool Load(std::istream& input);

private:

	DedicatedSlotType slotType;

};


