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
	void addSphere(const std::string& sphereID);
protected:
	std::vector<Sphere::SphereBase*> sphereBox;
};
