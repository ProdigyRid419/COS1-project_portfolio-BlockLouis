#pragma once

class Campfire {

public:

	bool IsBuilt() const;
	bool IsLit() const;
	int GetFuelMinutes() const;
	int GetAvailableFuelCap() const;

	void Build();
	int AddFuel(int woodAmount);
	void BurnForMinutes(int minutes);

private:

	bool isBuilt = false;
	int fuelMinutes = 0;
	const int maximumBurnTime = 480;

};

