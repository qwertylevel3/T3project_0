#pragma once

#include "Character.h"

class AIBase
{
public:
	AIBase();
	virtual ~AIBase();
	virtual void update();
	virtual void feedback(Character* character);
	virtual void handleDialogueResult(std::string dialogueName,int resultNumber);
	void setCharacter(Character* character);
	Character* searchTargetBFS(Character::Type type);
	virtual void levelUp();
protected:
	Character* characterPtr;
	void seek(Character* target);
	void changeOrientationTo(Character* target);
	//逃跑，如果成功移动，返回true，否则返回false
	bool flee(Character* target);
	bool isInAttackArea(Character* target);
	bool isNear(cocos2d::Point coord);
};

