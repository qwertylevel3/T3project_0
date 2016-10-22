#include "Attack.h"
#include "AttackSelector.h"
#include "AttackEffect.h"
#include "ToolFunction.h"


using namespace Skill;

Attack::Attack(Character* caster)
	:SkillBase(caster)
{
	AttackSelector* selector = new AttackSelector();
	this->setSelector(selector);
	AttackEffect* attackEffect = new AttackEffect();
	this->addEffect(attackEffect);

	this->setName("attack");
	this->setCname(ToolFunction::WStr2UTF8(L"¹¥»÷"));
}


Attack::~Attack()
{
}
