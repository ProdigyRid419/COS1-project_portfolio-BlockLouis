#include "Game.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;


void Game::Run() {

	cout << "=== Welcome to The Long Lost Isle ===\n\n";

	string userInput;

	cout << "1. Start Game\n2. Exit\n\n";
	cin >> userInput;
	while (userInput != "1" && userInput != "2") {

		cout << "Input not valid! Please choose from the menu choices.\n";
		cin >> userInput;

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

	string name;
	string userInput;
	bool shouldKeepRunning = true;

	cout << "Please input your name: ";
	
	cin.ignore();
	std::getline(cin, name);

	Player1.SetName(name);

	cout << "Welcome to The Long Lost Isle " << Player1.GetName() << ", it's time for your survival journey to begin.\n\n";

	cout << "\n\n===============================================\n\nYou find yourself stranded on an island, the last thing you remember is being on a cruise vacationing from work.\n\nYou must have fallen off while nobody was around to alert anybody and now you are here.\n\nYou quickly gather materials to start a small survival camp, a pile of leaves to sleep on, a quick shelter to prevent\nrain or wind from being too much of a hassle, a small storage space, and you find a suspiciously table-like stump.\n\n";
	
	while (shouldKeepRunning) {

		cout << "=== Camp ===\n\n1. View Status\n2. Sleep\n3. Exit Game\n";
		cin >> userInput;
		while (userInput != "1" && userInput != "2" && userInput != "3") {

			cout << "Input not valid! Please choose from the menu choices.\n";
			cin >> userInput;

		}

		int menuChoice = std::stoi(userInput);

		switch (menuChoice) {

		case 1:


			break;

		case 2:


			break;

		case 3:

			shouldKeepRunning = false;
			break;

		}

	}

}


