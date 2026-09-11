#include "Game.h"
#include "Item.h"
#include "InventorySlot.h"
#include "DedicatedInventorySlot.h"
#include "Inventory.h"
#include <iostream>
#include <string>

#include "Location.h"

void Game::Run() {

	std::cout << "=== Welcome to The Long Lost Isle ===\n\n";

	int menuChoice;

	std::cout << "1. Start Game\n2. Exit\nPlayer choice: ";
	std::cin >> menuChoice;
	while (menuChoice != 1 && menuChoice != 2) {

		std::cout << "\n\nInput not valid! Please choose from the menu choices.\n";
		std::cin >> menuChoice;

	}

	switch (menuChoice) {

	case 1:

		StartGame();
		break;

	case 2:

		break;

	}

	

}

void Game::StartGame() {

	std::string name;
	int menuChoice;
	bool shouldKeepRunning = true;

	std::cout << "\n=======================================\n";

	std::cout << "\nPlease input your name: ";
	
	std::cin.ignore();
	std::getline(std::cin, name);

	Player1.SetName(name);

	std::cout << "\n\nWelcome to The Long Lost Isle " << Player1.GetName() << ", it's time for your survival journey to begin.\n\n";

	std::cout << "===============================================\n\nYou find yourself stranded on an island, the last thing you remember is being on a cruise vacationing from work.\n\nYou must have fallen off while nobody was around to alert anybody and now you are here.\n\nYou quickly gather materials to start a small survival camp, a pile of leaves to sleep on, a quick shelter to prevent\nrain or wind from being too much of a hassle, a small storage space, and you find a suspiciously table-like stump.\n\n";
	
	while (shouldKeepRunning) {

		std::cout << "=== Camp ===\n\n1. View Status\n2. Sleep\n3. Show Inventory\n4. Explore\n5. Exit Game\nPlayer Choice: ";
		std::cin >> menuChoice;
		while (menuChoice != 1 && menuChoice != 2 && menuChoice != 3 && menuChoice != 4 && menuChoice != 5) {

			std::cout << "\n\nInput not valid! Please choose from the menu choices.\n";
			std::cin >> menuChoice;

		}

		switch (menuChoice) {

		case 1:

			ViewStatus();
			break;

		case 2:

			Sleep();
			break;

		case 3:

			ShowInventory();
			break;

		case 4:

			Explore();
			break;

		case 5:

			shouldKeepRunning = false;
			break;

		}

	}

}

void Game::ViewStatus() {

	std::cout << "\n=== Player Status ===\n";

	int temp = Player1.GetTemp();

	std::cout << "\nTemperature: " << temp;

	if (temp >= 35 && temp <= 65) {

		std::cout << " (Comfortable)";

	} else if (temp < 35) {

		std::cout << " (Cold)";

	}
	else if (temp > 65) {

		std::cout << " (Hot)";

	}


	std::cout << "\nHealth: " << Player1.GetHealth();
	std::cout << "\nHunger: " << Player1.GetHunger();
	std::cout << "\nHydration: " << Player1.GetHydration();
	std::cout << "\nStamina: " << Player1.GetStamina();
	std::cout << "\nSanity: " << Player1.GetSanity() << "\n\n";

}

void Game::Sleep() {

	std::cout << "\n=== Sleep ===\n\nYou sleep for 8 hours.\nYour Hunger and Hydration have decreased by 10.\n\n";
	
	Player1.DecreaseHungerSleep();
	Player1.DecreaseHydrationSleep();

}

void Game::ShowInventory() {

	Player1.GetInventory().DisplayInventory();

}

void Game::GatherFromLocation(Location& location) {

	std::cout << "\nYou gather materials.";

	int gatheredamount = location.GatherResource();

	if (gatheredamount > 0) {

		Item resourceType = location.GetResourceType();
		int remaining = Player1.GetInventory().AddItem(resourceType, gatheredamount);

		if (remaining > 0) {

			location.RestoreResource(remaining);

		}

	}
	
}

void Game::Explore() {

	bool exploring = true;

	while (exploring) {

		std::cout << "\n=== Exploration ===\n\n1. Search for New Location\n2. Travel to Known Location\n3. Return to Camp\nPlayer choice: ";

		int menuChoice;

		std::cin >> menuChoice;

		while (menuChoice != 1 && menuChoice != 2 && menuChoice != 3) {

			std::cout << "\nInput not valid! Please choose from the menu choices.\n";
			std::cin >> menuChoice;

		}

		switch (menuChoice) {

		case 1: {

			Location discoveredLocation;

			switch (discoveredLocation.GetLocType()) {

			case LocationType::Forest:

				if (!knownLocations[0].has_value()) {

					knownLocations[0] = discoveredLocation;
					DisplayLocationInfoDiscovery(discoveredLocation);

					std::cout << "This location has been saved in your known locations.\nWould you like to visit this Location?\n\n1. Yes\n2. No\n";

					std::cin >> menuChoice;

					while (menuChoice != 1 && menuChoice != 2) {

						std::cout << "\nInput not valid! Please choose from the menu choices.\nPlayer choice: ";
						std::cin >> menuChoice;

					}

					switch (menuChoice) {

					case 1:

						VisitLocation(*knownLocations[0]);
						break;

					case 2:
						
						break;

					}

				}
				else {


					DisplayLocationInfoDiscovery(discoveredLocation);

					int menuChoice;

					std::cout << "Would you like to visit this Location?\n\n1. Yes\n2. No\nPlayer choice: ";

					std::cin >> menuChoice;

					while (menuChoice != 1 && menuChoice != 2) {

						std::cout << "\nInput not valid! Please choose from the menu choices.\n";
						std::cin >> menuChoice;

					}

					switch (menuChoice) {

					case 1: {

						VisitLocation(discoveredLocation);

						int menuChoice1;

						std::cout << "Would you like to replace your currently known Forest with this newly discovered Forest?\n\n1. Yes\n2. No\nPlayer choice: ";
						std::cin >> menuChoice1;

						while (menuChoice1 != 1 && menuChoice1 != 2) {

							std::cout << "\nInput not valid! Please choose from the menu choices.\n";
							std::cin >> menuChoice1;

						}

						switch (menuChoice1) {

						case 1:

							knownLocations[0] = discoveredLocation;
							break;

						case 2:

							break;

						}

						break;

					}

					case 2:

						break;

					}

				}
				break;

			case LocationType::Cave:

				if (!knownLocations[1].has_value()) {

					knownLocations[1] = discoveredLocation;
					DisplayLocationInfoDiscovery(discoveredLocation);

					std::cout << "This location has been saved in your known locations.\nWould you like to visit this Location?\n\n1. Yes\n2. No\nPlayer choice: ";

					std::cin >> menuChoice;

					while (menuChoice != 1 && menuChoice != 2) {

						std::cout << "\nInput not valid! Please choose from the menu choices.\n";
						std::cin >> menuChoice;

					}

					switch (menuChoice) {

					case 1:

						VisitLocation(*knownLocations[1]);
						break;

					case 2:

						break;

					}

				}
				else {

					DisplayLocationInfoDiscovery(discoveredLocation);

					int menuChoice;

					std::cout << "Would you like to visit this Location?\n\n1. Yes\n2. No\nPlayer Choice: ";

					std::cin >> menuChoice;

					while (menuChoice != 1 && menuChoice != 2) {

						std::cout << "\nInput not valid! Please choose from the menu choices.\n";
						std::cin >> menuChoice;

					}

					switch (menuChoice) {

					case 1: {

						VisitLocation(discoveredLocation);

						int menuChoice1;

						std::cout << "Would you like to replace your currently known Cave with this newly discovered Cave?\n\n1. Yes\n2. No\nPlayer choice: ";
						std::cin >> menuChoice1;

						while (menuChoice1 != 1 && menuChoice1 != 2) {

							std::cout << "\nInput not valid! Please choose from the menu choices.\n";
							std::cin >> menuChoice1;

						}

						switch (menuChoice1) {

						case 1:

							knownLocations[1] = discoveredLocation;
							break;

						case 2:

							break;

						}
						break;

					}

					case 2:

						break;

					}

				}

				break;

			}

			break;

		}

		case 2: {

			std::cout << "\n=== Known Locations ===\n\n1. Forest";
			
			if (knownLocations[0].has_value()) {

				DisplayLocationInfo(*knownLocations[0]);

			}

			std::cout << "\n2. Cave\n";
			
			if (knownLocations[1].has_value()) {

				DisplayLocationInfo(*knownLocations[1]);

			}

			std::cout << "\n3.Back\nPlayer choice : ";
			int menuChoice;
			std::cin >> menuChoice;

			while (menuChoice != 1 && menuChoice != 2 && menuChoice != 3) {

				std::cout << "\nInput not valid! Please choose from the menu choices.\n";
				std::cin >> menuChoice;

			}

			switch (menuChoice) {

			case 1:

				if (knownLocations[0].has_value()) {

					VisitLocation(*knownLocations[0]);

				}
				else {

					std::cout << "No known location of this type.\n";

				}
				break;

			case 2:

				if (knownLocations[1].has_value()) {

					VisitLocation(*knownLocations[1]);

				}
				else {

					std::cout << "No known location of this type.\n";

				}
				break;

			case 3:

				break;

			}

			break;

		}

		case 3:

			exploring = false;
			break;

		}

	}

}

void Game::VisitLocation(Location& location) {

	bool visiting = true;

	while (visiting) {

		DisplayLocationInfo(location);

		std::cout << "=== Location Menu ===\n\n1. Gather Resources\n2. Show Inventory\n3. Leave Location\n";

		int menuChoice;
		std::cin >> menuChoice;

		while (menuChoice != 1 && menuChoice != 2 && menuChoice != 3) {

			std::cout << "\nInput not valid! Please choose from the menu choices.\n";
			std::cin >> menuChoice;

		}

		switch (menuChoice) {

		case 1:

			GatherFromLocation(location);
			break;

		case 2:

			ShowInventory();
			break;

		case 3:
			
			std::cout << "\n\nYou leave the location.\n\n";
			visiting = false;
			break;

		}

	}

}

void Game::DisplayLocationInfo(const Location& location) {

	std::cout << "\n\n=== Location Information ===\n\n";

	switch (location.GetLocSize()) {

	case LocationSize::Small:

		std::cout << "Small ";
		break;

	case LocationSize::Medium:

		std::cout << "Medium ";
		break;

	case LocationSize::Large:

		std::cout << "Large ";
		break;

	}

	switch (location.GetLocType()) {

	case LocationType::Forest:

		std::cout << "Forest\n";
		break;

	case LocationType::Cave:

		std::cout << "Cave\n";
		break;

	}

	switch (location.GetTravelTime()) {

	case 1:

		std::cout << "Travel Time: 1 hour\n";
		break;

	case 2:

		std::cout << "Travel Time: 2 hours\n";
		break;

	case 3:

		std::cout << "Travel Time: 3 hours\n";
		break;


	}

	switch (location.GetResourceType()) {

	case ItemID::CrudeWood:

		std::cout << "Resource Type: Crude Wood\n";
		break;

	case ItemID::Flint:

		std::cout << "Resource Type: Flint\n";
		break;

	}

	std::cout << "Remaining Resource Amount: " << location.GetResourceAmount() << "\n\n";

}

void Game::DisplayLocationInfoDiscovery(const Location& location) {

	std::cout << "\n\n=== Location Information ===\n\n";

	switch (location.GetLocType()) {

	case LocationType::Forest:

		std::cout << "Forest\n";
		break;

	case LocationType::Cave:

		std::cout << "Cave\n";
		break;

	}

	switch (location.GetTravelTime()) {

	case 1:

		std::cout << "Travel Time: 1 hour\n";
		break;

	case 2:

		std::cout << "Travel Time: 2 hours\n";
		break;

	case 3:

		std::cout << "Travel Time: 3 hours\n";
		break;


	}

	switch (location.GetResourceType()) {

	case ItemID::CrudeWood:

		std::cout << "Resource Type: Crude Wood\n";
		break;

	case ItemID::Flint:

		std::cout << "Resource Type: Flint\n";
		break;

	}

}

