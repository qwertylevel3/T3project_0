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
		virtual SphereBase* createProtoType() = 0;
		void init(std::vector<std::string> sphereMessage);
		virtual std::string getDescription();
	protected:
		void initBaseMessage(std::vector<std::string> baseMessage);
		virtual void initExtraMessage(std::vector<std::string> extraMessage)=0;
		CC_SYNTHESIZE(std::string, cname, Cname);
		CC_SYNTHESIZE(std::string, id, ID);
	};
}
