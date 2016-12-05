#pragma once

#include "BuffBase.h"

namespace Buff
{
	class ChantBuff:public BuffBase
	{
	public:
		ChantBuff();
		~ChantBuff();
		void apply(Character* target);
		ChantBuff* createPrototype();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, addPer, AddPer);
	};
}
