#pragma once

#include "EffectBase.h"
#include "base/ccTypes.h"

namespace Skill
{
	class FireBallEffect :public EffectBase
	{
	public:
		FireBallEffect();
		~FireBallEffect();
		bool run(Character* caster, std::vector<cocos2d::Point>& coord);
	protected:
		void showFireBall(cocos2d::Point oriPosition,cocos2d::Point dstPosition);
	};
}
