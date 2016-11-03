#pragma once

#include "SphereBase.h"

namespace Sphere
{
	class ManaBurnSphere:public SphereBase
	{
	public:
		ManaBurnSphere();
		~ManaBurnSphere();
		void run(Character* a, Character* b, int damage);
		ManaBurnSphere* createProtoType();
	protected:
		void initExtraMessage(std::vector<std::string> extraMessage);
		CC_SYNTHESIZE(int, mpDamagePer, MpDamagePer);
	};
}
