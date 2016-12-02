#include "BuffCast.h"
#include "Character.h"
#include "FixedSelector.h"
#include "Dungeon.h"




Skill::BuffCast::BuffCast()
{
}


Skill::BuffCast::~BuffCast()
{
}

Skill::BuffCast* Skill::BuffCast::createPrototype()
{
	return new BuffCast();
}

void Skill::BuffCast::run()
{
	FixedSelector selector;
	selector.addRelativeCoord(cocos2d::Point(0, 1));
	std::vector<cocos2d::Point > coords=selector.select(caster);
	cocos2d::Point targetCoord = coords[0];

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	Character* target = storey->getCharacter(targetCoord);
	cocos2d::Point targetPosition = storey->getTilePosition(targetCoord);


	if (target)
	{
		target->addBuff(buffID);
	}

}

void Skill::BuffCast::initExtraMessage(std::vector<std::string> extraMessage)
{
	buffID = extraMessage[0];

	for (int i=1;i<extraMessage.size();i++)
	{
		buffID += "_" + extraMessage[i];
	}
}
