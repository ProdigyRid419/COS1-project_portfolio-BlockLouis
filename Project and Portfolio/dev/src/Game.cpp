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
#include <limits>

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
	
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, name);

	while (name.empty()) {

		std::cout << "Empty input detected. Please input your name: ";
		std::getline(std::cin, name);

	}

	Player1.SetName(name);

	std::cout << "\n\nWelcome to The Long Lost Isle " << Player1.GetName() << ", it's time for your survival journey to begin.\n\n";

	std::cout << "===============================================\n\nYou find yourself stranded on an island, the last thing you remember is being on a cruise vacationing from work.\n\nYou must have fallen off while nobody was around to alert anybody and now you are here.\n\nYou quickly gather materials to start a small survival camp, a pile of leaves to sleep on, a quick shelter to prevent\nrain or wind from being too much of a hassle, a small storage space, and you find a suspiciously table-like stump that could be used as a work station.\n\n";

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

			OpenCraftingMenu();
			break;

		case 5:

			Explore();
			break;

		case 6:

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

	int amountToGather = GetGatherAmount(selectedResource);

	if (amountToGather == 0) {

		std::cout << "You do not have the required tool to gather this item.\n";
		return;

	}

	int gatheredAmount = location.GatherResource(selectedResource, amountToGather);

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

			Location discoveredLocation(GenerateDiscoverableLocationType());
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

			for (int i = 0; i < static_cast<int>(knownLocations.size()); i++) {

				if (!knownLocations[i].has_value()) {

					continue;

				}

				if (knownLocations[i]->HasBeenVisited()) {

					DisplayLocationInfo(*knownLocations[i]);

				}
				else {

					DisplayLocationInfoDiscovery(*knownLocations[i]);

				}

			}

			int menuChoice = Menu::DisplayMenu(MenuType::KnownLocations, gameClock);
			int backChoice = static_cast<int>(knownLocations.size()) + 1;

			if (menuChoice == backChoice) {

				break;

			}
			
			int selectedIndex = menuChoice - 1;

			if (knownLocations[selectedIndex].has_value()) {

				TravelToLocation(*knownLocations[selectedIndex]);

			} else {

				std::cout << "\nNo known location of this type.\n";

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

	std::cout << GetLocationName(GetLocationIndex(location.GetLocType())) << '\n';

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

	std::cout << GetLocationName(GetLocationIndex(location.GetLocType())) << '\n';

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
		
	case LocationType::HerbalGrove:

		return 2;

	case LocationType::BoarField:

		return 3;

	case LocationType::WaterSpring:

		return 4;

	case LocationType::SpiderNest:

		return 5;

	}

	return -1;

}

std::string Game::GetLocationName(int locationIndex) {

	switch (locationIndex) {

	case 0: 

		return "Forest";

	case 1:

		return "Cave";

	case 2:

		return "Herbal Grove";

	case 3:

		return "Boar Field";

	case 4:

		return "Water Spring";

	case 5:

		return "Spider Nest";

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

void Game::OpenCraftingMenu() {

	const std::vector<CraftingRecipe>& recipes = craftingSystem.GetCraftingRecipes();

	while (true) {

		int recipeChoice = Menu::DisplayCraftingMenu(craftingSystem, Player1.GetInventory());
		int backChoice = static_cast<int>(recipes.size()) + 1;

		if (recipeChoice == backChoice) {

			return;

		}

		const CraftingRecipe& selectedRecipe = recipes[recipeChoice - 1];

		bool craftingSuccessful = craftingSystem.CraftItem(Player1.GetInventory(), selectedRecipe);
		if (craftingSuccessful) {

			std::cout << "\nSuccessfully crafted " << selectedRecipe.recipeResultAmount << ' ' << selectedRecipe.recipeName << '\n';

		} else {

			std::cout << "\nUnable to craft " << selectedRecipe.recipeName << ". You may be missing materials or inventory space.\n";

		}

	}

}

LocationType Game::GenerateDiscoverableLocationType() {

	std::vector<LocationType> discoverableLocations{ LocationType::Forest, LocationType::Cave, LocationType::HerbalGrove, LocationType::WaterSpring };

	if (Player1.GetInventory().GetItemCount(ItemID::Spear) > 0) {

		discoverableLocations.push_back(LocationType::BoarField);

	}

	if (Player1.GetInventory().GetItemCount(ItemID::Spear) > 0 && Player1.GetInventory().GetItemCount(ItemID::Bow) > 0) {

		discoverableLocations.push_back(LocationType::SpiderNest);

	}

	int randomIndex = rand() % static_cast<int>(discoverableLocations.size());
	return discoverableLocations[randomIndex];

}

int Game::GetGatherAmount(ItemID resourceType) {

	switch (resourceType) {

	case ItemID::Hardwood:

		if (Player1.GetInventory().GetItemCount(ItemID::MetalAxe) > 0) {

			return 5;

		} else if (Player1.GetInventory().GetItemCount(ItemID::StoneAxe) > 0) {

			return 3;

		} 

		return 0;

	case ItemID::TreeSap:

		if (Player1.GetInventory().GetItemCount(ItemID::FlintAxe) > 0 || Player1.GetInventory().GetItemCount(ItemID::StoneAxe) > 0 || Player1.GetInventory().GetItemCount(ItemID::MetalAxe) > 0) {

			return 5;

		}

		return 0;

	case ItemID::Stone:

		if (Player1.GetInventory().GetItemCount(ItemID::FlintPickaxe) > 0 || Player1.GetInventory().GetItemCount(ItemID::StonePickaxe) > 0 || Player1.GetInventory().GetItemCount(ItemID::MetalPickaxe) > 0) {

			return 5;

		}

		return 0;

	case ItemID::Metal:

		if (Player1.GetInventory().GetItemCount(ItemID::StonePickaxe) > 0) {

			return 3;

		} else if (Player1.GetInventory().GetItemCount(ItemID::MetalPickaxe) > 0) {

			return 5;

		}

		return 0;

	}

	return 5;

}
