#pragma once

#include "SelectorBase.h"

class AttackSelector :public SelectorBase
{
public:
	AttackSelector();
	~AttackSelector();
	std::vector<cocos2d::Point> select(Character* caster);
};
