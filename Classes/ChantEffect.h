#pragma once

#include "EffectBase.h"

namespace Skill
{
	class ChantEffect:public EffectBase
	{
	public:
		ChantEffect();
		~ChantEffect();
		bool run(Character* caster, std::vector<cocos2d::Point>& coord);
	};
}
