#pragma once
#include <string>

using std::string;

class Player {

public:

	void SetName(const std::string& name);
	const string& GetName() const;

private:

	std::string playerName;

};
