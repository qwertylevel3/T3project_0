#include "FireBall.h"
#include "LinerSelector.h"
#include "FireBallEffect.h"
#include "ToolFunction.h"



Skill::FireBall::FireBall(Character* character)
	:SkillBase(character)
{
	LinerSelector* selector = new LinerSelector();
	FireBallEffect* effect = new FireBallEffect();

	this->setSelector(selector);
	this->addEffect(effect);

	this->setName("FireBall");
	this->setCname(ToolFunction::WStr2UTF8(L"¿ìËÙ»ðÇò"));
	this->setChantCost(20);
	this->setMpCost(20);
}


Skill::FireBall::~FireBall()
{
}
