#include "Repel.h"
#include "ToolFunction.h"
#include "FixedSelector.h"
#include "Dungeon.h"
#include "Character.h"
#include "LinerSelector.h"

Skill::Repel::Repel()
{
}

Skill::Repel::~Repel()
{
}

Skill::Repel* Skill::Repel::createPrototype()
{
	return new Skill::Repel();
}

std::string Skill::Repel::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"效果:\n")
		+ ToolFunction::WStr2UTF8(L"击退面前单位并造成")
		+ ToolFunction::int2string(damage) + ToolFunction::WStr2UTF8(L"伤害");
}

void Skill::Repel::run()
{
	FixedSelector selector;
	selector.addRelativeCoord(cocos2d::Point(0, 1));
	std::vector<cocos2d::Point > coords = selector.select(caster);
	cocos2d::Point targetCoord = coords[0];

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	Character* target = storey->getCharacter(targetCoord);
	cocos2d::Point targetPosition = storey->getTilePosition(targetCoord);

	if (!target)
	{
		return;
	}

	target->sufferHPEffect(-damage);
	//////////////////////////////////////////////////////////////////////////


	cocos2d::Point offset;
	switch (caster->getOrientation())
	{
	case Character::UP:
		offset.x = 0;
		offset.y = -1;
		break;
	case Character::DOWN:
		offset.x = 0;
		offset.y = 1;
		break;
	case Character::LEFT:
		offset.x = -1;
		offset.y = 0;
		break;
	case Character::RIGHT:
		offset.x = 1;
		offset.y = 0;
		break;
	default:
		break;
	}

	int i;
	for (i = 1; i <= distance; i++)
	{
		cocos2d::Point targetCoord = target->getMapCoord();

		targetCoord = targetCoord + offset*i;

		if (!storey->isMoveAble(targetCoord)
			|| storey->getCharacter(targetCoord))
		{
			break;
		}
	}
	if (i==1)
	{
		return;
	}

	targetCoord = target->getMapCoord();
	targetCoord = targetCoord + offset*(i-1);

	storey->changeCharacterCoord(target, targetCoord);
}

void Skill::Repel::initExtraMessage(std::vector<std::string> extraMessage)
{
	distance = ToolFunction::string2int(extraMessage[0]);
	damage = ToolFunction::string2int(extraMessage[0]);
}