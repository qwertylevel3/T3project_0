#pragma once

#include "BuffBase.h"

namespace Buff
{
	class BuffAutoHeal:public BuffBase
	{
	public:
		BuffAutoHeal();
		~BuffAutoHeal();
		void apply(Character* target);
	};
}
