#pragma once

#include"Character.h"
#include"platform\CCPlatformMacros.h"

class Skill
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
	Skill(Character* character);
	~Skill();
	virtual int run()=0;
	Character* caster;
	CC_SYNTHESIZE(Direction, directioni, Direction);
};

