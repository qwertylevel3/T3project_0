#pragma once

#include "BuffBase.h"

namespace Buff
{
	class VertigoBuff:public BuffBase
	{
	public:
		VertigoBuff();
		~VertigoBuff();
		void apply(Character* target);
		VertigoBuff* createPrototype();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
	};
}
