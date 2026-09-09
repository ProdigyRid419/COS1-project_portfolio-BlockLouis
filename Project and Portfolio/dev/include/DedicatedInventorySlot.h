#pragma once
#include "InventorySlot.h"

enum class DedicatedSlotType {

	VineGear, LeatherGear, Spear, Bow,
	Arrow, Axe, Pickaxe

};

class DedicatedInventorySlot : public InventorySlot {

public:
	
	DedicatedInventorySlot(DedicatedSlotType newSlotType);
	bool CanAcceptItem(const Item& newItem) const override;
	DedicatedSlotType GetSlotType() const;

private:

	DedicatedSlotType slotType;

};


