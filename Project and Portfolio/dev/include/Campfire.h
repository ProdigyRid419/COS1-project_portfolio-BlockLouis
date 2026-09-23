#pragma once
#include <iosfwd>

class Campfire {

public:

	bool IsBuilt() const;
	bool IsLit() const;
	int GetFuelMinutes() const;
	int GetAvailableFuelCap() const;

	void Build();
	int AddFuel(int woodAmount);
	void BurnForMinutes(int minutes);

	bool Save(std::ostream& output) const;
	bool Load(std::istream& input);

private:

	bool isBuilt = false;
	int fuelMinutes = 0;
	static constexpr int maximumBurnTime = 480;

};

