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
protected:
	cocos2d::Sprite* lightClipe;
	cocos2d::Sprite* light;
	cocos2d::ClippingNode* clipeNode;
	CC_SYNTHESIZE(int, size, Size);
	Character* character;
};

