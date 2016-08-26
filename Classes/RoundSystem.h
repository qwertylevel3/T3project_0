#pragma once

#include "Singleton.h"
#include <vector>

class Character;

class RoundSystem:public Singleton<RoundSystem>
{
public:
	RoundSystem();
	~RoundSystem();
	void init();
	void loadStorey();
	int getRoundCount();
	void nextRound();
protected:
	int roundCount;
	std::vector<Character*> allCharacter;
};

