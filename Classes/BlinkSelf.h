#pragma once

#include "SkillBase.h"

namespace Skill
{
	class BlinkSelf:public SkillBase
	{
	public:
		BlinkSelf();
		~BlinkSelf();
		BlinkSelf* createPrototype();
	protected:
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);

		int distance;
	};
}
