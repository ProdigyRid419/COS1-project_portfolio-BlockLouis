#include "Menu.h"
#include <iostream>

int Menu::DisplayMenu(MenuType menuType) {

	int minimum = 1;
	int maximum = 0;

	switch (menuType) {

	case MenuType::Main:

		std::cout << "=== Welcome to The Long Lost Isle ===\n\n1. Start Game\n2. Exit\nPlayer choice: ";
		maximum = 2;

		break;

	case MenuType::Camp:

		std::cout << "=== Camp ===\n\n1. View Status\n2. Sleep\n3. Show Inventory\n4. Explore\n5. Exit Game\nPlayer Choice: ";
		maximum = 5;

		break;

	case MenuType::Exploration:

		std::cout << "\n=== Exploration ===\n\n1. Search for New Location\n2. Travel to Known Location\n3. Return to Camp\nPlayer choice: ";
		maximum = 3;

		break;

	case MenuType::KnownLocations:

		std::cout << "\n=== Known Locations ===\n\n1. Forest\n2. Cave\n3. Back\nPlayer choice: ";
		maximum = 3;

		break;

	case MenuType::Location:

		std::cout << "=== Location Menu ===\n\n1. Gather Resources\n2. Show Inventory\n3. Leave Location\n";
		maximum = 3;

		break;

	case MenuType::YesNo:

		std::cout << "1. Yes\n2. No\nPlayer choice: ";
		maximum = 2;
		break;

	 }

	int menuChoice;
	std::cin >> menuChoice;

	while (menuChoice < minimum || menuChoice > maximum) {

		std::cout << "\n\nInput not valid! Please choose from the menu choices.\n";
		std::cin >> menuChoice;

	}

	return menuChoice;

}


