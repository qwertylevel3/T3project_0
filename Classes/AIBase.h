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
	//死亡触发
	virtual void lastWords();
protected:
	Character* characterPtr;
	//计算character和target之间的麦哈顿距离
	int getManhattanDistance(Character* target);
	void seek(Character* target);
	void changeOrientationTo(Character* target);
	//逃跑，如果成功移动，返回true，否则返回false
	bool flee(Character* target);
	bool isInAttackArea(Character* target);
	bool isNear(cocos2d::Point coord);
	
	//向targetCoord逼近
	void seek(cocos2d::Point targetCoord);

	bool isPlayerNear();
};

