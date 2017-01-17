#include "HPCastAccordInt.h"
#include "EffectManager.h"
#include "Dungeon.h"
#include "FixedSelector.h"
#include "ToolFunction.h"
#include "Character.h"



Skill::HPCastAccordInt::HPCastAccordInt()
{
}


Skill::HPCastAccordInt::~HPCastAccordInt()
{
}

Skill::HPCastAccordInt* Skill::HPCastAccordInt::createPrototype()
{
	return new Skill::HPCastAccordInt();
}

std::string Skill::HPCastAccordInt::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"效果:\n")
		+ ToolFunction::WStr2UTF8(L"面前单位回复:(")
		+ ToolFunction::int2string(valuePer) 
		+ToolFunction::WStr2UTF8(L"% x [智力])")
		+ ToolFunction::WStr2UTF8(L"生命值");
}

void Skill::HPCastAccordInt::run()
{
	FixedSelector selector;
	selector.addRelativeCoord(cocos2d::Point(0, 1));
	std::vector<cocos2d::Point > coords=selector.select(caster);
	cocos2d::Point targetCoord = coords[0];

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	Character* target = storey->getCharacter(targetCoord);
	cocos2d::Point targetPosition = storey->getTilePosition(targetCoord);

	EffectManager::getInstance()->showEffect("HPRecovery", targetPosition, 1.0);

	if (target)
	{
		int value = double(valuePer)*double(caster->getIntellect()) / 100.0;
		target->sufferHPEffect(value);
	}

}

void Skill::HPCastAccordInt::initExtraMessage(std::vector<std::string> extraMessage)
{
	valuePer = ToolFunction::string2int(extraMessage[0]);
}
