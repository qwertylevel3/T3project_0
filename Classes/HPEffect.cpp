#include "HPEffect.h"
#include "Dungeon.h"



Skill::HPEffect::HPEffect()
{
}


Skill::HPEffect::~HPEffect()
{
}

bool Skill::HPEffect::run(Character* caster, std::vector<cocos2d::Point>& coord)
{
	bool success=true;
	for each (cocos2d::Point point in coord)
	{
		Character* target = Field::Dungeon::getInstance()->getCharacter(point);
		if (target)
		{
			if (!target->sufferHPEffect(hpOffset))
			{
				success = false;
			}
		}
	}
	return success;
}
