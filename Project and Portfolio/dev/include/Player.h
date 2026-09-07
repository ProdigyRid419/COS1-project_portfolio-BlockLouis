#pragma once
#include <string>

class Player {

public:

	const std::string& GetName() const;
	int GetTemp() const;
	int GetHealth() const;
	int GetHunger() const;
	int GetHydration() const;
	int GetStamina() const;
	int GetSanity() const;

	void SetName(const std::string& name);
	void DecreaseHungerSleep();
	void DecreaseHydrationSleep();

private:

	std::string playerName;
	int playerTemp = 50;
	int playerHealth = 100;
	int playerHunger = 100;
	int playerHydration = 100;
	int playerStamina = 100;
	int playerSanity = 100;

};
