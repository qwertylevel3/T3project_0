#pragma once

#include "BuffBase.h"

namespace Buff
{
	class BuffAgiVal:public BuffBase
	{
	public:
		BuffAgiVal();
		~BuffAgiVal();
		void apply(Character* target);
		void setOffset(int offset);
	protected:
		int agiOffset;
	};
}
