#pragma once

#include "base/ccMacros.h"

class Character;

namespace cocos2d
{
	class Sprite;
	class ClippingNode;
}

class Illuminant
{
public:
	Illuminant(Character* c);
	~Illuminant();
	void update();
	cocos2d::Sprite* getLight();
	Character* getCharacter();
protected:
	cocos2d::Sprite* light;
	CC_SYNTHESIZE(int, size, Size);
	Character* character;
};

