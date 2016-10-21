#pragma once

#include "BuffBase.h"

namespace Buff
{
	class BuffMaxHPPer:public BuffBase
	{
	public:
		BuffMaxHPPer();
		~BuffMaxHPPer();
		void setPercent(int per);
		void apply(Character* target);
	protected:
		int percent;
	};
}
