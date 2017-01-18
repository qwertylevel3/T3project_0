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
	Character* searchTargetBFS(Character::Type type,int distance);


	virtual void levelUp();
	//死亡触发
	virtual void lastWords();
protected:
	Character* characterPtr;
	//计算character和target之间的麦哈顿距离
	int getManhattanDistance(Character* target);

	void seek(Character* target);
	
	void goNextStep(
		cocos2d::Point startPoint,
		cocos2d::Point endPoint,
		cocos2d::Point nextStep
	);



	void changeOrientationTo(Character* target);
	//逃跑，如果成功移动，返回true，否则返回false
	bool flee(Character* target);
	bool isInAttackArea(Character* target);
	bool isNear(cocos2d::Point coord);

	//获得原点周围的所有对应目标
	std::vector<Character* > getTargetAround(
		cocos2d::Point ori,
		Character::Type type,
		int searchSize
	);


	//某个位置是否可以到达
	bool isAccessAble(cocos2d::Point coord);
	
	//向targetCoord逼近
	void approach(cocos2d::Point targetCoord);


	//闲逛
	void wander();
	bool isPlayerNear();
};

