#include "SkillBase.h"
#include "SelectorBase.h"
#include "EffectBase.h"
#include "base/ccTypes.h"
#include <vector>
#include "HudMessageBox.h"

using namespace Skill;

SkillBase::SkillBase(Character* character)
{
	caster = character;
	selector = nullptr;
	mpCost = 0;
	chantCost = 0;
}

SkillBase::~SkillBase()
{
	delete selector;
}

void Skill::SkillBase::addEffect(EffectBase* effect)
{
	effectBox.push_back(effect);
}

bool Skill::SkillBase::active()
{
	if (chantCost > caster->getChant())
	{
		HudMessageBox::getInstance()->addMessage(L"吟唱点数不够");
		return false;
	}
	if (mpCost > caster->getMP())
	{
		HudMessageBox::getInstance()->addMessage(L"法力值不够");
		return false;
	}
	if (chantCost > 0)
	{
		caster->clearChant();
	}

	caster->sufferMPEffect(-mpCost);

	std::vector<cocos2d::Point> targetPositionVec;
	if (selector)
	{
		targetPositionVec = selector->select(caster);
	}
	for each (EffectBase* effect in effectBox)
	{
		effect->run(caster, targetPositionVec);
	}
	return true;
}