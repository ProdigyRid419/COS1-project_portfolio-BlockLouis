#pragma once

enum class DayPeriod {

	Morning, Afternoon, Evening, Night

};

class GameClock {

public:

	GameClock();

	int GetCurrentDay() const;
	int GetCurrentTimeMinutes() const;
	DayPeriod GetDayPeriod() const;
	void AdvanceTime(int minutes);
	void DisplayTime() const;

private:

	int currentDay;
	int currentTimeMinutes;

};


