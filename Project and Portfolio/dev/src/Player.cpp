#include "Player.h"
#include <iostream>

void Player::SetName(const std::string& name) {

	playerName = name;

}

const std::string& Player::GetName() const {

	return playerName;

}

int Player::GetTemp() const{

	return playerTemp;

}

float Player::GetHealth() const {

	return playerHealth;

}

float Player::GetHunger() const {

	return playerHunger;

}

float Player::GetHydration() const {

	return playerHydration;

}

float Player::GetStamina() const {

	return playerStamina;

}

float Player::GetSanity() const {

	return playerSanity;
	
}

Inventory& Player::GetInventory() {

	return playerInventory;

}

void Player::DecreaseHunger(float amount) {

	playerHunger -= amount;
	if (playerHunger <= 0) {

		playerHunger = 0;
		std::cout << "Your Hunger has reached Critical State!!!\nYou will now start losing health over time!!!\n";
		

	}

}

void Player::DecreaseHydration(float amount) {

	playerHydration -= amount;
	if (playerHydration <= 0) {

		playerHydration = 0;
		std::cout << "Your Hydration has reached Critical State!!!\nYou will now start losing health over time!!!\n";


	}

}

void Player::DecreaseStamina(float amount) {

	playerStamina -= amount;
	if (playerStamina <= 0) {

		playerStamina = 0;
		std::cout << "Your stamina has reached 0, you can no longer perform strenuous actions.\nYou may return to Camp or rest to regain some stamina.\n";

	}

}

void Player::DecreaseSanity(float amount) {

	playerSanity -= amount;
	if (playerSanity <= 0) {

		playerSanity = 0;
		std::cout << "Your Sanity has reached Critical State!!!\n";

	}

}



