#pragma once

#include "EffectBase.h"
#include "base/ccMacros.h"

namespace Skill
{
	class MPEffect:public EffectBase
	{
	public:
		MPEffect();
		~MPEffect();
		bool run(Character* caster, std::vector<cocos2d::Point>& coord);
	protected:
		CC_SYNTHESIZE(int, mpOffset, MpOffset);
	};
}
