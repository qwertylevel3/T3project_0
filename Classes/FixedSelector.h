#pragma once

#include "SelectorBase.h"

class FixedSelector :public SelectorBase
{
public:
	FixedSelector();
	~FixedSelector();
	std::vector<cocos2d::Point> select(Character* caster);
	void addRelativeCoord(cocos2d::Point coord);
	void addRelativeCoord(int x, int y);
protected:
	//相对于caster的坐标
	//向上为正y，向右为正x
	std::vector<cocos2d::Point> relativeCoord;
};
