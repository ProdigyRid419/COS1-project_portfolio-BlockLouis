#include "Game.h"
#include "Item.h"
#include "InventorySlot.h"
#include "DedicatedInventorySlot.h"
#include "Inventory.h"
#include <iostream>
#include <string>
#include "Menu.h"
#include "Location.h"
#include "GameClock.h"
#include <iomanip>

void Game::Run() {

	int menuChoice = Menu::DisplayMenu(MenuType::Main, gameClock);

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
	bool shouldKeepRunning = true;

	std::cout << "\n=======================================\n";

	std::cout << "\nPlease input your name: ";
	
	std::cin.ignore();
	std::getline(std::cin, name);

	while (name.empty()) {

		std::cout << "Empty input detected. Please input your name: ";
		std::getline(std::cin, name);

	}

	Player1.SetName(name);

	std::cout << "\n\nWelcome to The Long Lost Isle " << Player1.GetName() << ", it's time for your survival journey to begin.\n\n";

	std::cout << "===============================================\n\nYou find yourself stranded on an island, the last thing you remember is being on a cruise vacationing from work.\n\nYou must have fallen off while nobody was around to alert anybody and now you are here.\n\nYou quickly gather materials to start a small survival camp, a pile of leaves to sleep on, a quick shelter to prevent\nrain or wind from being too much of a hassle, a small storage space, and you find a suspiciously table-like stump.\n\n";

	while (shouldKeepRunning) {

		int menuChoice = Menu::DisplayMenu(MenuType::Camp, gameClock);

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


	std::cout << std::fixed << std::setprecision(2) << "\nHealth: " << Player1.GetHealth();
	std::cout << "\nHunger: " << Player1.GetHunger();
	std::cout << "\nHydration: " << Player1.GetHydration();
	std::cout << "\nStamina: " << Player1.GetStamina();
	std::cout << "\nSanity: " << Player1.GetSanity() << "\n\n";

}

void Game::Sleep() {

	std::cout << "\n=== Sleep ===\n\nYou sleep for 8 hours.\nYour Hunger and Hydration have decreased by 10.\n\n";
	ProcessTime(32, ActivityLevel::Normal);

}

void Game::ShowInventory() {

	Player1.GetInventory().DisplayInventory();

}

void Game::GatherFromLocation(Location& location) {

	const std::vector<LocationResource>& resources = location.GetLocationResources();

	int resourceChoice = Menu::DisplayResourceMenu(location); 

	int backChoice = static_cast<int>(resources.size()) + 1;

	if (resourceChoice == backChoice) {

		return;

	} 

	ItemID selectedResource = resources[resourceChoice - 1].resourceType;

	int gatheredAmount = location.GatherResource(selectedResource, 5);

	if (gatheredAmount > 0) {

		Item resourceType = selectedResource;
		int remaining = Player1.GetInventory().AddItem(resourceType, gatheredAmount);

		std::cout << "\nYou gathered " << gatheredAmount - remaining << " materials.\n";

		if (remaining > 0) {

			location.RestoreResource(selectedResource, remaining);

			if (remaining == gatheredAmount) {

				std::cout << "No resources gathered. Your inventory is full!!!\n";

			} else if (remaining < gatheredAmount) {

				std::cout << "Your inventory is now full.\n" << remaining << " resources were not collected because you ran out of inventory space.\n";

			}
			
		}

		ProcessTime(1, ActivityLevel::Strenuous);

	} else {

		std::cout << "The Location has no more resources to gather. Come back tomorrow.\n";

	}
	
}

void Game::Explore() {

	bool exploring = true;

	while (exploring) {

		std::cout << '\n';

		int exploreChoice = Menu::DisplayMenu(MenuType::Exploration, gameClock);

		switch (exploreChoice) {

		case 1: {

			Location discoveredLocation;
			int locationIndex = GetLocationIndex(discoveredLocation.GetLocType());

			if (locationIndex != -1) {

				if (!knownLocations[locationIndex].has_value()) {

					knownLocations[locationIndex] = discoveredLocation;
					DisplayLocationInfoDiscovery(discoveredLocation);

					std::cout << "This location has been saved in your known locations.\nWould you like to visit this Location?\n\n";

					int yesNoChoice = Menu::DisplayMenu(MenuType::YesNo, gameClock);

					if (yesNoChoice == 1) {

						TravelToLocation(*knownLocations[locationIndex]);

					}

				}
				else {

					DisplayLocationInfoDiscovery(discoveredLocation);

					std::cout << "Would you like to visit this Location?\n\n";

					int yesNoChoice = Menu::DisplayMenu(MenuType::YesNo, gameClock);

					if (yesNoChoice == 1) {

						TravelToLocation(discoveredLocation);

						std::cout << "Would you like to replace your currently known " << GetLocationName(locationIndex) << " with this newly discovered " << GetLocationName(locationIndex) << "?\n\n";

						int replaceChoice = Menu::DisplayMenu(MenuType::YesNo, gameClock);

						if (replaceChoice == 1) {

							knownLocations[locationIndex] = discoveredLocation;

						}

					}

				}
			}

			break;

		}

		case 2: {

			if (knownLocations[0].has_value()) {

				if (knownLocations[0]->HasBeenVisited()) {

					DisplayLocationInfo(*knownLocations[0]);
					
				} else {

					DisplayLocationInfoDiscovery(*knownLocations[0]);
					
				}

			}

			if (knownLocations[1].has_value()) {

				if (knownLocations[1]->HasBeenVisited()) {

					DisplayLocationInfo(*knownLocations[1]);
					
				} else {

					DisplayLocationInfoDiscovery(*knownLocations[1]);
					
				}

			}

			int menuChoice = Menu::DisplayMenu(MenuType::KnownLocations, gameClock);

			switch (menuChoice) {

			case 1:

				if (knownLocations[0].has_value()) {

					TravelToLocation(*knownLocations[0]);

				}
				else {

					std::cout << "No known location of this type.\n";

				}
				break;

			case 2:

				if (knownLocations[1].has_value()) {

					TravelToLocation(*knownLocations[1]);

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

			ViewStatus();
			break;

		case 4:

			exploring = false;
			break;

		}

	}

}

void Game::VisitLocation(Location& location) {

	bool visiting = true;

	while (visiting) {

		DisplayLocationInfo(location);

		int menuChoice = Menu::DisplayMenu(MenuType::Location, gameClock);

		switch (menuChoice) {

		case 1:

			GatherFromLocation(location);
			break;

		case 2:

			ShowInventory();
			break;

		case 3:

			ViewStatus();
			break;

		case 4:
			
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

		std::cout << "Round-trip Travel Time: 1 hour\n";
		break;

	case 2:

		std::cout << "Round-trip Travel Time: 2 hours\n";
		break;

	case 3:

		std::cout << "Round-trip Travel Time: 3 hours\n";
		break;


	}

	std::cout << "\n\n=== Location Resources ===\n\n";

	for (const LocationResource& resource : location.GetLocationResources()) {

		Item tempItem(resource.resourceType);
		std::cout << tempItem.GetName() << ": " << resource.resourceAmount << " Remaining.\n";

	}

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

		std::cout << "Round-Trip Travel Time: 1 hour\n";
		break;

	case 2:

		std::cout << "Round-Trip Travel Time: 2 hours\n";
		break;

	case 3:

		std::cout << "Round-Trip Travel Time: 3 hours\n";
		break;


	}

	std::cout << "\n\n=== Location Resources ===\n\n";

	for (const LocationResource& resource : location.GetLocationResources()) {

		Item tempItem(resource.resourceType);
		std::cout << tempItem.GetName() << '\n';

	}

	std::cout << '\n';

}

int Game::GetLocationIndex(LocationType locationType) {

	switch (locationType) {

	case LocationType::Forest:

		return 0;
		
	case LocationType::Cave:

		return 1;
		
	}

	return -1;

}

std::string Game::GetLocationName(int locationIndex) {

	switch (locationIndex) {

	case 0: 

		return "Forest";

	case 1:

		return "Cave";

	}

	return "Unknown";

}

void Game::ProcessTime(int fifteenMinuteIntervals, ActivityLevel activityLevel) {

	for (int i = 0; i < fifteenMinuteIntervals; i++) {

		gameClock.AdvanceTime(1);
		DrainResult statDrain = playerDrain.CalculateDrain(gameClock, activityLevel);
		if (statDrain.hungerDrain > 0 && Player1.GetHunger() > 0) {

			Player1.DecreaseHunger(statDrain.hungerDrain);

		}

		if (statDrain.hydrationDrain > 0 && Player1.GetHydration() > 0) {

			Player1.DecreaseHydration(statDrain.hydrationDrain);
			
		}

		if (statDrain.staminaDrain > 0 && Player1.GetStamina() > 0) {

			Player1.DecreaseStamina(statDrain.staminaDrain);

		}

		if (statDrain.sanityDrain > 0 && Player1.GetSanity() > 0) {

			Player1.DecreaseSanity(statDrain.sanityDrain);

		}

	}

}

void Game::TravelToLocation(Location& location) {
	
	std::cout << "You travel to a " << GetLocationName(GetLocationIndex(location.GetLocType()));

	ProcessTime((location.GetTravelTime() * 2), ActivityLevel::Strenuous);

	location.MarkVisited();

	std::cout << "\nThis is a ";
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
	std::cout << GetLocationName(GetLocationIndex(location.GetLocType())) << ".\n";

	VisitLocation(location);

	ProcessTime((location.GetTravelTime() * 2), ActivityLevel::Strenuous);

}
