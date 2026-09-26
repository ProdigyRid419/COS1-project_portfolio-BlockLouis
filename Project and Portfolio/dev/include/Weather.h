#pragma once
#include <iosfwd>

enum class WeatherType {

	Coldsnap, Rainstorm, Overcast, Clear, Heatwave

};

class Weather {

public:

	WeatherType GetWeatherType() const;
	int GetTemp() const;

	void RandomizeWeather();
	void DisplayWeather() const;

	bool Save(std::ostream& output) const;
	bool Load(std::istream& input);

private:

	WeatherType currentWeather = WeatherType::Clear;




};

