#include "Attack.h"
#include "FrontSelector.h"
#include "AttackEffect.h"


using namespace Skill;

Attack::Attack(Character* caster)
	:SkillBase(caster)
{
	FrontSelector* frontSelector = new FrontSelector();
	this->setSelector(frontSelector);
	AttackEffect* attackEffect = new AttackEffect();
	this->setEffector(attackEffect);

	this->setName("attack");
}


Attack::~Attack()
{
}
