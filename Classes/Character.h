#pragma once

#include<cocos2d.h>

class Character:public cocos2d::CCSprite
{
public:
	static Character* create(const std::string& filename);
protected:
	Character();
	~Character();
	CC_SYNTHESIZE(cocos2d::Point, mapCoord, MapCoord);
};

