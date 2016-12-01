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
		virtual SkillBase* createPrototype(Character* caster) = 0;
		void init(std::vector<std::string> skillMessage);
	protected:
		void initBaseMessage(std::vector<std::string> baseMessage);
		virtual void initExtraMessage(std::vector<std::string> extraMessage)=0;

		void initCName(std::string cn);
		void initChantCost(std::string chantCostStr);
		void initMPCost(std::string MPCostStr);

		bool cost();
		virtual void run();

		CC_SYNTHESIZE(std::string, id, ID);
		CC_SYNTHESIZE(std::string, cname, Cname);
		CC_SYNTHESIZE(Character*, caster, Caster);
		CC_SYNTHESIZE(int, mpCost, MpCost);
		CC_SYNTHESIZE(int, chantCost, ChantCost);

	};
}
