#pragma once

#include "SphereBase.h"

namespace Sphere
{
	class ActiveSkilllSphere:public SphereBase
	{
	public:
		ActiveSkilllSphere();
		~ActiveSkilllSphere();
		void run(Character* a, Character* b, int damage);
		ActiveSkilllSphere* createProtoType();
		std::string getDescription();
	protected:
		void initExtraMessage(std::vector<std::string> extraMessage);
		int activePro;
		std::string skillID;

	};
}
