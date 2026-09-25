#include "SaveSystem.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <system_error>

bool SaveSystem::SaveGame(const DailyCheckpoint& currentState, const DailyCheckpoint& dailyCheckpoint) {

	std::ofstream output("savegame.tmp");
	if (!output) {

		return false;

	}
	
	output << "LONG_LOST_ISLE 3" << '\n';

	if (!SaveCheckpoint(output, currentState)) {

		return false;

	}

	if (!SaveCheckpoint(output, dailyCheckpoint)) {

		return false;

	}

	output.close();
	if (!output) {

		return false;

	}

	std::error_code fileError;
	bool saveExists = std::filesystem::exists("savegame.txt", fileError);
	if (fileError) {

		return false;

	}

	if (saveExists) {

		std::filesystem::copy_file("savegame.txt", "savegame.bak", std::filesystem::copy_options::overwrite_existing, fileError);
		
		if (fileError) {

			return false;

		}

		std::filesystem::remove("savegame.txt", fileError);
		if (fileError) {

			return false;

		}

	}

	std::filesystem::rename("savegame.tmp", "savegame.txt", fileError);
	if (fileError) {

		if (saveExists) {

			std::error_code restoreError;
			std::filesystem::copy_file("savegame.bak", "savegame.txt", std::filesystem::copy_options::overwrite_existing, restoreError);
			

		}

		return false;
	
	}

	return true;

}

bool SaveSystem::LoadGame(DailyCheckpoint& currentState, DailyCheckpoint& dailyCheckpoint) {

	std::ifstream input("savegame.txt");
	if (!input) {

		return false;

	}

std::string fileIdentifier;
int version = 0;

input >> fileIdentifier >> version;
if (!input || fileIdentifier != "LONG_LOST_ISLE" || version != 3) {

	return false;

}

DailyCheckpoint loadedCurrentState;
DailyCheckpoint loadedDailyCheckpoint;

if (!LoadCheckpoint(input, loadedCurrentState)) {

	return false;

}

if (!LoadCheckpoint(input, loadedDailyCheckpoint)) {

	return false;

}

if (loadedCurrentState.playerCheckpoint.GetHealth() <= 0 || loadedDailyCheckpoint.playerCheckpoint.GetHealth() <= 0) {

	return false;

}

currentState = loadedCurrentState;
dailyCheckpoint = loadedDailyCheckpoint;
return true;

}

bool SaveSystem::SaveCheckpoint(std::ostream& output, const DailyCheckpoint& checkpoint) {

	if (!checkpoint.playerCheckpoint.Save(output)) {

		return false;

	}

	if (!checkpoint.gameClockCheckpoint.Save(output)) {

		return false;

	}

	for (const std::optional<Location>& location : checkpoint.knownLocationsCheckpoint) {

		output << location.has_value() << '\n';
		if (!static_cast<bool>(output)) {

			return false;

		}
		
		if (location.has_value()) {

			if (!location->Save(output)) {

				return false;

			}

		}

	}

	if (!checkpoint.campfireCheckpoint.Save(output)) {

		return false;

	}
	if (!checkpoint.campStorageCheckpoint.Save(output)) {

		return false;

	}
	if (!checkpoint.raftCheckpoint.Save(output)) {

		return false;

	}
	if (!checkpoint.weatherCheckpoint.Save(output)) {

		return false;

	}

	return static_cast<bool>(output);

}

bool SaveSystem::LoadCheckpoint(std::istream& input, DailyCheckpoint& checkpoint) {

	DailyCheckpoint loadedCheckpoint;

	if (!loadedCheckpoint.playerCheckpoint.Load(input)) {

		return false;

	}

	if (!loadedCheckpoint.gameClockCheckpoint.Load(input)) {

		return false;

	}

	for (std::optional<Location>& location : loadedCheckpoint.knownLocationsCheckpoint) {

		bool locationExists = false;
		
		input >> locationExists;
		if (!input) {

			return false;

		}

		if (locationExists) {

			Location loadedLocation;
			if (!loadedLocation.Load(input)) {

				return false;

			}

			location = loadedLocation;

		}

	}

	if (!loadedCheckpoint.campfireCheckpoint.Load(input)) {

		return false;

	}

	if (!loadedCheckpoint.campStorageCheckpoint.Load(input)) {

		return false;

	}
	if (!loadedCheckpoint.raftCheckpoint.Load(input)) {

		return false;

	}
	if (!loadedCheckpoint.weatherCheckpoint.Load(input)) {

		return false;

	}

	checkpoint = loadedCheckpoint;
	return true;

}


