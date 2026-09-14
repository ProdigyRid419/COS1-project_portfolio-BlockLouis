#include "SurvivalDrain.h"
#include <iostream>

DrainResult SurvivalDrain::CalculateDrain(const GameClock& time, ActivityLevel drainLevel) {

	DrainResult statDrain{};

	if (time.GetCurrentTimeMinutes() % 60 == 0) {

		statDrain.hungerDrain += 1.25f;
		statDrain.hydrationDrain += 1.25f;

	}

	if (drainLevel == ActivityLevel::Strenuous) {

		statDrain.hungerDrain += 1.25f;
		statDrain.hydrationDrain += 1.25f;

	}

	return statDrain;

}

