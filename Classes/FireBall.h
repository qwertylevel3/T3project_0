#pragma once

#include "SkillBase.h"

namespace Skill
{
	class FireBall:public SkillBase
	{
	public:
		FireBall(Character* character);
		~FireBall();
	};
}
