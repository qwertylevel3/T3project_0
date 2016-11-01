#include "WeaponSphereHandler.h"
#include "SphereFactory.h"



WeaponSphereHandler::WeaponSphereHandler()
{
}


WeaponSphereHandler::~WeaponSphereHandler()
{
	for each (Sphere::SphereBase* sphere in sphereBox)
	{
		delete sphere;
	}
	sphereBox.clear();
}


std::vector<Sphere::SphereBase*>& WeaponSphereHandler::getSphereBoxRef()
{
	return sphereBox;
}

void WeaponSphereHandler::addSphere(const std::string& sphereID)
{
	Sphere::SphereBase* sphere = Sphere::SphereFactory::getInstance()->getSphere(sphereID);
	sphereBox.push_back(sphere);
}
