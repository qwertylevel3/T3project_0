#include "SingleDirectionSearchSelector.h"
#include "Character.h"
#include "Dungeon.h"



SingleDirectionSearchSelector::SingleDirectionSearchSelector()
{
	impactNumber = 1;
	deepth = 5;
}


SingleDirectionSearchSelector::~SingleDirectionSearchSelector()
{
}

std::vector<cocos2d::Point> SingleDirectionSearchSelector::select(Character* caster)
{
	cocos2d::Point directionOffset;
	cocos2d::Point leftOffset;
	cocos2d::Point rightOffset;

	switch (caster->getOrientation())
	{
	case Character::UP:
		directionOffset.x = 0;
		directionOffset.y = -1;
		leftOffset.x = -1;
		leftOffset.y = 0;
		rightOffset.x = 1;
		rightOffset.y = 0;
		break;
	case Character::DOWN:
		directionOffset.x = 0;
		directionOffset.y = 1;
		leftOffset.x = 1;
		leftOffset.y = 0;
		rightOffset.x = -1;
		rightOffset.y = 0;
		break;
	case Character::LEFT:
		directionOffset.x = -1;
		directionOffset.y = 0;
		leftOffset.x = 0;
		leftOffset.y = 1;
		rightOffset.x = 0;
		rightOffset.y = -1;
		break;
	case Character::RIGHT:
		directionOffset.x = 1;
		directionOffset.y = 0;
		leftOffset.x = 0;
		leftOffset.y = -1;
		rightOffset.x = 0;
		rightOffset.y = 1;
		break;
	default:
		break;
	}

	int impactCount=0;
	cocos2d::Point targetCoord = caster->getMapCoord();
	std::vector<cocos2d::Point> resultVec;
	for (int i=1;i<=deepth;i++)
	{
		cocos2d::Point directionCoord = targetCoord + directionOffset*i;
		std::vector<cocos2d::Point> tempVec;
		tempVec.push_back(directionCoord);
		
		for (int j=1;j<=deepth-i;j++)
		{
			cocos2d::Point leftCoord = directionCoord + leftOffset*j;
			cocos2d::Point rightCoord = directionCoord + rightOffset*j;

			tempVec.push_back(leftCoord);
			tempVec.push_back(rightCoord);
		}

		if (impactNumber == -1)
		{
			for each (cocos2d::Point target in tempVec)
			{
				resultVec.push_back(target);
			}
		}
		else
		{
			for each (cocos2d::Point target in tempVec)
			{
				Character* targetCharacter = Field::Dungeon::getInstance()->getCharacter(target);
				if (targetCharacter)
				{
					impactCount++;
					resultVec.push_back(target);
					if (impactCount>=impactNumber)
					{
						return resultVec;
					}
				}
			}
		}
	}
	return resultVec;

}

void SingleDirectionSearchSelector::setImpactNumber(int number)
{
	impactNumber = number;
}

void SingleDirectionSearchSelector::setDeepth(int d)
{
	deepth = d;
}
