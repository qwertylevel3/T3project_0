#pragma once

#include<cocos2d.h>
#include"Dungeon.h"

class Character:public cocos2d::CCSprite
{
public:
	static Character* create(const std::string& filename);
protected:
	Character();
	~Character();
	CC_SYNTHESIZE(cocos2d::Point, mapCoord, MapCoord);
	CC_SYNTHESIZE(int, strength, Strength);
	CC_SYNTHESIZE(int, intellect, Intellect);
	CC_SYNTHESIZE(int, agility, Agility);
	CC_SYNTHESIZE(int, HP, HP);
	CC_SYNTHESIZE(int, MP, MP);
	CC_SYNTHESIZE(int, curHP, CurHP);
	CC_SYNTHESIZE(int, curMP, CurMP);
	CC_SYNTHESIZE(Field::Dungeon*, dungeon, Dungeon);
};

