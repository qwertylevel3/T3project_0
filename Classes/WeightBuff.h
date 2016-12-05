#pragma once

#include "BuffBase.h"

namespace Buff
{
	class WeightBuff:public BuffBase
	{
	public:
		WeightBuff();
		~WeightBuff();
		void apply(Character* target);
		WeightBuff* createPrototype();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, weightOffset, WeightOffset);
	};
}
