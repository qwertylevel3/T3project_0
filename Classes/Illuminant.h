#pragma once

#include "base/ccMacros.h"
#include "base/ccTypes.h"

class Character;

namespace cocos2d
{
	class Sprite;
	class ClippingNode;
}

class Illuminant
{
public:
	Illuminant();
	~Illuminant();
	virtual void update() = 0;
	cocos2d::Sprite* getLight();
	bool isExtinguish();
protected:
	cocos2d::Sprite* light;
	CC_SYNTHESIZE(int, size, Size);
	bool extinguish;
};

class IlluminantForCharacter:public Illuminant
{
public:
	IlluminantForCharacter(Character* c);
	~IlluminantForCharacter();
	void update();
	Character* getCharacter();
protected:
	Character* character;
};


class IlluminantFixed :public Illuminant
{
public:
	IlluminantFixed(int lightSize,cocos2d::Point lightCoord,int dt);
	~IlluminantFixed();
	void update();
protected:
	int startTime;
	int delayTime;
};

