#include "LinerSelector.h"
#include "Character.h"
#include "Dungeon.h"



Skill::LinerSelector::LinerSelector()
{
	orientation = UP;
	impactNumber = 1;
	maxLength = 5;
}


Skill::LinerSelector::~LinerSelector()
{
}

std::vector<cocos2d::Point> Skill::LinerSelector::select(Character* caster)
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
			if (storey->isValid(targetCoord))
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

void Skill::LinerSelector::setOrientation(LinerOrientation ori)
{
	orientation = ori;
}

void Skill::LinerSelector::setImpactNumber(int number)
{
	impactNumber = number;
}

void Skill::LinerSelector::setMaxLength(int length)
{
	maxLength = length;
}

cocos2d::Point Skill::LinerSelector::getOffset(Character* caster)
{
	cocos2d::Point offset(0, 0);
	switch (orientation)
	{
	case Skill::LinerSelector::ZERO:
		break;
	case Skill::LinerSelector::UP:
		offset.y--;
		break;
	case Skill::LinerSelector::DOWN:
		offset.y++;
		break;
	case Skill::LinerSelector::LEFT:
		offset.x--;
		break;
	case Skill::LinerSelector::RIGHT:
		offset.x++;
		break;
	case Skill::LinerSelector::UPLEFT:
		offset.x--;
		offset.y--;
		break;
	case Skill::LinerSelector::UPRIGHT:
		offset.x++;
		offset.y--;
		break;
	case Skill::LinerSelector::DOWNLEFT:
		offset.x--;
		offset.y++;
		break;
	case Skill::LinerSelector::DOWNRIGHT:
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
