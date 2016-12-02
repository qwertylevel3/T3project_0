#include "LinerSelector.h"
#include "Character.h"
#include "Dungeon.h"



LinerSelector::LinerSelector()
{
	orientation = UP;
	impactNumber = 1;
	maxLength = 5;
}


LinerSelector::~LinerSelector()
{
}

std::vector<cocos2d::Point> LinerSelector::select(Character* caster)
{
	std::vector<cocos2d::Point> vec;
	cocos2d::Point offset = getOffset(caster);
	cocos2d::Point targetCoord = caster->getMapCoord();

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	int impactCount=0;
	for (int i=0;i<maxLength;i++)
	{
		targetCoord += offset;
		if (impactNumber<0)
		{
			if (storey->isMoveAble(targetCoord)
				&& !storey->getCharacter(targetCoord))
			{
				vec.push_back(targetCoord);
			}
		}
		else
		{
			Character* targetCharacter = Field::Dungeon::getInstance()->getCharacter(targetCoord);
			if (targetCharacter)
			{
				vec.push_back(targetCoord);
				impactCount++;
				if (impactCount>=impactNumber)
				{
					return vec;
				}
			}
		}
	}
	return vec;
}

void LinerSelector::setOrientation(LinerOrientation ori)
{
	orientation = ori;
}

void LinerSelector::setImpactNumber(int number)
{
	impactNumber = number;
}

void LinerSelector::setMaxLength(int length)
{
	maxLength = length;
}

cocos2d::Point LinerSelector::getOffset(Character* caster)
{
	cocos2d::Point offset(0, 0);
	switch (orientation)
	{
	case LinerSelector::ZERO:
		break;
	case LinerSelector::UP:
		offset.y--;
		break;
	case LinerSelector::DOWN:
		offset.y++;
		break;
	case LinerSelector::LEFT:
		offset.x--;
		break;
	case LinerSelector::RIGHT:
		offset.x++;
		break;
	case LinerSelector::UPLEFT:
		offset.x--;
		offset.y--;
		break;
	case LinerSelector::UPRIGHT:
		offset.x++;
		offset.y--;
		break;
	case LinerSelector::DOWNLEFT:
		offset.x--;
		offset.y++;
		break;
	case LinerSelector::DOWNRIGHT:
		offset.x++;
		offset.y++;
		break;
	default:
		break;
	}

	int temp;
	switch (caster->getOrientation())
	{
	case Character::UP:
		break;
	case Character::DOWN:
		offset.y = -offset.y;
		offset.x = -offset.x;
		break;
	case Character::LEFT:
		temp = -offset.x;
		offset.x = offset.y;
		offset.y = temp;
		break;
	case Character::RIGHT:
		temp = offset.x;
		offset.x = -offset.y;
		offset.y = temp;
		break;
	default:
		break;
	}
	return offset;
}
