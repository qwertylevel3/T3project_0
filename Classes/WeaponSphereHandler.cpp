#include "WeaponSphereHandler.h"



WeaponSphereHandler::WeaponSphereHandler()
{
}


WeaponSphereHandler::~WeaponSphereHandler()
{
}

std::vector<Sphere::SphereBase*>& WeaponSphereHandler::getSphereBoxRef()
{
	return sphereBox;
}
