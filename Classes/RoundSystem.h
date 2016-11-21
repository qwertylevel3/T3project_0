#pragma once

#include "Singleton.h"
#include <vector>
#include "base/ccTypes.h"
#include "2d/CCNode.h"

class Character;

namespace cocos2d
{
	class Sprite;
	class EventListenerCustom;
}


class RoundHandler
{
public:
	RoundHandler(Character* character);
	~RoundHandler();
//	void useActionPoint();
	void processAction(float delayTime);
protected:
	Character* characterPtr;
	int actionPoint;
	float delayTime;

};
	

class RoundSystem:public cocos2d::Node,public Singleton<RoundSystem>
{
public:
	RoundSystem();
	~RoundSystem();
	void start();
	bool init();
	void loadStorey();
	int getRoundCount();
	void sendNextRoundMessage();
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
	cocos2d::EventListenerCustom* listener;
};

