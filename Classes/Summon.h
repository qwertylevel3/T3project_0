#pragma once

#include "SkillBase.h"
#include <string>

namespace Skill
{
	class Summon:public SkillBase
	{
	public:
		Summon();
		~Summon();
		Summon* createPrototype();
	protected:
		std::string getExtraDescription();
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);

		std::string characterName;
	};
}
