#include "MPRecoveryCast.h"
#include "ToolFunction.h"
#include "FixedSelector.h"
#include "Dungeon.h"
#include "Character.h"

Skill::MPRecoveryCast::MPRecoveryCast()
{
}

Skill::MPRecoveryCast::~MPRecoveryCast()
{
}

Skill::MPRecoveryCast* Skill::MPRecoveryCast::createPrototype()
{
	return new MPRecoveryCast();
}

void Skill::MPRecoveryCast::run()
{
	FixedSelector selector;
	selector.addRelativeCoord(cocos2d::Point(0, 1));
	std::vector<cocos2d::Point > coords = selector.select(caster);
	cocos2d::Point targetCoord = coords[0];

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	Character* target = storey->getCharacter(targetCoord);
	cocos2d::Point targetPosition = storey->getTilePosition(targetCoord);

	//EffectManager::getInstance()->showEffect("HPRecovery", targetPosition, 1.0);

	if (target)
	{
		target->sufferMPEffect(value);
	}
}

void Skill::MPRecoveryCast::initExtraMessage(std::vector<std::string> extraMessage)
{
	value = ToolFunction::string2int(extraMessage[0]);
}