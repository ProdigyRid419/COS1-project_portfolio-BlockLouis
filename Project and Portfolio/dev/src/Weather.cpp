#include "Weather.h"
#include <cstdlib>
#include <iostream>

WeatherType Weather::GetWeatherType() const {

	return currentWeather;

}

int Weather::GetTemp() const {

	switch (currentWeather) {

	case WeatherType::Coldsnap:

		return 30;

	case WeatherType::Rainstorm:

		return 40;

	case WeatherType::Overcast:

		return 50;

	case WeatherType::Clear:

		return 60;

	case WeatherType::Heatwave:

		return 80;

	}

	return 60;

}

void Weather::RandomizeWeather() {

	int randomNumber = rand() % 5;

	currentWeather = static_cast<WeatherType>(randomNumber);

}

bool Weather::Save(std::ostream& output) const {

	output << static_cast<int>(currentWeather) << '\n';
	if (!static_cast<bool>(output)) {

		return false;

	}

	return true;

}

bool Weather::Load(std::istream& input) {

	int loadedWeather = 0;

	input >> loadedWeather;
	if (!static_cast<bool>(input)) {

		return false;

	}

	if (loadedWeather < static_cast<int>(WeatherType::Coldsnap) || loadedWeather > static_cast<int>(WeatherType::Heatwave)) {

		return false;

	}

	currentWeather = static_cast<WeatherType>(loadedWeather);
	return true;

}

void Weather::DisplayWeather() const {

	std::cout << "\n\n=== Weather ===\n\nCurrent weather: ";

	switch (currentWeather) {

	case WeatherType::Coldsnap:

		std::cout << "Coldsnap";
		break;

	case WeatherType::Rainstorm:

		std::cout << "Rainstorm";
		break;

	case WeatherType::Overcast:

		std::cout << "Overcast";
		break;

	case WeatherType::Clear:

		std::cout << "Clear";
		break;

	case WeatherType::Heatwave:

		std::cout << "Heatwave";
		break;

	}

	std::cout << "\nTemperature: " << GetTemp() << '\n';

}
