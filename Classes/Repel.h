#pragma once

#include "SkillBase.h"

namespace Skill
{
	class Repel:public SkillBase
	{
	public:
		Repel();
		~Repel();
		Repel* createPrototype();
	protected:
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);

		int distance;
		int damage;
	};
}
