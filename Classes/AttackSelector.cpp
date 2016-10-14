#include "AttackSelector.h"
#include "Character.h"



Skill::AttackSelector::AttackSelector()
{
}


Skill::AttackSelector::~AttackSelector()
{
}

std::vector<cocos2d::Point> Skill::AttackSelector::select(Character* caster)
{
	return caster->getAtkArea();
}
