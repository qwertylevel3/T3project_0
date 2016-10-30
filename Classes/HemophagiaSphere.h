#pragma once

#include "SphereBase.h"

namespace Sphere
{
	class HemophagiaSphere:public SphereBase
	{
	public:
		HemophagiaSphere();
		~HemophagiaSphere();
		void run(Character* a,Character* b,int damage);
	protected:
		CC_SYNTHESIZE(int, healPer, HealPer);
	};
}
