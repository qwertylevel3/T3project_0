#include "Summon.h"
#include "MonsterFactory.h"
#include "Dungeon.h"
#include "FixedSelector.h"
#include "ToolFunction.h"



Skill::Summon::Summon()
{
}


Skill::Summon::~Summon()
{
}

Skill::Summon* Skill::Summon::createPrototype()
{
	return new Summon();
}

void Skill::Summon::run()
{
	Character* summonCharacter = MonsterFactory::getInstance()->getMonster(characterName);
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	FixedSelector selector;
	selector.addRelativeCoord(cocos2d::Point(0, 1));
	std::vector<cocos2d::Point > coords=selector.select(caster);
	cocos2d::Point targetCoord = coords[0];

	//如果在面前已经有了单位或者这个地方不合法
	if (storey->getCharacter(targetCoord)
		|| !storey->isMoveAble(targetCoord))
	{
		targetCoord = ToolFunction::validPlace(targetCoord);
	}

	storey->addCharacter(targetCoord, summonCharacter);
}

void Skill::Summon::initExtraMessage(std::vector<std::string> extraMessage)
{
	characterName = extraMessage[0];
}
