#pragma once

#include "BuffBase.h"

namespace Buff
{
	class BlockPointBuff:public BuffBase
	{
	public:
		BlockPointBuff();
		~BlockPointBuff();
		void apply(Character* target);
		BlockPointBuff* createPrototype();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, blockPointOffset, BlockPointOffset);
	};
}
