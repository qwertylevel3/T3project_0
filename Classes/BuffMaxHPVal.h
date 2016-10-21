#pragma once

#include "BuffBase.h"

namespace Buff
{
	class BuffMaxHPVal :public BuffBase
	{
	public:
		BuffMaxHPVal();
		~BuffMaxHPVal();
		void apply(Character* target);
		void setHPOffset(int offset);
	protected:
		int hpOffset;
	};
}
