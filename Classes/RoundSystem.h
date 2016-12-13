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
	void startRound();
	void processAction(float dt);
	int getActionPoint();
	bool isSkipNextRound();
	void setSkipNextRound(bool b);
protected:
	Character* characterPtr;
	int actionPoint;
	float delayTime;
	bool skipNextRound;
};
	

class RoundSystem:public cocos2d::Node,public Singleton<RoundSystem>
{
public:
	RoundSystem();
	~RoundSystem();
	void start();
	bool init();
	void clear();
	void initMission();
	int getRoundCount();
	void sendNextRoundMessage();
	void unlockPlayerKey();
	void nextRound();
	void addCharacter(Character* character);


	//全部character是否都结束了回合
	//假如没有，那么是不能解除键盘锁定的(放置玩家攻击键按的太快造成连击)
	bool isCircleOver();
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

	bool circleOver;

};

