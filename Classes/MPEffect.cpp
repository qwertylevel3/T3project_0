#include "MPEffect.h"
#include "Dungeon.h"
#include "Character.h"



Skill::MPEffect::MPEffect()
{
}


Skill::MPEffect::~MPEffect()
{
}

bool Skill::MPEffect::run(Character* caster, std::vector<cocos2d::Point>& coord)
{
	bool success=true;
	for each (cocos2d::Point point in coord)
	{
		Character* target = Field::Dungeon::getInstance()->getCharacter(point);
		if (target)
		{
			if (!target->sufferMPEffect(mpOffset))
			{
				success = false;
			}
		}
	}
	return success;
}
