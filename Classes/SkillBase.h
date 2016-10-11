#pragma once

#include "base/ccMacros.h"
#include <string>

class Character;

namespace Skill
{
	class SelectorBase;
	class EffectBase;

	class SkillBase
	{
	public:
		SkillBase(Character* character);
		virtual ~SkillBase();
	protected:
		CC_SYNTHESIZE(std::string, name, Name);
		CC_SYNTHESIZE(Character*, caster, Caster);

		CC_SYNTHESIZE(SelectorBase*, selector, Selector);
		CC_SYNTHESIZE(EffectBase*, effector, Effector);

		//∫Û–¯÷∏’Î
		CC_SYNTHESIZE(SkillBase*, nextSkill, NextSkill);
		void active();
	};
}
