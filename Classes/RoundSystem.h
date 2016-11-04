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
	void nextIndex();
	bool isPlayer(Character* character);
	void round(int index);
	void NPCAction(Character* character);
	void playerAction();
	int roundCount;
	int curIndex;
	std::vector<Character*> allCharacter;
};

