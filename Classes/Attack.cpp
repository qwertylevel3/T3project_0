#include "Attack.h"
#include "AttackSelector.h"
#include "AttackEffect.h"


using namespace Skill;

Attack::Attack(Character* caster)
	:SkillBase(caster)
{
	AttackSelector* selector = new AttackSelector();
	this->setSelector(selector);
	AttackEffect* attackEffect = new AttackEffect();
	this->setEffector(attackEffect);

	this->setName("attack");
}


Attack::~Attack()
{
}
