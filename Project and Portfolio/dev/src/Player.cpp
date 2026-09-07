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

int Player::GetHealth() const {

	return playerHealth;

}

int Player::GetHunger() const {

	return playerHunger;

}

int Player::GetHydration() const {

	return playerHydration;

}

int Player::GetStamina() const {

	return playerStamina;

}

int Player::GetSanity() const {

	return playerSanity;
	
}

void Player::DecreaseHungerSleep() {

	playerHunger -= 10;
	if (playerHunger <= 0) {

		playerHunger = 0;
		std::cout << "Your Hunger has reached Critical State!!!\nYou will now start losing health over time!!!\n";
		

	}

}

void Player::DecreaseHydrationSleep() {

	playerHydration -= 10;
	if (playerHydration <= 0) {

		playerHydration = 0;
		std::cout << "Your Hydration has reached Critical State!!!\nYou will now start losing health over time!!!\n";


	}

}



