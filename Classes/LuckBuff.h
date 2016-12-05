#pragma once

#include "BuffBase.h"

namespace Buff
{
	class LuckBuff:public BuffBase
	{
	public:
		LuckBuff();
		~LuckBuff();
		void apply(Character* target);
		LuckBuff* createPrototype();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, luckOffset, LuckOffset);
	};
}
