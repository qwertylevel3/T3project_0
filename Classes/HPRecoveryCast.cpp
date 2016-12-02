#include "HPRecoveryCast.h"
#include "ToolFunction.h"
#include "FixedSelector.h"
#include "Dungeon.h"
#include "Character.h"




Skill::HPRecoveryCast::HPRecoveryCast(Character* character)
	:SkillBase(character)
{
}


Skill::HPRecoveryCast::~HPRecoveryCast()
{
}

Skill::HPRecoveryCast* Skill::HPRecoveryCast::createPrototype(Character* caster)
{
	return new HPRecoveryCast(caster);
}

void Skill::HPRecoveryCast::run()
{
	FixedSelector selector;
	selector.addRelativeCoord(cocos2d::Point(0, 1));
	std::vector<cocos2d::Point > coords=selector.select(caster);
	cocos2d::Point targetCoord = coords[0];

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	Character* target = storey->getCharacter(targetCoord);

	if (target)
	{
		target->sufferHPEffect(value);
	}
}

void Skill::HPRecoveryCast::initExtraMessage(std::vector<std::string> extraMessage)
{
	value = ToolFunction::string2int(extraMessage[0]);
}
