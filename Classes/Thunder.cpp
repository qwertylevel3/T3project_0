#include "Thunder.h"
#include "ToolFunction.h"
#include "FixedSelector.h"
#include "Dungeon.h"
#include "Character.h"



Skill::Thunder::Thunder()
{
}


Skill::Thunder::~Thunder()
{
}

Skill::Thunder* Skill::Thunder::createPrototype()
{
	return new Thunder();
}

std::string Skill::Thunder::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"效果")
		+ ToolFunction::WStr2UTF8(L"面前3x3范围内所有单位受到")
		+ ToolFunction::int2string(damage) + ToolFunction::WStr2UTF8(L"伤害");
}

void Skill::Thunder::run()
{
	FixedSelector selector;

	selector.addRelativeCoord(cocos2d::Point(0, 1));
	selector.addRelativeCoord(cocos2d::Point(-1, 1));
	selector.addRelativeCoord(cocos2d::Point(1, 1));

	selector.addRelativeCoord(cocos2d::Point(0, 2));
	selector.addRelativeCoord(cocos2d::Point(1, 2));
	selector.addRelativeCoord(cocos2d::Point(-1, 2));

	selector.addRelativeCoord(cocos2d::Point(0, 3));
	selector.addRelativeCoord(cocos2d::Point(1, 3));
	selector.addRelativeCoord(cocos2d::Point(-1, 3));

	std::vector<cocos2d::Point > coords=selector.select(caster);

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	for each (cocos2d::Point coord in coords)
	{
		Character* targetCharacter = storey->getCharacter(coord);
		if (targetCharacter)
		{
			targetCharacter->sufferHPEffect(-damage);
		}
	}
}

void Skill::Thunder::initExtraMessage(std::vector<std::string> extraMessage)
{
	damage = ToolFunction::string2int(extraMessage[0]);
}
