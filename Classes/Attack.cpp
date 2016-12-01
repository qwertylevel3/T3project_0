#include "Attack.h"
#include "AttackSelector.h"
#include "ToolFunction.h"
#include "BattleSystem.h"


using namespace Skill;

Attack::Attack(Character* caster)
	:SkillBase(caster)
{
	this->setCname(ToolFunction::WStr2UTF8(L"¹¥»÷"));
	this->setChantCost(0);
	this->setMpCost(0);
}


Attack::~Attack()
{
}

Skill::Attack* Skill::Attack::createPrototype(Character* caster)
{
	return new Attack(caster);
}

void Skill::Attack::initExtraMessage(std::vector<std::string> extraMessage)
{
	return;
}

void Skill::Attack::run()
{
	AttackSelector selector;
	std::vector<cocos2d::Point > coords=selector.select(caster);

	BattleSystem::getInstance()->attack(caster, coords);
}
