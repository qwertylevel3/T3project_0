#pragma once

#include "SphereBase.h"

namespace Sphere
{
	class AntiChantSphere:public SphereBase
	{
	public:
		AntiChantSphere();
		~AntiChantSphere();
		void run(Character* a, Character* b, int damage);
		AntiChantSphere* createProtoType();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> extraMessage);
		CC_SYNTHESIZE(int, chantClearPro, ChantClearPro);
	};
}
