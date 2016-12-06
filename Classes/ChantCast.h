#pragma once

#include "SkillBase.h"

namespace Skill
{
	class ChantCast:public SkillBase
	{
	public:
		ChantCast();
		~ChantCast();
		ChantCast* createPrototype();
	protected:
		std::string getExtraDescription();
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		int value;
	};
}
