#pragma once

#include "BuffBase.h"

namespace Buff
{
	class BlockProBuff:public BuffBase
	{
	public:
		BlockProBuff();
		~BlockProBuff();
		void apply(Character* target);
		BlockProBuff* createPrototype();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, blockProOffset, BlockProOffset);
	};
}
