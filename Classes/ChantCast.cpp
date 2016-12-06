#include "ChantCast.h"
#include "ToolFunction.h"
#include "Character.h"
#include "Dungeon.h"
#include "FixedSelector.h"



Skill::ChantCast::ChantCast()
{
}


Skill::ChantCast::~ChantCast()
{
}

Skill::ChantCast* Skill::ChantCast::createPrototype()
{
	return new ChantCast();
}

std::string Skill::ChantCast::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"效果:\n")
		+ ToolFunction::WStr2UTF8(L"为面前单位增加吟唱点")
		+ ToolFunction::int2string(value);
}

void Skill::ChantCast::run()
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
		target->accumulateChant(value);
	}

}

void Skill::ChantCast::initExtraMessage(std::vector<std::string> extraMessage)
{
	value = ToolFunction::string2int(extraMessage[0]);
}
