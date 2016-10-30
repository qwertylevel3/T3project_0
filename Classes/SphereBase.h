#pragma once

#include <base/ccMacros.h>

class Character;

namespace Sphere
{
	class SphereBase
	{
	public:
		SphereBase();
		virtual ~SphereBase();
		virtual void run(Character* a,Character* b,int damage)=0;
	protected:
		CC_SYNTHESIZE(std::string, cname, Cname);
	};
}
