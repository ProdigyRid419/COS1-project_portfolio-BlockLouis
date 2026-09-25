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
#include "SaveSystem.h"


void Game::Run() {

	int menuChoice = Menu::DisplayMenu(MenuType::Main, gameClock);

	switch (menuChoice) {

	case 1:

		StartGame();
		break;

	case 2:

		ContinueSavedGame();
		break;

	case 3:

		break;

	}

}

void Game::StartGame() {

	std::string name;
	
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

	std::cout << "===============================================\n\nYou find yourself stranded on an island, the last thing you remember is being on a cruise vacationing from work.\n\nYou must have fallen off while nobody was around to alert anybody and now you are here.\n\nYou quickly gather materials to start a small survival camp, a pile of leaves to sleep on, a quick shelter to prevent\nrain or wind from being too much of a hassle, a small storage space,\nand you find a suspiciously table-like stump that could be used as a work station.\n\n";

	Player1.SetTemp(gameWeather.GetTemp());

	CaptureDailyCheckpoint();

	RunCampLoop();

}

void Game::ViewStatus() {

	gameWeather.DisplayWeather();

	std::cout << "\n=== Player Status ===\n";

	int temp = Player1.GetTemp();

	std::cout << "\nTemperature: " << temp;

	if (temp > 34 && temp < 75) {

		std::cout << " (Comfortable)";

	} else if (temp < 35) {

		std::cout << " (Cold)";

	}
	else if (temp > 74) {

		std::cout << " (Hot)";

	}


	std::cout << std::fixed << std::setprecision(2) << "\nHealth: " << Player1.GetHealth();
	std::cout << "\nHunger: " << Player1.GetHunger();
	std::cout << "\nHydration: " << Player1.GetHydration();
	std::cout << "\nStamina: " << Player1.GetStamina();
	std::cout << "\nSanity: " << Player1.GetSanity() << "\n\n";

}

void Game::Sleep() {

	std::cout << "\n=== Sleep ===\n\n";
	ProcessTime(32, ActivityLevel::Normal);

	if (Player1.GetHealth() <= 0) {

		return;

	}

	std::cout << "You sleep for 8 hours.\n";

	Player1.RestoreStamina(100.0);

}

void Game::ShowInventory() {

	bool viewing = true;

	while (viewing) {

		Player1.GetInventory().DisplayInventory();
		
		int menuChoice = Menu::DisplayConsumableMenu(Player1.GetInventory());

		switch (menuChoice) {

		case 1:

			ConsumeFood(ItemID::RawMeat);
			break;

		case 2:

			ConsumeFood(ItemID::CookedMeat);
			break;

		case 3:

			ConsumeWater();
			break;

		case 4:

			UseBandage(ItemID::BasicBandage);
			break;

		case 5:

			UseBandage(ItemID::ImprovedBandage);
			break;

		case 6:

			viewing = false;
			break;

		}

	}

}

void Game::GatherFromLocation(Location& location) {

	if (!CanPerformStrenuousAction()) {

		return;

	}

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

	while (exploring && Player1.GetHealth() > 0) {

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

						if (Player1.GetHealth() <= 0) {

							return;

						}

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

			Rest();
			break;

		case 5:

			exploring = false;
			break;

		}

	}

}

void Game::VisitLocation(Location& location) {

	if (location.GetLocType() == LocationType::BoarField) {

		VisitBoarField(location);
		return;

	}

	if (location.GetLocType() == LocationType::WaterSpring) {

		VisitWaterSpring(location);
		return;

	}

	if (location.GetLocType() == LocationType::SpiderNest) {

		VisitSpiderNest(location);
		return;

	}

	bool visiting = true;

	while (visiting && Player1.GetHealth() > 0) {

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
			
			Rest();
			break;

		case 5:

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

		int dayBeforeAdvance = gameClock.GetCurrentDay();

		DayPeriod periodBeforeAdvance = gameClock.GetDayPeriod();

		gameClock.AdvanceTime(1);

		if (periodBeforeAdvance != gameClock.GetDayPeriod()) {

			gameWeather.RandomizeWeather();

		}

		if (gameClock.GetCurrentDay() > dayBeforeAdvance) {

			RefreshKnownLocations();
			std::cout << "\nA new day has begun. Location resources and wildlife have refreshed.\n";

		}

		Player1.SetTemp(gameWeather.GetTemp());

		DrainResult statDrain = playerDrain.CalculateDrain(gameClock, activityLevel);

		if (Player1.isHot() && Player1.GetInventory().GetItemCount(ItemID::VineGear) <= 0) {

			statDrain.hydrationDrain *= 2;

		}

		if (Player1.isCold() && Player1.GetInventory().GetItemCount(ItemID::LeatherGear) <= 0) {

			statDrain.hungerDrain *= 2;

		}

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

		if (Player1.GetHunger() == 0) {

			Player1.DecreaseHealth(1.0f);

		}

		if (Player1.GetHydration() == 0) {

			Player1.DecreaseHealth(1.0f);

		}

		if (Player1.GetHealth() <= 0) {

			return;

		}

		campfire.BurnForMinutes(15);

		if (dayBeforeAdvance < gameClock.GetCurrentDay() && Player1.GetHealth() > 0) {

			CaptureDailyCheckpoint();

		}

	}

}

void Game::TravelToLocation(Location& location) {
	
	if (!CanPerformStrenuousAction()) {

		return;

	}

	std::cout << "You travel to a " << GetLocationName(GetLocationIndex(location.GetLocType()));

	ProcessTime((location.GetTravelTime() * 2), ActivityLevel::Strenuous);

	if (Player1.GetHealth() <= 0) {

		return;

	}

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

	if (Player1.GetHealth() <= 0) {

		return;

	}

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

void Game::VisitBoarField(Location& location) {

	bool visiting = true;

	while (visiting && Player1.GetHealth() > 0) {

		std::cout << "\nLiving Boars: " << location.GetRemainingBoars() << "\nUnprocessed Carcasses: " << location.GetUnprocessedBoars() << "\n\n";

		int menuChoice = Menu::DisplayMenu(MenuType::BoarField, gameClock);

		switch (menuChoice) {

		case 1:

			HuntAtBoarField(location);
			break;

		case 2:

			ProcessBoarCarcassAtField(location);
			break;

		case 3:

			ShowInventory();
			break;

		case 4:

			ViewStatus();
			break;

		case 5:

			Rest();
			break;

		case 6:

			visiting = false;
			break;

		}

	}

}

void Game::HuntAtBoarField(Location& location) {

	if (!CanPerformStrenuousAction()) {

		return;

	}

	if (Player1.GetInventory().GetItemCount(ItemID::Spear) == 0) {

		std::cout << "Spear is required to hunt.\n";
		return;

	} 

	int huntedBoars = location.HuntBoars();

	if (huntedBoars == 0) {

		std::cout << "No living Boars remain. Please return tomorrow.\n";
		return;

	}

	std::cout << "You successfully hunted " << huntedBoars << " Boars.\n";
	ProcessTime(1, ActivityLevel::Strenuous);

}

void Game::ProcessBoarCarcassAtField(Location& location) {

	if (location.GetUnprocessedBoars() <= 0) {

		std::cout << "There are no carcasses to process.\n";
		return;

	}

	int processingChoice = Menu::DisplayMenu(MenuType::BoarCarcass, gameClock);

	int meatAmount = 0;
	int leatherAmount = 0;

	switch (processingChoice) {

	case 1:

		meatAmount = 8;
		leatherAmount = 4;
		break;

	case 2:

		meatAmount = 4;
		leatherAmount = 8;
		break;

	case 3:

		return;

	}

	Inventory tempInventory = Player1.GetInventory();
	Item rawMeat(ItemID::RawMeat);
	Item leather(ItemID::Leather);
	int meatOverflow = tempInventory.AddItem(rawMeat, meatAmount);
	int leatherOverflow = tempInventory.AddItem(leather, leatherAmount);

	if (meatOverflow > 0 || leatherOverflow > 0) {

		std::cout << "There is not enough space in your inventory.\nThe carcass will be here when you have inventory space.\n";
		return;
		
	} 

	if (!location.ProcessBoarCarcass()) {

		std::cout << "The carcass could not be processed.\n";
		return;

	}

	Player1.GetInventory() = tempInventory;
	std::cout << "You have received " << meatAmount << " raw meat, and " << leatherAmount << " leather.\n";
	ProcessTime(1, ActivityLevel::Normal);

}

void Game::RefreshKnownLocations() {
	
	for (std::optional<Location>& location : knownLocations) {

		if (!location.has_value()) {

			continue;

		}

		location->RefreshDailyState();

	}

}

void Game::VisitWaterSpring(Location& location) {

	bool visiting = true;

	while (visiting && Player1.GetHealth() > 0) {

		std::cout << "Current Water: " << Player1.GetInventory().GetStoredWater() << '/' << Player1.GetInventory().GetWaterCapacity() << '\n';

		int menuChoice = Menu::DisplayMenu(MenuType::WaterSpring, gameClock);

		switch (menuChoice) {

		case 1:

			FillAtWaterSpring();
			break;

		case 2:

			ShowInventory();
			break;

		case 3:

			ViewStatus();
			break;

		case 4:

			Rest();
			break;

		case 5:

			visiting = false;
			break;

		}

	}

}

void Game::FillAtWaterSpring() {

	int capacity = Player1.GetInventory().GetWaterCapacity();

	if (capacity <= 0) {

		std::cout << "A Waterskin is required to collect water.\n";
		return;

	}

	int waterAdded = Player1.GetInventory().FillWaterContainer();

	if (waterAdded == 0) {

		std::cout << "Waterskin is already full.\n";
		return;

	}

	std::cout << "You collected " << waterAdded << " units of water in your Waterskin.\nYour Waterskin now holds " << Player1.GetInventory().GetStoredWater() << '/' << capacity << " water.\n";
	ProcessTime(1, ActivityLevel::Normal);

}

void Game::OpenCampfireMenu() {

	bool atCampfire = true;

	while (atCampfire && Player1.GetHealth() > 0) {

		int menuChoice = Menu::DisplayCampfireMenu(campfire, gameClock);

		if (!campfire.IsBuilt()) {

			if (menuChoice == 1) {

				BuildCampfire();
				continue;

			}
			else {

				return;

			}

		}

		switch (menuChoice) {

		case 1:

			AddFuelToCampfire();
			break;

		case 2:

			CookMeatAtCampfire();
			break;

		case 3:

			atCampfire = false;
			break;

		}

	}

}

void Game::BuildCampfire() {

	if (campfire.IsBuilt()) {

		std::cout << "Campfire is already built.\n";
		return;

	}

	if (Player1.GetInventory().GetItemCount(ItemID::CrudeWood) < 20 || Player1.GetInventory().GetItemCount(ItemID::Flint) < 10) {

		std::cout << "You are missing materials.\nCrude Wood: " << Player1.GetInventory().GetItemCount(ItemID::CrudeWood) << "/20 Crude Wood\nFlint: " << Player1.GetInventory().GetItemCount(ItemID::Flint) << "/10 Flint.\n";
		return;

	} 

	Player1.GetInventory().RemoveItem(ItemID::CrudeWood, 20);
	Player1.GetInventory().RemoveItem(ItemID::Flint, 10);

	campfire.Build();
	ProcessTime(2, ActivityLevel::Normal);

	std::cout << "Campfire has been built successfully.\n";

}

void Game::AddFuelToCampfire() {

	if (!campfire.IsBuilt()) {

		std::cout << "Campfire has not been built yet.\n";
		return;

	}

	int playerWood = Player1.GetInventory().GetItemCount(ItemID::CrudeWood);
	int campfireFuelCap = campfire.GetAvailableFuelCap();
	
	if (playerWood <= 0) {

		std::cout << "Player has no wood.\n";
		return;

	}

	if (campfireFuelCap <= 0) {

		std::cout << "Campfire cannot accept any more fuel.\n";
		return;

	}
	
	int menuChoice = Menu::DisplayFuelAmountMenu(playerWood, campfireFuelCap);

	if (menuChoice == 0) {

		return;

	}

	int woodAdded = campfire.AddFuel(menuChoice);

	if (woodAdded <= 0) {

		std::cout << "Campfire could not accept any fuel.\n";
		return;

	}

	Player1.GetInventory().RemoveItem(ItemID::CrudeWood, woodAdded);

	int campfireTotalMinutes = campfire.GetFuelMinutes();

	int fireRemainingHours = campfireTotalMinutes / 60;
	int fireRemainingMinutes = campfireTotalMinutes % 60;

	std::cout << "You have added " << woodAdded << " pieces of Crude Wood.\nThe fire will now burn for " << fireRemainingHours << " hours and " << fireRemainingMinutes << " minutes.\n";

}

void Game::CookMeatAtCampfire() {

	if (!campfire.IsBuilt()) {

		std::cout << "Campfire has not been built yet.\n";
		return;

	}

	if (!campfire.IsLit()) {

		std::cout << "Campfire has no fuel. You must add fuel before cooking.\n";
		return;

	}

	int playerMeat = Player1.GetInventory().GetItemCount(ItemID::RawMeat);

	if (playerMeat <= 0) {

		std::cout << "You have no meat to cook.\n";
		return;

	}

	int menuChoice = Menu::DisplayCookingMenu(playerMeat);

	if (menuChoice == 0) {

		return;

	}

	Inventory tempInventory = Player1.GetInventory();
	int remaining = tempInventory.RemoveItem(ItemID::RawMeat, menuChoice);

	if (remaining > 0) {

		std::cout << "The requested raw meat could not be removed.\n";
		return;

	}

	int overflow = tempInventory.AddItem(ItemID::CookedMeat, menuChoice);

	if (overflow > 0) {

		std::cout << "You do not have enough inventory space to cook any meat.\n";
		return;

	}

	Player1.GetInventory() = tempInventory;

	std::cout << "You cooked " << menuChoice << " raw meat into cooked meat.\n";

	ProcessTime(1, ActivityLevel::Normal);

}

void Game::Rest() {

	if (Player1.GetStamina() >= 100.0f) {

		std::cout << "You do not need rest, your stamina is full.\n";
		return;

	}

	ProcessTime(2, ActivityLevel::Normal);

	if (Player1.GetHealth() <= 0) {

		return;

	}

	Player1.RestoreStamina(50);

	std::cout << "You have rested for 30 minutes and restored up to 50 stamina.\nCurrent stamina: " << Player1.GetStamina() << '\n';

}

void Game::ConsumeFood(ItemID item) {

	if (Player1.GetHunger() >= 100) {

		std::cout << "You are not hungry.\n";
		return;

	}

	float restorationAmount = 0;

	if (item != ItemID::RawMeat && item != ItemID::CookedMeat) {

		std::cout << "Invalid food type.\n";
		return;

	} else if (item == ItemID::RawMeat) {

		restorationAmount = 12.5f;

	} else if (item == ItemID::CookedMeat) {

		restorationAmount = 25.0f;

	}

	int itemAmount = Player1.GetInventory().GetItemCount(item);

	if (itemAmount <= 0) {

		Item tempItem = item;
		std::cout << "You do not currently have any " << tempItem.GetName() << ".\n";
		return;

	}

	int remaining = Player1.GetInventory().RemoveItem(item, 1);

	if (remaining > 0) {

		std::cout << "Failed to consume food.\n";
		return;

	}

	float hungerBeforeEating = Player1.GetHunger();

	Player1.RestoreHunger(restorationAmount);

	float amountRestored = Player1.GetHunger() - hungerBeforeEating;

	Item consumedItem = item;

	std::cout << "You have consumed " << consumedItem.GetName() << " and restored " << amountRestored << " hunger.\nYour current hunger is: " << Player1.GetHunger() << ".\n";

}

void Game::ConsumeWater() {

	if (Player1.GetHydration() >= 100) {

		std::cout << "You are not thirsty.\n";
		return;

	}

	if (Player1.GetInventory().GetStoredWater() <= 0) {

		std::cout << "You currently have no water to drink.\n";
		return;

	}

	bool result = Player1.GetInventory().ConsumeWater();

	if (!result) {

		std::cout << "Failed to consume water.\n";
		return;

	}

	float hydrationBeforeDrinking = Player1.GetHydration();

	Player1.RestoreHydration(25);

	float amountRestored = Player1.GetHydration() - hydrationBeforeDrinking;

	std::cout << "You have sipped from your Waterskin and restored " << amountRestored << " hydration.\nYour current hydration is: " << Player1.GetHydration() << ".\n";

}

bool Game::CanPerformStrenuousAction() const {

	if (Player1.GetStamina() <= 0) {

		std::cout << "You are out of stamina and can no longer perform strenuous actions.\nYou may rest to regain some stamina or return to camp.\n";
		return false;

	}

	return true;

}

void Game::OpenCampStorageMenu() {

	bool organizing = true;

	while (organizing) {

		campStorage.DisplayCampStorage();
		int menuChoice = Menu::DisplayMenu(MenuType::CampStorage, gameClock);

		switch (menuChoice) {

		case 1: 

			DepositItemToStorage();
			break;

		case 2:

			WithdrawItemFromStorage();
			break;

		case 3:

			organizing = false;
			break;

		}

	}

}

void Game::DepositItemToStorage() {

	int menuChoice = Menu::DisplayInventorySlotSelection(Player1.GetInventory());

	const std::array<InventorySlot, 10>& inventorySlots = Player1.GetInventory().GetInventorySlots();

	int backChoice = static_cast<int>(inventorySlots.size()) + 1;

	if (menuChoice == backChoice) {

		return;

	}

	int indexNumber = menuChoice - 1;

	const InventorySlot& selectedSlot = inventorySlots[indexNumber];

	if (selectedSlot.IsEmpty()) {

		std::cout << "Selected slot is empty.\n";
		return;

	}

	Item itemCopy = selectedSlot.GetItem();

	int transferAmount = Menu::DisplayQuantityMenu(itemCopy, selectedSlot.GetQuantity());

	if (transferAmount <= 0) {

		return;

	}

	CampStorage tempCampStorage = campStorage;
	Inventory tempPlayerInventory = Player1.GetInventory();

	int overflow = tempCampStorage.AddItem(itemCopy, transferAmount);

	if (overflow > 0) {

		std::cout << "There is not enough camp storage space to complete this transfer.\n";
		return;

	}

	int unremovedAmount = tempPlayerInventory.RemoveItem(itemCopy, transferAmount);

	if (unremovedAmount > 0) {

		std::cout << "You were unable to store the items.\n";
		return;

	}

	campStorage = tempCampStorage;
	Player1.GetInventory() = tempPlayerInventory;

	std::cout << "You successfully stored " << transferAmount << " of " << itemCopy.GetName() << " in camp storage.\n";

}

void Game::WithdrawItemFromStorage() {

	int menuChoice = Menu::DisplayStorageSlotSelection(campStorage);

	const std::array<InventorySlot, 20>& storageSlots = campStorage.GetCampStorageSlots();

	int backChoice = static_cast<int>(storageSlots.size()) + 1;

	if (menuChoice == backChoice) {

		return;

	}

	int indexNumber = menuChoice - 1;

	const InventorySlot& selectedSlot = storageSlots[indexNumber];

	if (selectedSlot.IsEmpty()) {

		std::cout << "Selected storage slot is empty.\n";
		return;

	}

	Item itemCopy = selectedSlot.GetItem();

	int transferAmount = Menu::DisplayQuantityMenu(itemCopy, selectedSlot.GetQuantity());

	if (transferAmount <= 0) {

		return;

	}

	CampStorage tempCampStorage = campStorage;
	Inventory tempPlayerInventory = Player1.GetInventory();

	int overflow = tempPlayerInventory.AddItem(itemCopy, transferAmount);

	if (overflow > 0) {

		std::cout << "You do not have the inventory space to withdraw items from camp storage.\n";
		return;

	}

	int unremovedAmount = tempCampStorage.RemoveItem(itemCopy, transferAmount);

	if (unremovedAmount > 0) {

		std::cout << "You could not remove the chosen amount from camp storage.\n";
		return;

	}

	campStorage = tempCampStorage;
	Player1.GetInventory() = tempPlayerInventory;

	std::cout << "You have removed " << transferAmount << " of " << itemCopy.GetName() << " from camp storage.\n";

}

void Game::VisitSpiderNest(Location& location) {

	bool visiting = true;

	while (visiting && Player1.GetHealth() > 0) {

		std::cout << "Remaining spiders: " << location.GetRemainingSpiders() << '\n';

		int menuChoice = Menu::DisplayMenu(MenuType::SpiderNest, gameClock);

		switch (menuChoice) {

		case 1:

			FightSpiderAtNest(location);
			break;

		case 2:

			ShowInventory();
			break;

		case 3:

			ViewStatus();
			break;

		case 4:

			Rest();
			break;

		case 5:

			visiting = false;
			break;

		}

	}

}

void Game::FightSpiderAtNest(Location& location) {

	if (!CanPerformStrenuousAction()) {
		
		return;

	}

	if (Player1.GetInventory().GetItemCount(ItemID::Spear) <= 0 && Player1.GetInventory().GetItemCount(ItemID::Bow) <= 0) {

		std::cout << "You do not have required weapons to be here.\n";
		return;

	}

	if (location.GetRemainingSpiders() <= 0) {

		std::cout << "There are no spiders left.\n";
		return;

	}

	Inventory capacityCheck = Player1.GetInventory();
	int silkOverflow = capacityCheck.AddItem(ItemID::Silk, 4);
	if (silkOverflow > 0) {

		std::cout << "You do not have enough inventory space to collect silk.\n";
		return;

	}

	int spiderHealth = 6;

	while (spiderHealth > 0 && Player1.GetHealth() > 0) {

		int combatChoice = Menu::DisplayMenu(MenuType::SpiderCombat, gameClock);

		switch (combatChoice) {

		case 1:

			if (Player1.GetInventory().GetItemCount(ItemID::Spear) <= 0) {

				std::cout << "You do not have a spear.\n";
				break;

			}

			spiderHealth -= 3;

			if (spiderHealth < 0) {

				spiderHealth = 0;

			}

			std::cout << "You attack the spider with your spear dealing 3 damage.\n";

			if (spiderHealth > 0) {

				int randomAttackCheck = rand() % 100;

				if (randomAttackCheck < 75) {

					Player1.DecreaseHealth(5.0f);
					std::cout << "The spider attacks you dealing 5 damage.\nYour current health is " << Player1.GetHealth() << '\n';

				}

			}
			break;

		case 2: {

			if (Player1.GetInventory().GetItemCount(ItemID::Bow) <= 0) {

				std::cout << "You do not have a bow.\n";
				break;

			}

			ItemID arrowType = ItemID::Empty;
			int arrowDamage = 0;

			int arrowChoice = Menu::DisplayArrowSelection(Player1.GetInventory());

			if (arrowChoice == 4) {

				break;
				
			}

			switch (arrowChoice) {

			case 1: 
				
				arrowType = ItemID::FlintArrow;
				arrowDamage = 2;
				break;

			case 2:

				arrowType = ItemID::StoneArrow;
				arrowDamage = 3;
				break;

			case 3:

				arrowType = ItemID::MetalArrow;
				arrowDamage = 6;
				break;

			}

			if (Player1.GetInventory().GetItemCount(arrowType) <= 0) {

				std::cout << "You do not have any arrows of this kind.\n";
				break;

			}

			int unremovedAmount = Player1.GetInventory().RemoveItem(arrowType, 1);

			if (unremovedAmount > 0) {

				std::cout << "Failed to use arrow.\n";
				break;

			}

			int randomShotChance = rand() % 100;

			if (randomShotChance < 25) {

				std::cout << "You missed the shot.\n";
				break;

			}

			spiderHealth -= arrowDamage;
			if (spiderHealth < 0) {

				spiderHealth = 0;

			}

			std::cout << "You shot the spider with an arrow and dealt " << arrowDamage << " damage.\nSpider health: " << spiderHealth << '\n';

			break;

		}

		case 3:

			std::cout << "You retreat from the fight.\n";
			return;

		}

	}

	if (Player1.GetHealth() <= 0) {

		return;

	}

	Inventory tempPlayerInventory = Player1.GetInventory();

	int overflow = tempPlayerInventory.AddItem(ItemID::Silk, 4);

	if (overflow > 0) {

		std::cout << "You do not have the inventory space to collect silk.\n";
		return;

	}

	if (!location.DefeatSpider()) {

		std::cout << "You cannot defeat spider.\n";
		return;

	}

	std::cout << "You defeated 1 spider and got 4 silk.\n";

	Player1.GetInventory() = tempPlayerInventory;

	ProcessTime(1, ActivityLevel::Strenuous);

}

void Game::UseBandage(ItemID item) {

	if (Player1.GetHealth() >= 100) {

		std::cout << "Your Health is full.\n";
		return;

	}

	float restorationAmount = 0;

	if (item != ItemID::BasicBandage && item != ItemID::ImprovedBandage) {

		std::cout << "Invalid healing item.\n";
		return;

	} else if (item == ItemID::BasicBandage) {

		restorationAmount = 5.0f;

	} else if (item == ItemID::ImprovedBandage) {
	
		restorationAmount = 10.0f;
	
	}

	int itemAmount = Player1.GetInventory().GetItemCount(item);

	if (itemAmount <= 0) {

		Item tempItem = item;
		std::cout << "You do not currently have any " << tempItem.GetName() << ".\n";
		return;

	}

	int remaining = Player1.GetInventory().RemoveItem(item, 1);

	if (remaining > 0) {

		std::cout << "Failed to use bandage.\n";
		return;

	}

	float healthBeforeHealing = Player1.GetHealth();

	Player1.RestoreHealth(restorationAmount);

	float amountRestored = Player1.GetHealth() - healthBeforeHealing;

	Item consumedItem = item;

	std::cout << "You have used a " << consumedItem.GetName() << " and restored " << amountRestored << " health.\nYour current health is: " << Player1.GetHealth() << ".\n";

}

void Game::CaptureDailyCheckpoint() {

	DailyCheckpoint checkpoint;
	checkpoint.playerCheckpoint = Player1;
	checkpoint.gameClockCheckpoint = gameClock;
	checkpoint.knownLocationsCheckpoint = knownLocations;
	checkpoint.campfireCheckpoint = campfire;
	checkpoint.campStorageCheckpoint = campStorage;
	checkpoint.raftCheckpoint = raft;
	checkpoint.weatherCheckpoint = gameWeather;
	dailyCheckpoint = checkpoint;

}

bool Game::RestoreDailyCheckpoint() {

	if (!dailyCheckpoint.has_value()) {

		return false;

	}

	Player1 = dailyCheckpoint->playerCheckpoint;
	gameClock = dailyCheckpoint->gameClockCheckpoint;
	knownLocations = dailyCheckpoint->knownLocationsCheckpoint;
	campfire = dailyCheckpoint->campfireCheckpoint;
	campStorage = dailyCheckpoint->campStorageCheckpoint;
	raft = dailyCheckpoint->raftCheckpoint;
	gameWeather = dailyCheckpoint->weatherCheckpoint;
	return true; 

}

void Game::RunCampLoop() {

	bool shouldKeepRunning = true;

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

			Rest();
			break;

		case 4:

			ShowInventory();
			break;

		case 5:

			OpenCraftingMenu();
			break;

		case 6:

			OpenCampfireMenu();
			break;

		case 7:

			OpenCampStorageMenu();
			break;

		case 8:

			Explore();
			break;

		case 9:

			if (OpenRaftMenu()) {

				shouldKeepRunning = false;

			}
			break;
			
		case 10:

			SaveCurrentGame();
			break;

		case 11:

			shouldKeepRunning = false;
			break;

		}

		if (Player1.GetHealth() <= 0) {

			std::cout << "You have died\n";
			if (!RestoreDailyCheckpoint()) {

				std::cout << "No available checkpoint.\n";
				shouldKeepRunning = false;

			}
			else {

				std::cout << "You will now restart at the beginning of the current day.\n";

			}

		}

	}

}

void Game::SaveCurrentGame() {

	if (!dailyCheckpoint.has_value()) {

		std::cout << "Could not save game\n";
		return;

	}

	DailyCheckpoint currentState;
	currentState.playerCheckpoint = Player1;
	currentState.gameClockCheckpoint = gameClock;
	currentState.knownLocationsCheckpoint = knownLocations;
	currentState.campfireCheckpoint = campfire;
	currentState.campStorageCheckpoint = campStorage;
	currentState.raftCheckpoint = raft;
	currentState.weatherCheckpoint = gameWeather;

	
	if (!SaveSystem::SaveGame(currentState, *dailyCheckpoint)) {

		std::cout << "Game save failed please try again.\n";
		return;

	}

	std::cout << "Game has been saved.\n";

}

void Game::ContinueSavedGame() {

	DailyCheckpoint loadedCurrentState;
	DailyCheckpoint loadedDailyCheckpoint;

	if (!SaveSystem::LoadGame(loadedCurrentState, loadedDailyCheckpoint)) {

		std::cout << "Loading game failed.\n";
		return;

	}

	Player1 = loadedCurrentState.playerCheckpoint;
	gameClock = loadedCurrentState.gameClockCheckpoint;
	knownLocations = loadedCurrentState.knownLocationsCheckpoint;
	campfire = loadedCurrentState.campfireCheckpoint;
	campStorage = loadedCurrentState.campStorageCheckpoint;
	raft = loadedCurrentState.raftCheckpoint;
	gameWeather = loadedCurrentState.weatherCheckpoint;
	dailyCheckpoint = loadedDailyCheckpoint;
	

	std::cout << "\n\n=== GAME LOADED SUCCESFULLY ===\n\n";
	RunCampLoop();

}

bool Game::OpenRaftMenu() {

	bool atRaft = true;

	while (atRaft && Player1.GetHealth() > 0) {

		raft.DisplayProgress();
		int menuChoice = Menu::DisplayMenu(MenuType::Raft, gameClock);

		switch (menuChoice) {

		case 1:

			ContributeToRaft();
			break;

		case 2:

			TransferWaterToRaft();
			break;

		case 3:

			if (!raft.IsReadyToEscape()) {

				if (!raft.IsBuilt()) {

					std::cout << "The raft is not finished, please finish building and preparing for departure.\n";
					break;

				}

				std::cout << "The raft is not stocked for departure, please finish stocking.\n";
				break;

			}

			std::cout << "\n\n===========================================\n\nCONGRATULATIONS!!!!\n\nYOU HAVE ESCAPED THE LONG LOST ISLE!!!!!\n\n";
			return true;


		case 4:

			atRaft = false;
			break;

		}

	}

		return false;

}

void Game::ContributeToRaft() {

	int menuChoice = Menu::DisplayStorageSlotSelection(campStorage);

	const std::array<InventorySlot, 20>& storageSlots = campStorage.GetCampStorageSlots();

	int backChoice = static_cast<int>(storageSlots.size()) + 1;

	if (menuChoice == backChoice) {

		return;

	}

	int indexNumber = menuChoice - 1;

	const InventorySlot& selectedSlot = storageSlots[indexNumber];

	if (selectedSlot.IsEmpty()) {

		std::cout << "Selected storage slot is empty.\n";
		return;

	}

	Item itemCopy = selectedSlot.GetItem();

	int remainingRequired = raft.GetRemainingRequirement(itemCopy.GetID());

	if (remainingRequired <= 0) {

		std::cout << "The raft does not require any more of this item.\n";
		return;

	}

	int maxContribution = selectedSlot.GetQuantity();
	if (maxContribution > remainingRequired) {

		maxContribution = remainingRequired;

	}

	int transferAmount = Menu::DisplayQuantityMenu(itemCopy, maxContribution);

	if (transferAmount == 0) {

		return;

	}

	CampStorage tempCampStorage = campStorage;
	Raft tempRaft = raft;
	int acceptedAmount = tempRaft.ContributeItem(itemCopy.GetID(), transferAmount);
	if (acceptedAmount == 0) {

		return;

	}

	int unremovedAmount = tempCampStorage.RemoveItem(itemCopy, acceptedAmount);

	if (unremovedAmount > 0) {

		std::cout << "Failed to remove item from storage.\n";
		return;
	
	}

	campStorage = tempCampStorage;
	raft = tempRaft;

	std::cout << "You contributed " << acceptedAmount << ' ' << itemCopy.GetName() << ".\n";

}

void Game::TransferWaterToRaft() {

	if (Player1.GetInventory().GetStoredWater() <= 0) {

		std::cout << "You do not have any water to contribute.\n";
		return;

	}

	if (raft.GetRemainingWaterRequirement() <= 0) {

		std::cout << "The raft does not require any more water.\n";
		return;

	}

	Inventory tempInventory = Player1.GetInventory();
	Raft tempRaft = raft;

	int acceptedWater = tempRaft.ContributeWater(tempInventory.GetStoredWater());
	int removedWater = tempInventory.RemoveWater(acceptedWater);

	if (acceptedWater != removedWater) {

		return;

	}

	raft = tempRaft;
	Player1.GetInventory() = tempInventory;
	std::cout << "You have contributed " << acceptedWater << " units of water to the raft stock.\n";

}

