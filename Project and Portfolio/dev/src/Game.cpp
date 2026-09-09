#include "Game.h"
#include "Item.h"
#include "InventorySlot.h"
#include "DedicatedInventorySlot.h"
#include "Inventory.h"
#include <iostream>
#include <string>

void Game::Run() {

	std::cout << "=== Welcome to The Long Lost Isle ===\n\n";

	std::string userInput;

	std::cout << "1. Start Game\n2. Exit\n\n";
	std::cin >> userInput;
	while (userInput != "1" && userInput != "2") {

		std::cout << "Input not valid! Please choose from the menu choices.\n";
		std::cin >> userInput;

	}

	int menuChoice = std::stoi(userInput);

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
	std::string userInput;
	bool shouldKeepRunning = true;

	std::cout << "Please input your name: ";
	
	std::cin.ignore();
	std::getline(std::cin, name);

	Player1.SetName(name);

	std::cout << "Welcome to The Long Lost Isle " << Player1.GetName() << ", it's time for your survival journey to begin.\n\n";

	std::cout << "\n\n===============================================\n\nYou find yourself stranded on an island, the last thing you remember is being on a cruise vacationing from work.\n\nYou must have fallen off while nobody was around to alert anybody and now you are here.\n\nYou quickly gather materials to start a small survival camp, a pile of leaves to sleep on, a quick shelter to prevent\nrain or wind from being too much of a hassle, a small storage space, and you find a suspiciously table-like stump.\n\n";
	
	while (shouldKeepRunning) {

		std::cout << "=== Camp ===\n\n1. View Status\n2. Sleep\n3. Show Inventory\n4. Exit Game\n";
		std::cin >> userInput;
		while (userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4") {

			std::cout << "Input not valid! Please choose from the menu choices.\n";
			std::cin >> userInput;

		}

		int menuChoice = std::stoi(userInput);

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

			shouldKeepRunning = false;
			break;

		}

	}

}

void Game::ViewStatus() {

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

	Player1.DecreaseHungerSleep();
	Player1.DecreaseHydrationSleep();

}

void Game::ShowInventory() {

	Player1.GetInventory().DisplayInventory();

}


