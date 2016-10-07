#pragma once

#include <vector>
#include "base/ccTypes.h"

namespace Skill
{
	class RunnerBase
	{
	public:
		RunnerBase();
		virtual ~RunnerBase();
		virtual void run(std::vector<cocos2d::Point>& position)=0;
	};
}
