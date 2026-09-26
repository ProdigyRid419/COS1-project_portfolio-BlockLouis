#pragma once
#include "Item.h"
#include <iosfwd>

class InventorySlot {

public:

	InventorySlot();
	InventorySlot(Item item, int quantity);

	const Item& GetItem() const;
	int GetQuantity() const;

	bool IsEmpty() const;
	virtual bool CanAcceptItem(const Item& newItem) const;

	int AddQuantity(const Item& newItem, int amount);
	int RemoveQuantity(int amount);

	bool Save(std::ostream& output) const;
	bool Load(std::istream& input);

private:

	Item item;
	int quantity;

};
