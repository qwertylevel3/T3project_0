#include "FixedSelector.h"
#include "Character.h"



Skill::FixedSelector::FixedSelector()
{
}


Skill::FixedSelector::~FixedSelector()
{
}

std::vector<cocos2d::Point> Skill::FixedSelector::select(Character* caster)
{
	cocos2d::Point basePoint = caster->getMapCoord();
	std::vector<cocos2d::Point> tempArea;

	switch (caster->getOrientation())
	{
	case Character::UP:
		for each (cocos2d::Point point in relativeCoord)
		{
			cocos2d::Point tempPoint;
			tempPoint.x = point.x + basePoint.x;
			tempPoint.y = -point.y + basePoint.y;
			tempArea.push_back(tempPoint);
		}
		break;
	case Character::DOWN:
		for each (cocos2d::Point point in relativeCoord)
		{
			cocos2d::Point tempPoint;
			tempPoint.x = -point.x + basePoint.x;
			tempPoint.y = point.y + basePoint.y;
			tempArea.push_back(tempPoint);
		}
		break;
	case Character::LEFT:
		for each (cocos2d::Point point in relativeCoord)
		{
			cocos2d::Point tempPoint;
			tempPoint.x = -point.y + basePoint.x;
			tempPoint.y = point.x + basePoint.y;
			tempArea.push_back(tempPoint);
		}
		break;
	case Character::RIGHT:
		for each (cocos2d::Point point in relativeCoord)
		{
			cocos2d::Point tempPoint;
			tempPoint.x = point.y + basePoint.x;
			tempPoint.y = -point.x + basePoint.y;
			tempArea.push_back(tempPoint);
		}
		break;
	}
	return tempArea;
}

void Skill::FixedSelector::addRelativeCoord(cocos2d::Point coord)
{
	relativeCoord.push_back(coord);
}

void Skill::FixedSelector::addRelativeCoord(int x, int y)
{
	relativeCoord.push_back(cocos2d::Point(x, y));
}
