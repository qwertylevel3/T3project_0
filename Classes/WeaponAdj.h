#pragma once

//#include"platform\CCPlatformMacros.h"
#include"cocos2d.h"

class WeaponAdj
{
public:
	WeaponAdj();
	~WeaponAdj();
protected:
	CC_SYNTHESIZE(std::string, adjName, AdjName);
};

