#include "Summon.h"
#include "Character.h"
#include "GameActorFactory.h"
#include "FriendCreatureManager.h"
#include "Dungeon.h"
#include "FixedSelector.h"
#include "ToolFunction.h"
#include "EffectManager.h"

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

std::string Skill::Summon::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"效果:\n")
		+ ToolFunction::WStr2UTF8(L"召唤")
		+ characterName;
}

void Skill::Summon::run()
{
	Character* summonCharacter = GameActorFactory::getInstance()->getActor(characterName);
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	FixedSelector selector;
	selector.addRelativeCoord(cocos2d::Point(0, 1));
	std::vector<cocos2d::Point > coords = selector.select(caster);
	cocos2d::Point targetCoord = coords[0];

	//如果在面前已经有了单位或者这个地方不合法
	if (storey->getCharacter(targetCoord)
		|| !storey->isMoveAble(targetCoord))
	{
		targetCoord = ToolFunction::findValidPlace(
			Field::Dungeon::getInstance()->getStorey(),
			targetCoord
		);
	}

	storey->addCharacter(targetCoord, summonCharacter);
	if (summonCharacter->getPlayType() == Character::Friend)
	{
		FriendCreatureManager::getInstance()->addCharacter(summonCharacter);
	}

	EffectManager::getInstance()->showEffect("summon", summonCharacter->getPosition(), 0.5);
}

void Skill::Summon::initExtraMessage(std::vector<std::string> extraMessage)
{
	characterName = extraMessage[0];
}