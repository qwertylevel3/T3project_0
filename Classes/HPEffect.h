#pragma once

#include "EffectBase.h"
#include "base/ccMacros.h"


namespace Skill
{
	class HPEffect :public EffectBase
	{
	public:
		HPEffect();
		~HPEffect();
		bool run(Character* caster, std::vector<cocos2d::Point>& coord);
	protected:
		CC_SYNTHESIZE(int, hpOffset, HpOffset);
	};
}
