#include "AreaSearchSelector.h"
#include "Character.h"
#include "Dungeon.h"



AreaSearchSelector::AreaSearchSelector()
{
	deepth = 5;
	impactNumber = 1;
}


AreaSearchSelector::~AreaSearchSelector()
{
}

std::vector<cocos2d::Point> AreaSearchSelector::select(Character* caster)
{
	std::vector<cocos2d::Point> vec;
	return vec;
}

void AreaSearchSelector::setDeepth(int d)
{
	deepth = d;
}


void AreaSearchSelector::setImpactNumber(int number)
{
	impactNumber = number;
}
