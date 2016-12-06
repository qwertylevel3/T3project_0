#pragma once

#include "SphereBase.h"

namespace Sphere
{
	class MagicphagiaSphere:public SphereBase
	{
	public:
		MagicphagiaSphere();
		~MagicphagiaSphere();
		void run(Character* a, Character* b, int damage);
		MagicphagiaSphere* createProtoType();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> extraMessage);
		CC_SYNTHESIZE(int, healPer, HealPer);
	};
}
