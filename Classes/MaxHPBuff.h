#pragma once

#include "BuffBase.h"

namespace Buff
{
	class MaxHPBuff:public BuffBase
	{
	public:
		MaxHPBuff();
		~MaxHPBuff();
		void apply(Character* target);
		MaxHPBuff* createPrototype();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, maxHPOffset, MaxHPOffset);
	};
}
