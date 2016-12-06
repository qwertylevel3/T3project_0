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
		SkillBase();
		virtual ~SkillBase();
		virtual bool active();
		virtual SkillBase* createPrototype() = 0;
		void init(std::vector<std::string> skillMessage);

		std::string getDescription();
	protected:
		std::string getBaseDescription();
		virtual std::string getExtraDescription();
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
