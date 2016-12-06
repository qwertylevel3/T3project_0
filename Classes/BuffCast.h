#pragma once

#include "SkillBase.h"
#include <string>

namespace Skill
{
	class BuffCast:public SkillBase
	{
	public:
		BuffCast();
		~BuffCast();
		BuffCast* createPrototype();
	protected:
		std::string getExtraDescription();
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);

		std::string buffID;
	};
}
