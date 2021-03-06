#pragma once

#include "SelectorBase.h"


class AreaSearchSelector:public SelectorBase
{
public:
	AreaSearchSelector();
	~AreaSearchSelector();
	std::vector<cocos2d::Point> select(Character* caster);
	void setDeepth(int d);
	void setImpactNumber(int number);
protected:
	int deepth;
	int impactNumber;
};

