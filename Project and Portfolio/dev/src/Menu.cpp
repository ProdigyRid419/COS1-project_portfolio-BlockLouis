#include "Menu.h"
#include "GameClock.h"
#include <iostream>
#include <string>
#include "Location.h"
#include "Item.h"
#include "Crafting.h"
#include "Inventory.h"

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

		std::cout << "=== Camp ===\n\n1. View Status\n2. Sleep\n3. Show Inventory\n4. Crafting\n5. Explore\n6. Exit Game\nPlayer Choice: ";
		maximum = 6;

		break;

	case MenuType::Exploration:

		gameClock.DisplayTime();

		std::cout << "\n=== Exploration ===\n\n1. Search for New Location\n2. Travel to Known Location\n3. View Status\n4. Return to Camp\nPlayer choice: ";
		maximum = 4;

		break;

	case MenuType::KnownLocations:

		gameClock.DisplayTime();

		std::cout << "\n=== Known Locations ===\n\n1. Forest\n2. Cave\n3. Herbal Grove\n4. Boar Field\n5. Water Spring\n6. Spider Nest\n7. Back\nPlayer choice: ";
		maximum = 7;

		break;

	case MenuType::Location:

		gameClock.DisplayTime();

		std::cout << "=== Location Menu ===\n\n1. Gather Resources\n2. Show Inventory\n3. View Status\n4. Leave Location\nPlayer Choice: ";
		maximum = 4;

		break;

	case MenuType::YesNo:

		std::cout << "1. Yes\n2. No\nPlayer choice: ";
		maximum = 2;
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

