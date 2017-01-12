#include "BuffCast.h"
#include "EffectManager.h"
#include "Character.h"
#include "FixedSelector.h"
#include "Dungeon.h"
#include "ToolFunction.h"
#include "BuffFactory.h"
#include "BuffBase.h"




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

std::string Skill::BuffCast::getExtraDescription()
{
	std::string description;
	description+=ToolFunction::WStr2UTF8(L"效果:\n")
		+ ToolFunction::WStr2UTF8(L"对面前单位施加buff:");

	Buff::BuffBase* buff = Buff::BuffFactory::getInstance()->getBuff(buffID);
	description += buff->getDescription();
	delete buff;
	return description;
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
		EffectManager::getInstance()->showEffect("magicCircle", target->getPosition(), 0.5);
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
