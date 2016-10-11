#pragma once

#include "SelectorBase.h"


namespace Skill
{
	class FrontSelector:public SelectorBase
	{
	public:
		FrontSelector();
		~FrontSelector();
		std::vector<cocos2d::Point> select(Character* caster);
	};
}
