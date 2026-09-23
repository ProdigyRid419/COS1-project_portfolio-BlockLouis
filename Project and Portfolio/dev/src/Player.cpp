#include "Player.h"
#include <iostream>
#include <iomanip>

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

void Player::RestoreHunger(float amount) {

	if (amount <= 0) {

		return;

	}

	playerHunger += amount;
	if (playerHunger >= 100.0f) {

		playerHunger = 100.0f;
		std::cout << "Your Hunger has reached maximum amount.\n";

	}

}

void Player::DecreaseHunger(float amount) {

	if (amount <= 0) {

		return;

	}

	playerHunger -= amount;
	if (playerHunger <= 0) {

		playerHunger = 0;
		std::cout << "Your Hunger has reached Critical State!!!\nYou will now start losing health over time!!!\n";
		

	}

}

void Player::RestoreHydration(float amount) {

	if (amount <= 0) {

		return;

	}

	playerHydration += amount;
	if (playerHydration >= 100.0f) {

		playerHydration = 100.0f;
		std::cout << "Your Hydration has reached maximum amount.\n";

	}

}

void Player::DecreaseHydration(float amount) {

	if (amount <= 0) {

		return;

	}

	playerHydration -= amount;
	if (playerHydration <= 0) {

		playerHydration = 0;
		std::cout << "Your Hydration has reached Critical State!!!\nYou will now start losing health over time!!!\n";


	}

}

void Player::RestoreStamina(float amount) {

	if (amount <= 0) {

		return;

	}

	playerStamina += amount;
	if (playerStamina >= 100.0f) {

		playerStamina = 100.0f;
		std::cout << "Your Stamina has reached maximum amount.\n";

	}

}

void Player::DecreaseStamina(float amount) {

	if (amount <= 0) {

		return;

	}

	playerStamina -= amount;
	if (playerStamina <= 0) {

		playerStamina = 0;
		std::cout << "Your stamina has reached 0, you can no longer perform strenuous actions.\nYou may return to Camp or rest to regain some stamina.\n";

	}

}

void Player::RestoreSanity(float amount) {

	if (amount <= 0) {

		return;

	}

	playerSanity += amount;
	if (playerSanity >= 100.0f) {

		playerSanity = 100.0f;
		std::cout << "Your Sanity has reached maximum amount.\n";

	}

}

void Player::DecreaseSanity(float amount) {

	if (amount <= 0) {

		return;

	}

	playerSanity -= amount;
	if (playerSanity <= 0) {

		playerSanity = 0;
		std::cout << "Your Sanity has reached Critical State!!!\n";

	}

}

void Player::RestoreHealth(float amount) {

	if (amount <= 0) {

		return;

	}

	playerHealth += amount;
	if (playerHealth >= 100.0f) {

		playerHealth = 100.0f;
		std::cout << "Your Health has reached maximum amount.\n";

	}

}

void Player::DecreaseHealth(float amount) {

	if (amount <= 0) {

		return;

	}

	playerHealth -= amount;
	if (playerHealth <= 0) {

		playerHealth = 0;
		
	}

}

bool Player::Save(std::ostream& output) const {

	output << std::quoted(playerName) << '\n';
	output << playerTemp << ' ' << playerHealth << ' ' << playerHunger << ' ' << playerHydration << ' ' << playerStamina << ' ' << playerSanity << '\n';
	if (!playerInventory.Save(output)) {

		return false;

	}

	return static_cast<bool>(output);

}

bool Player::Load(std::istream& input) {

	Player loadedPlayer;

	input >> std::quoted(loadedPlayer.playerName) >> loadedPlayer.playerTemp >> loadedPlayer.playerHealth >> loadedPlayer.playerHunger >> loadedPlayer.playerHydration >> loadedPlayer.playerStamina >> loadedPlayer.playerSanity;
	if (!static_cast<bool>(input)) {

		return false;

	}

	if (loadedPlayer.playerName.empty()) {

		return false;

	}

	if (loadedPlayer.playerHealth < 0 || loadedPlayer.playerHealth > 100) {

		return false;

	}

	if (loadedPlayer.playerHunger < 0 || loadedPlayer.playerHunger > 100) {

		return false;

	}

	if (loadedPlayer.playerHydration < 0 || loadedPlayer.playerHydration > 100) {

		return false;

	}

	if (loadedPlayer.playerStamina < 0 || loadedPlayer.playerStamina > 100) {

		return false;

	}

	if (loadedPlayer.playerSanity < 0 || loadedPlayer.playerSanity > 100) {

		return false;

	}

	if (!loadedPlayer.playerInventory.Load(input)) {

		return false;

	}

	*this = loadedPlayer;
	return true;

}

