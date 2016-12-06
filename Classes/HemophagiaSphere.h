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
		HemophagiaSphere* createProtoType() ;
		std::string getDescription();
	protected:
		virtual void initExtraMessage(std::vector<std::string> extraMessage);
		CC_SYNTHESIZE(int, healPer, HealPer);
	};
}
