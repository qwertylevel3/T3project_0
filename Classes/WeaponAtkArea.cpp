#include "WeaponAtkArea.h"



WeaponAtkArea::WeaponAtkArea()
{
}


WeaponAtkArea::~WeaponAtkArea()
{
}

std::vector<cocos2d::Point>& WeaponAtkArea::getArea()
{
	return area;
}

void WeaponAtkArea::addPosition(cocos2d::Point position)
{
	area.push_back(position);
}
