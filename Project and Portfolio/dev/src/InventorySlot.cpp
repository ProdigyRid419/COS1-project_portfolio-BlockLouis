#include "InventorySlot.h"
#include <iostream>

InventorySlot::InventorySlot() {

	quantity = 0;

}

InventorySlot::InventorySlot(Item newItem, int newQuantity) {

	item = newItem;
	quantity = newQuantity;

}

const Item& InventorySlot::GetItem() const {

	return item;

}

int InventorySlot::GetQuantity() const {

	return quantity;

}

bool InventorySlot::IsEmpty() const {

	return item.GetID() == ItemID::Empty;

}

bool InventorySlot::CanAcceptItem(const Item& newItem) const {

	if (item.GetID() == ItemID::Empty) {

		return true;

	}
	else if (item.GetID() != newItem.GetID()) {

		return false;

	}
	else {

		if (item.IsStackable()) {

			if (quantity < item.GetMaxStack()) {

				return true;

			}

			return false;

		}

	}

	return false;

}

int InventorySlot::AddQuantity(const Item& newItem, int amount) {

		if (CanAcceptItem(newItem) == false) {

			return amount;

		}

		if (IsEmpty()) {

			item = newItem;

		}

		int availableSpace = item.GetMaxStack() - quantity;

		if (availableSpace >= amount) {

			quantity += amount;
			return 0;

		} else {

			quantity += availableSpace;
			return amount - availableSpace;

		}

}

int InventorySlot::RemoveQuantity(int amount) {

	if (IsEmpty()) {

		return amount;

	} else if (quantity >= amount) {

		quantity -= amount;
		if (quantity == 0) {

			item = Item();

		}
		return 0;

	} else {

		int remain = amount - quantity;
		quantity = 0;
		item = Item();
		return remain;

	}

}

bool InventorySlot::Save(std::ostream& output) const {

	if (!item.Save(output)) {

		return false;

	}

	output << quantity << '\n';
	return static_cast<bool>(output);

}

bool InventorySlot::Load(std::istream& input) {

	Item loadedItem;
	int loadedQuantity = 0;
	if (!loadedItem.Load(input)) {

		return false;

	}

	input >> loadedQuantity;
	if (!static_cast<bool>(input)) {

		return false;

	}

	if (loadedQuantity < 0 || loadedQuantity > loadedItem.GetMaxStack() || (loadedItem.GetID() != ItemID::Empty && loadedQuantity == 0)) {

		return false;

	}

	item = loadedItem;
	quantity = loadedQuantity;
	return true;

}
