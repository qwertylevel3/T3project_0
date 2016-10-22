#pragma once

#include "base/ccMacros.h"
#include <string>
#include <vector>

class Character;
class SelectorBase;

namespace Skill
{

	class EffectBase;

	class SkillBase
	{
	public:
		SkillBase(Character* character);
		virtual ~SkillBase();
		void addEffect(EffectBase* effect);
	protected:
		CC_SYNTHESIZE(std::string, name, Name);
		CC_SYNTHESIZE(std::string, cname, Cname);
		CC_SYNTHESIZE(Character*, caster, Caster);

		CC_SYNTHESIZE(SelectorBase*, selector, Selector);
		std::vector<EffectBase* > effectBox;

		//∫Û–¯÷∏’Î
		CC_SYNTHESIZE(SkillBase*, nextSkill, NextSkill);
		CC_SYNTHESIZE(int, mpCost, MpCost);
		virtual void active();
	};
}
