#pragma once
#include "DailyCheckpoint.h"
#include <iosfwd>



class SaveSystem {

public:

	static bool SaveGame(const DailyCheckpoint& currentState, const DailyCheckpoint& dailyCheckpoint);
	static bool LoadGame(DailyCheckpoint& currentState, DailyCheckpoint& dailyCheckpoint);

private:

	static bool SaveCheckpoint(std::ostream& output, const DailyCheckpoint& checkpoint);
	static bool LoadCheckpoint(std::istream& input, DailyCheckpoint& checkpoint);


};

