#include "Chant.h"
#include "Character.h"
#include "FixedSelector.h"
#include "ToolFunction.h"
#include "ChantEffect.h"

Skill::Chant::Chant(Character* character)
	:SkillBase(character)
{
	FixedSelector* selector = new FixedSelector();
	//choose self
	selector->addRelativeCoord(0, 0);
	this->setSelector(selector);

	ChantEffect* effect = new ChantEffect();
	this->addEffect(effect);

	this->setName("chant");
	this->setCname(ToolFunction::WStr2UTF8(L"Ò÷³ª"));
}

Skill::Chant::~Chant()
{
}

bool Skill::Chant::active()
{
	std::vector<cocos2d::Point> targetPositionVec;
	for each (EffectBase* effect in effectBox)
	{
		effect->run(caster, targetPositionVec);
	}
	return true;
}