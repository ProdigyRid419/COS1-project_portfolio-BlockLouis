#pragma once
#include <string>
#include "Inventory.h"

class Player {

public:

	const std::string& GetName() const;
	int GetTemp() const;
	float GetHealth() const;
	float GetHunger() const;
	float GetHydration() const;
	float GetStamina() const;
	float GetSanity() const;
	Inventory& GetInventory();

	void SetName(const std::string& name);
	void DecreaseHunger(float amount);
	void DecreaseHydration(float amount);
	void DecreaseStamina(float amount);
	void DecreaseSanity(float amount);

private:

	std::string playerName;
	int playerTemp = 50;
	float playerHealth = 100.0f;
	float playerHunger = 100.0f;
	float playerHydration = 100.0f;
	float playerStamina = 100.0f;
	float playerSanity = 100.0f;
	Inventory playerInventory;

};
