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

		CC_SYNTHESIZE(int, mpCost, MpCost);
		CC_SYNTHESIZE(int, chantCost, ChantCost);
		virtual bool active();
	};
}
