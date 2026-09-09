#pragma once
#include "Item.h"

class InventorySlot {

public:

	InventorySlot();
	InventorySlot(Item item, int quantity);

	const Item& GetItem() const;
	int GetQuantity() const;

	bool IsEmpty() const;
	bool CanAcceptItem(const Item& newItem) const;

	int AddQuantity(const Item& newItem, int amount);
	int RemoveQuantity(int amount);

private:

	Item item;
	int quantity;

};
