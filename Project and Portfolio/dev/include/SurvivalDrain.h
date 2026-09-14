#pragma once
#include "GameClock.h"

enum class ActivityLevel {

	Normal, Strenuous

};

struct DrainResult {

	float hungerDrain = 0.0f;
	float hydrationDrain = 0.0f;
	float staminaDrain = 0.0f;
	float sanityDrain = 0.0f;

};

class SurvivalDrain {

private:
	
	

public:

DrainResult CalculateDrain(const GameClock& time, ActivityLevel drainLevel);

};

