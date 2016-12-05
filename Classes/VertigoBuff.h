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
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> baseMessage);
	};
}
