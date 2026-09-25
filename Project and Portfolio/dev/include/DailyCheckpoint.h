#pragma once
#include "Player.h"
#include "GameClock.h"
#include "Location.h"
#include "Campfire.h"
#include "CampStorage.h"
#include <array>
#include <optional>
#include "Raft.h"
#include "Weather.h"

struct DailyCheckpoint {

	Player playerCheckpoint;
	GameClock gameClockCheckpoint;
	std::array<std::optional<Location>, 6> knownLocationsCheckpoint;
	Campfire campfireCheckpoint;
	CampStorage campStorageCheckpoint;
	Raft raftCheckpoint;
	Weather weatherCheckpoint;

};
