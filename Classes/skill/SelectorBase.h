#pragma once

#include <vector>
#include "base/ccTypes.h"


namespace Skill
{
	class SelectorBase
	{
	public:
		SelectorBase();
		virtual ~SelectorBase();
		virtual std::vector<cocos2d::Point> select()=0;
	};
}
