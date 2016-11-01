#pragma once

#include <map>
#include <vector>
#include "Singleton.h"

namespace Sphere
{
	class SphereBase;

	class SphereFactory:public Singleton<SphereFactory>
	{
	public:
		SphereFactory();
		~SphereFactory();
		void init();
		SphereBase* getSphere(const std::string& sphereID);
	protected:
		std::map<std::string, SphereBase*> sphereBox;
		void split(std::string s, char splitchar, std::vector<std::string>& vec);
	};
}
