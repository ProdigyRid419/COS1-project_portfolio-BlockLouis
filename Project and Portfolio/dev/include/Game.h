#pragma once
#include "Player.h"

class Game {

public:

	void Run();

private:

	void StartGame();
	void ViewStatus();
	void Sleep();
	void ShowInventory();

	Player Player1;

};


