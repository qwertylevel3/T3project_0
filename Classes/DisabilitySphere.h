#pragma once

#include "SphereBase.h"

namespace Sphere
{
	class DisabilitySphere:public SphereBase
	{
	public:
		DisabilitySphere();
		~DisabilitySphere();
		void run(Character* a, Character* b, int damage);
		DisabilitySphere* createProtoType();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> extraMessage);
		CC_SYNTHESIZE(std::string, strOffset, StrOffset);
		CC_SYNTHESIZE(std::string, agiOffset, AgiOffset);
		CC_SYNTHESIZE(std::string, intOffset, IntOffset);
	};
}
