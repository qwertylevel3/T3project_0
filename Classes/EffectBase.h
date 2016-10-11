#pragma once

#include <vector>
#include "base/ccTypes.h"
#include "Character.h"

namespace Skill
{
	class EffectBase
	{
	public:
		EffectBase();
		virtual ~EffectBase();
		virtual void run(Character* caster,std::vector<cocos2d::Point>& coord)=0;
	};
}
