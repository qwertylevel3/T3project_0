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
		virtual bool active();
	protected:
		bool cost();
		virtual void run();

		CC_SYNTHESIZE(std::string, name, Name);
		CC_SYNTHESIZE(std::string, cname, Cname);
		CC_SYNTHESIZE(Character*, caster, Caster);
		CC_SYNTHESIZE(int, mpCost, MpCost);
		CC_SYNTHESIZE(int, chantCost, ChantCost);

	};
}
