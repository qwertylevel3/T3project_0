#pragma once

#include <vector>

namespace Sphere
{
	class SphereBase;
}


class WeaponSphereHandler
{
public:
	WeaponSphereHandler();
	~WeaponSphereHandler();
	std::vector<Sphere::SphereBase*>& getSphereBoxRef();
protected:
	std::vector<Sphere::SphereBase*> sphereBox;
};
