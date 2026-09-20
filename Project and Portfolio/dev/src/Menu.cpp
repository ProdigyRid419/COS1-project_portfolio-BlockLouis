#include "Menu.h"
#include "GameClock.h"
#include <iostream>
#include <string>
#include "Location.h"
#include "Item.h"
#include "Crafting.h"
#include "Inventory.h"
#include "CampStorage.h"

int Menu::DisplayMenu(MenuType menuType, const GameClock& gameClock) {

	int minimum = 1;
	int maximum = 0;

	switch (menuType) {

	case MenuType::Main:

		std::cout << "=== Welcome to The Long Lost Isle ===\n\n1. Start Game\n2. Exit\nPlayer choice: ";
		maximum = 2;

		break;

	case MenuType::Camp:

		gameClock.DisplayTime();

		std::cout << "=== Camp ===\n\n1. View Status\n2. Sleep\n3. Rest\n4. Show Inventory\n5. Crafting\n6. Campfire\n7. Camp Storage\n8. Explore\n9. Exit Game\nPlayer Choice: ";
		maximum = 9;

		break;

	case MenuType::Exploration:

		gameClock.DisplayTime();

		std::cout << "\n=== Exploration ===\n\n1. Search for New Location\n2. Travel to Known Location\n3. View Status\n4. Rest\n5. Return to Camp\nPlayer choice: ";
		maximum = 5;

		break;

	case MenuType::KnownLocations:

		gameClock.DisplayTime();

		std::cout << "\n=== Known Locations ===\n\n1. Forest\n2. Cave\n3. Herbal Grove\n4. Boar Field\n5. Water Spring\n6. Spider Nest\n7. Back\nPlayer choice: ";
		maximum = 7;

		break;

	case MenuType::Location:

		gameClock.DisplayTime();

		std::cout << "=== Location Menu ===\n\n1. Gather Resources\n2. Show Inventory\n3. View Status\n4. Rest\n5. Leave Location\nPlayer Choice: ";
		maximum = 5;

		break;

	case MenuType::YesNo:

		std::cout << "1. Yes\n2. No\nPlayer choice: ";
		maximum = 2;
		break;

	case MenuType::BoarField:

		gameClock.DisplayTime();

		std::cout << "\n\n=== Boar Field ===\n\n1. Hunt boars\n2. Process boar carcass\n3. Show inventory\n4. View status\n5. Rest\n6. Leave location\n";
		maximum = 6;
		break;

	case MenuType::BoarCarcass:

		std::cout << "\n\n=== Boar Carcasses ===\n\n1. Carve carcass (More meat than leather)\n2. Skin carcass (more leather than meat)\n3. Back\nPlayer choice: ";
		maximum = 3;
		break;

	case MenuType::WaterSpring:

		gameClock.DisplayTime();

		std::cout << "\n\n=== Water Spring ===\n\n1. Fill water container\n2. Show inventory\n3. View status\n4. Rest\n5. Leave location\nPlayer choice: ";
		maximum = 5;
		break;

	case MenuType::CampStorage:

		gameClock.DisplayTime();

		std::cout << "1. Deposit item\n2. Withdraw item\n3. Back\nPlayer choice: ";
		maximum = 3;
		break;

	}

	return GetValidatedChoice(minimum, maximum);

}

int Menu::GetValidatedChoice(int minimum, int maximum) {

	int intMenuChoice;

	while (true) {

		std::string menuChoice;
		std::cin >> menuChoice;

		bool isInt = true;

		for (char character : menuChoice) {

			if (character < '0' || character > '9') {

				isInt = false;
				break;

			}

		}

		if (!isInt) {

			std::cout << "\n\nInput not valid! Please choose from the menu choices.\nPlayer Choice\n";
			continue;

		}

		intMenuChoice = std::stoi(menuChoice);

		if (intMenuChoice < minimum || intMenuChoice > maximum) {

			std::cout << "\n\nInput not valid! Please choose from the menu choices.\nPlayer Choice\n";
			continue;

		}

		return intMenuChoice;

	}

}

int Menu::DisplayResourceMenu(const Location& location) {

	int i = 0;
		
	std::cout << "\n\n=== Location Resources ===\n\n";

	for (const LocationResource& resource : location.GetLocationResources()) {
		
		Item tempItem(resource.resourceType);
		std::cout << i + 1 << ". " << tempItem.GetName() << ": x" << resource.resourceAmount << '\n';
		i++;

	}

	std::cout << i + 1 << ". Back\nPlayer choice: ";

	return GetValidatedChoice(1, i + 1);

}

int Menu::DisplayCraftingMenu(const Crafting& craftingSystem, const Inventory& inventory) {

	const std::vector<CraftingRecipe>& recipes = craftingSystem.GetCraftingRecipes();

	int i = 0;

	std::cout << "\n\n=== Crafting ===\n\n";

	for (const CraftingRecipe& recipe : recipes) {

		std::cout << i + 1 << ". " << recipe.recipeName << '\n';

		for (const RecipeIngredient& ingredient : recipe.ingredients) {

			Item ingredientItem(ingredient.ingredientType);
			int ownedAmount = inventory.GetItemCount(ingredient.ingredientType);
			std::cout << ingredientItem.GetName() << ": " << ownedAmount << '/' << ingredient.requiredAmount << ".\n";

		}

		std::cout << '\n';
		i++;

	}

	std::cout << i + 1 << ". Back\nPlayer choice: ";

	return GetValidatedChoice(1, i + 1);

}

int Menu::DisplayCampfireMenu(const Campfire& campfire, const GameClock& gameClock) {

	gameClock.DisplayTime();

	std::cout << "\n\n=== Campfire ===\n\n";

	if (!campfire.IsBuilt()) {

		std::cout << "The campfire has not been built yet.\n\n1. Build campfire\n2. Back\nPlayer choice: ";
		return GetValidatedChoice(1, 2);

	}

	std::cout << "Remaining fuel: " << (campfire.GetFuelMinutes() / 60) << " hours and " << (campfire.GetFuelMinutes() % 60) << " minutes.\n\n1. Add fuel\n2. Cook meat\n3. Back\nPlayer choice: ";
	return GetValidatedChoice(1, 3);

}

int Menu::DisplayFuelAmountMenu(int playerWood, int fuelFireCanAccept) {

	int maximumFuelAmount = playerWood;

	if (fuelFireCanAccept < playerWood) {

		maximumFuelAmount = fuelFireCanAccept;

	}

	std::cout << "\n\n=== Add Fuel ===\n\nYou have " << playerWood << " Crude Wood.\nEach Crude wood will add one hour of fuel, up to 8 hours.\n";
	
	int i;

	for (i = 1; i <= maximumFuelAmount; i++) {

		std::cout << i << ". " << i << " Crude Wood\n";

	}

	std::cout << maximumFuelAmount + 1 << ". Back\nPlayer choice: ";

	int validatedResult = GetValidatedChoice(1, maximumFuelAmount + 1);

	if (validatedResult == (maximumFuelAmount + 1)) {

		return 0;

	}

	return validatedResult;

}

int Menu::DisplayCookingMenu(int playerMeat) {

	std::cout << "\n\n=== Cook Meat ===\n\nYou have " << playerMeat << " uncooked meat.\n";
	int maximumCookableMeat = 3;

	if (playerMeat < maximumCookableMeat) {

		maximumCookableMeat = playerMeat;

	}

	int i;

	for (i = 1; i <= maximumCookableMeat; i++) {

		std::cout << i << ". Cook " << i << " raw meat.\n";

	}

	std::cout << i  << ". Back\nPlayer choice: ";

	int validatedResult = GetValidatedChoice(1, i);

	if (validatedResult == i) {

		return 0;

	}

	return validatedResult;

}

int Menu::DisplayConsumableMenu(const Inventory& inventory) {

	std::cout << "\n\n=== Consumables ===\n\n1. Raw meat\nAmount: " << inventory.GetItemCount(ItemID::RawMeat) << "\n2. Cooked meat\nAmount: " << inventory.GetItemCount(ItemID::CookedMeat) << "\n3. Water\nAmount: " << inventory.GetStoredWater() << "\n4. Back\nPlayer choice: ";

	int validatedResult = GetValidatedChoice(1, 4);
	return validatedResult;

}

int Menu::DisplayInventorySlotSelection(const Inventory& inventory) {

	int menuNumber = 1;

	for (const InventorySlot& slot : inventory.GetInventorySlots()) {

		std::cout << menuNumber << ". " << slot.GetItem().GetName() << "\tAmount: " << slot.GetQuantity() << '\n';
		menuNumber++;

	}

	std::cout << menuNumber << ". Back\nPlayer choice: ";

	int validatedResult = GetValidatedChoice(1, menuNumber);

	return validatedResult;

}

int Menu::DisplayQuantityMenu(const Item& item, int availableQuantity) {

	if (availableQuantity <= 0) {

		return 0;

	}

	std::cout << "\n\n=== Quantity Selection ===\n\n" << item.GetName() << "\tAvailable quantity: " << availableQuantity << "\n";

	for (int i = 1; i <= availableQuantity; i++) {

		std::cout << i << ". " << i << '\n';

	}

	std::cout << availableQuantity + 1 << ". Back\nPlayer choice: ";

	int validatedChoice = GetValidatedChoice(1, availableQuantity + 1);

	if (validatedChoice == availableQuantity + 1) {

		return 0;

	}

	return validatedChoice;

}

int Menu::DisplayStorageSlotSelection(const CampStorage& campStorage) {

	int menuNumber = 1;

	for (const InventorySlot& storageSlot : campStorage.GetCampStorageSlots()) {

		std::cout << menuNumber << ". " << storageSlot.GetItem().GetName() << "\tAmount: " << storageSlot.GetQuantity() << '\n';

		menuNumber++;

	}

	std::cout << menuNumber << ". Back\nPlayer choice: ";

	int validatedChoice = GetValidatedChoice(1, menuNumber);

	return validatedChoice;

}
