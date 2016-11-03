#pragma once

#include "BuffBase.h"

namespace Buff
{
	class MaxMPBuff:public BuffBase
	{
	public:
		MaxMPBuff();
		~MaxMPBuff();
		void apply(Character* target);
		MaxMPBuff* createPrototype();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, maxMPOffset, MaxMPOffset);
	};
}
