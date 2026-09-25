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

	void SetTemp(int temperature);

	void RestoreHunger(float amount);
	void DecreaseHunger(float amount);
	
	void RestoreHydration(float amount);
	void DecreaseHydration(float amount);
	
	void RestoreStamina(float amount);
	void DecreaseStamina(float amount);
	
	void RestoreSanity(float amount);
	void DecreaseSanity(float amount);

	void RestoreHealth(float amount);
	void DecreaseHealth(float amount);

	bool Save(std::ostream& output) const;
	bool Load(std::istream& input);

	bool isHot() const;
	bool isCold() const;

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
