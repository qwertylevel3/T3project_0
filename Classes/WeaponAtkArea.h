#pragma once

#include <vector>
#include "base/ccTypes.h"

class WeaponAtkArea
{
public:
	WeaponAtkArea();
	~WeaponAtkArea();

	std::vector<cocos2d::Point>& getArea();
	void addPosition(cocos2d::Point position);
protected:
	std::vector<cocos2d::Point > area;
};

