#include "GameClock.h"
#include <iostream>

GameClock::GameClock() {

	currentDay = 1;
	currentTimeMinutes = 600;

}

int GameClock::GetCurrentDay() const {

	return currentDay;

}

int GameClock::GetCurrentTimeMinutes() const {

	return currentTimeMinutes;

}

DayPeriod GameClock::GetDayPeriod() const {

	if (currentTimeMinutes >= 240 && currentTimeMinutes < 600) {

		return DayPeriod::Morning;

	} else if (currentTimeMinutes >= 600 && currentTimeMinutes < 960){

		return DayPeriod::Afternoon;

	} else if (currentTimeMinutes >= 960 && currentTimeMinutes < 1320) {

		return DayPeriod::Evening;

	} else {

		return DayPeriod::Night;

	}

}

void GameClock::AdvanceTime(int FifteenMinuteIntervals) {

	currentTimeMinutes += (FifteenMinuteIntervals * 15);
	while (currentTimeMinutes >= 1440) {

		currentTimeMinutes -= 1440;
		currentDay += 1;

	}

}

void GameClock::DisplayTime() const {

	int hour24 = GetCurrentTimeMinutes() / 60;
	int minute = GetCurrentTimeMinutes() % 60;
	int displayHour;
	std::string timeSuffix;

	if (hour24 < 12) {

		timeSuffix = "AM";

	}
	else {

		timeSuffix = "PM";

	}

	if (hour24 == 0 || hour24 == 12) {

		displayHour = 12;

	} else if (hour24 > 0 && hour24 < 12) {

		displayHour = hour24;

	} else {

		displayHour = hour24 - 12;

	}

	std::cout << "=== Current Time ===\n\nDay: " << GetCurrentDay() << '\n';

	std::cout << "Time: " << displayHour << ':';
	if (minute == 0) {

		std::cout << "00";

	} else {

		std::cout << minute;

	}
	std::cout << ' ' << timeSuffix << "\nPeriod: ";

	switch (GetDayPeriod()) {

	case DayPeriod::Morning:

		std::cout << "Morning\n\n";
		break;

	case DayPeriod::Afternoon:

		std::cout << "Afternoon\n\n";
		break;

	case DayPeriod::Evening:

		std::cout << "Evening\n\n";
		break;

	case DayPeriod::Night:

		std::cout << "Night\n\n";
		break;

	}

}

