#pragma once

#include <vector>
#include "base/ccTypes.h"

class Character;

class WeaponAtkArea
{
public:
	WeaponAtkArea();
	~WeaponAtkArea();

	std::vector<cocos2d::Point> getAtkArea(Character* attacker);
	void addPosition(cocos2d::Point position);
	void copyAtkAreaData(WeaponAtkArea* atkArea);
	void clear();
protected:
	std::vector<cocos2d::Point > area;
};

