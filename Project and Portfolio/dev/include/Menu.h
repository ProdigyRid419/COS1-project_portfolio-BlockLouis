#pragma once
#include "GameClock.h"

class Location;

enum class MenuType {

	Main, Camp, Exploration,
	KnownLocations,	Location, YesNo, Resources

};

class Menu {

public:

	static int DisplayMenu(MenuType menuType, const GameClock& gameClock);
	static int DisplayResourceMenu(const Location& location);
	
private:

	static int GetValidatedChoice(int minimum, int maximum);

};

