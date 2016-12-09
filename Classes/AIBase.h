#pragma once

#include "Character.h"

class AIBase
{
public:
	AIBase();
	virtual ~AIBase();
	virtual void update();
	virtual void interaction();
	virtual void handleDialogueResult(std::string dialogueName,int resultNumber);
	void setCharacter(Character* character);
	Character* searchTargetBFS(Character::Type type);
protected:
	Character* characterPtr;
	void seek(Character* target);
	void flee(Character* target);
	bool isInAttackArea(Character* target);
	bool isNear(cocos2d::Point coord);
};

