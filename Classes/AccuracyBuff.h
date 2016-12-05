#pragma once

#include "BuffBase.h"

namespace Buff
{
	class AccuracyBuff:public BuffBase
	{
	public:
		AccuracyBuff();
		~AccuracyBuff();
		void apply(Character* target);
		AccuracyBuff* createPrototype();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
		CC_SYNTHESIZE(int, accuracyOffset, AccuracyOffset);
	};
}
