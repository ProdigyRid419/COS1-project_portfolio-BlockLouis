#pragma once
#include <iosfwd>

enum class DayPeriod {

	Morning, Afternoon, Evening, Night

};

class GameClock {

public:

	GameClock();

	bool Save(std::ostream& output) const;
	bool Load(std::istream& input);

	int GetCurrentDay() const;
	int GetCurrentTimeMinutes() const;
	DayPeriod GetDayPeriod() const;
	void AdvanceTime(int minutes);
	void DisplayTime() const;

private:

	int currentDay;
	int currentTimeMinutes;

};


