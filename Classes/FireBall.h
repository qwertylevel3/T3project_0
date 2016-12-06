#pragma once

#include "SkillBase.h"
#include "base/ccTypes.h"

namespace Skill
{
	class FireBall:public SkillBase
	{
	public:
		FireBall();
		~FireBall();
		FireBall* createPrototype();
	protected:
		std::string getExtraDescription();
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		void showFireBall(cocos2d::Point oriPosition,cocos2d::Point dstPosition);

		int damage;
		int distance;
	};
}
