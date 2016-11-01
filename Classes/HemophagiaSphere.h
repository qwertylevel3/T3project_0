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
		virtual SphereBase* makeProtoType() ;
	protected:
		virtual void initExtraMessage(std::vector<std::string> extraMessage);
		CC_SYNTHESIZE(int, healPer, HealPer);
	};
}
