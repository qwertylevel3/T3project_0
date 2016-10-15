#include "AttackSelector.h"
#include "Character.h"



AttackSelector::AttackSelector()
{
}


AttackSelector::~AttackSelector()
{
}

std::vector<cocos2d::Point> AttackSelector::select(Character* caster)
{
	return caster->getAtkArea();
}
