#pragma once
#include "GameClock.h"

enum class MenuType {

	Main, Camp, Exploration,
	KnownLocations,	Location, YesNo

};

class Menu {

public:

	static int DisplayMenu(MenuType menuType, const GameClock& gameClock);

private:




};

