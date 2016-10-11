#include "FrontSelector.h"
#include "Character.h"


using namespace Skill;

FrontSelector::FrontSelector()
{
}


FrontSelector::~FrontSelector()
{
}

std::vector<cocos2d::Point> Skill::FrontSelector::select(Character* caster)
{
	Character::Orientation orientation = caster->getOrientation();

	std::vector<cocos2d::Point> vec;
	cocos2d::Point targetPosition=caster->getMapCoord();
	switch (orientation)
	{
	case Character::UP:
		targetPosition.y -= 1;
		break;
	case Character::DOWN:
		targetPosition.y += 1;
		break;
	case Character::LEFT:
		targetPosition.x -= 1;
		break;
	case Character::RIGHT:
		targetPosition.x += 1;
		break;
	default:
		break;
	}
	vec.push_back(targetPosition);
	return vec;
}
