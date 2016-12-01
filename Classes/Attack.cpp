#include "Attack.h"
#include "AttackSelector.h"
#include "ToolFunction.h"
#include "BattleSystem.h"


using namespace Skill;

Attack::Attack(Character* caster)
	:SkillBase(caster)
{
	this->setName("attack");
	this->setCname(ToolFunction::WStr2UTF8(L"¹¥»÷"));
	this->setChantCost(0);
	this->setMpCost(0);
}


Attack::~Attack()
{
}

void Skill::Attack::run()
{
	AttackSelector selector;
	std::vector<cocos2d::Point > coords=selector.select(caster);

	BattleSystem::getInstance()->attack(caster, coords);
}
