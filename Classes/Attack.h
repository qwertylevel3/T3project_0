#pragma once

#include "SkillBase.h"

namespace Skill
{
	class Attack :public SkillBase
	{
	public:
		Attack(Character* caster);
		~Attack();
	};
}
