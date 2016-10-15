#pragma once

#include "SelectorBase.h"

class SingleDirectionSearchSelector:public SelectorBase
{
public:
	SingleDirectionSearchSelector();
	~SingleDirectionSearchSelector();
	std::vector<cocos2d::Point> select(Character* caster);
	void setImpactNumber(int number);
	void setDeepth(int d);
protected:
	int impactNumber;
	int deepth;
};

