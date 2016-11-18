#pragma once

#include "Singleton.h"
#include <vector>
#include "base/ccTypes.h"

class Character;

namespace cocos2d
{
	class Sprite;
}

class RoundSystem:public cocos2d::Ref,public Singleton<RoundSystem>
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
	void round();
	void NPCAction(Character* character);
	void playerAction();
	int roundCount;
	int curIndex;
	std::vector<Character*> allCharacter;
	cocos2d::Sprite* chooseArrow;
};

