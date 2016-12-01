#pragma once

#include "SkillBase.h"

namespace Skill
{
	class Chant :public SkillBase
	{
	public:
		Chant(Character* character);
		~Chant();
	protected:
		void run();
	};
}
