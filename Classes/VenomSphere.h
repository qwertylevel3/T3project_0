#pragma once

#include "SphereBase.h"

namespace Sphere
{
	class VenomSphere:public SphereBase
	{
	public:
		VenomSphere();
		~VenomSphere();
		void run(Character* a, Character* b, int damage);
		VenomSphere* createProtoType();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> extraMessage);
		CC_SYNTHESIZE(std::string, venomDamage, VenomDamage);
	};
}
