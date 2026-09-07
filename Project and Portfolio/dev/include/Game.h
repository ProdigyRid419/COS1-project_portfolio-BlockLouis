#pragma once
#include "Player.h"

class Game {

public:

	void Run();

private:

	void StartGame();
	void ViewStatus();
	void Sleep();

	Player Player1;

};


