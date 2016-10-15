#pragma once

#include <vector>
#include "base/ccTypes.h"

class Character;

class SelectorBase
{
public:
	SelectorBase();
	virtual ~SelectorBase();
	virtual std::vector<cocos2d::Point> select(Character* caster) = 0;
};
