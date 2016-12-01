#pragma once

#include "SkillBase.h"
#include "base/ccTypes.h"

namespace Skill
{
	class FireBall:public SkillBase
	{
	public:
		FireBall(Character* character);
		~FireBall();
	protected:
		void run();
		void showFireBall(cocos2d::Point oriPosition,cocos2d::Point dstPosition);
	};
}
