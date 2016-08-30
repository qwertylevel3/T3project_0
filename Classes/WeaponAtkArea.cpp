#include "WeaponAtkArea.h"
#include "Character.h"



WeaponAtkArea::WeaponAtkArea()
{
}


WeaponAtkArea::~WeaponAtkArea()
{
}

std::vector<cocos2d::Point> WeaponAtkArea::getAtkArea(Character* attacker)
{
	std::vector<cocos2d::Point> tempArea;
	cocos2d::Point basePoint = attacker->getMapCoord();
	switch (attacker->getOrientation())
	{
	case Character::UP:
		for each (cocos2d::Point point in area)
		{
			cocos2d::Point tempPoint;
			tempPoint.x = point.x + basePoint.x;
			tempPoint.y = point.y + basePoint.y;
			tempArea.push_back(tempPoint);
		}
		break;
	case Character::DOWN:
		for each (cocos2d::Point point in area)
		{
			cocos2d::Point tempPoint;
			tempPoint.x = -point.x + basePoint.x;
			tempPoint.y = -point.y + basePoint.y;
			tempArea.push_back(tempPoint);
		}
		break;
	case Character::LEFT:
		for each (cocos2d::Point point in area)
		{
			cocos2d::Point tempPoint;
			tempPoint.x = -point.y + basePoint.x;
			tempPoint.y = point.x + basePoint.y;
			tempArea.push_back(tempPoint);
		}
		break;
	case Character::RIGHT:
		for each (cocos2d::Point point in area)
		{
			cocos2d::Point tempPoint;
			tempPoint.x = point.y + basePoint.x;
			tempPoint.y = -point.x + basePoint.y;
			tempArea.push_back(tempPoint);
		}
		break;
	default:
		CCAssert(false, "character is in error orientation");
	}
	return tempArea;
}

void WeaponAtkArea::addPosition(cocos2d::Point position)
{
	area.push_back(position);
}

void WeaponAtkArea::copyAtkAreaData(WeaponAtkArea* atkArea)
{
	atkArea->clear();
	for each (cocos2d::Point point in area)
	{
		atkArea->addPosition(point);
	}
}

void WeaponAtkArea::clear()
{
	area.clear();
}
