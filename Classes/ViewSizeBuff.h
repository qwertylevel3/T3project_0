#pragma once

#include "BuffBase.h"

namespace Buff
{
	class ViewSizeBuff:public BuffBase
	{
	public:
		ViewSizeBuff();
		~ViewSizeBuff();
		void apply(Character* target);
		ViewSizeBuff* createPrototype();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, viewSizeOffset, ViewSizeOffset);
	};
}
