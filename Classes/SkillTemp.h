#pragma once

#include"cocos2d.h"
#include"2d\CCNode.h"

class Character;

class SkillTemp
{
	enum Direction
	{
		North,
		South,
		West,
		East,
		DirectionCount
	};
public:
	SkillTemp(Character* character);
	~SkillTemp();
	CC_SYNTHESIZE(Direction, direction, Direction);
	cocos2d::Animation* animation;
	virtual int run()=0;
	Character* caster;
};

