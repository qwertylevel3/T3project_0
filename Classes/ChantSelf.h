#pragma once

#include "SkillBase.h"

namespace Skill
{
	class ChantSelf:public SkillBase
	{
	public:
		ChantSelf();
		~ChantSelf();
		ChantSelf* createPrototype();
	protected:
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		int value;
	};
}
