#pragma once

#include "BuffBase.h"

namespace Buff
{
	class BaseAttrBuff:public BuffBase
	{
	public:
		BaseAttrBuff();
		~BaseAttrBuff();
		void apply(Character* target);
		BaseAttrBuff* createPrototype();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, strOffset, StrOffset);
		CC_SYNTHESIZE(int, agiOffset, AgiOffset);
		CC_SYNTHESIZE(int, intOffset, IntOffset);
	};
}
