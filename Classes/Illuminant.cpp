#include "Illuminant.h"
#include "ToolFunction.h"
#include "Dungeon.h"
#include "cocos2d.h"
#include "MaskLayer.h"
#include "Character.h"
#include "2d/CCSprite.h"


Illuminant::Illuminant()
{
	light = cocos2d::Sprite::create("mask/testLight2.png");
	cocos2d::BlendFunc func0 = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA };
	light->setBlendFunc(func0);
	light->retain();

	extinguish = false;

}

Illuminant::~Illuminant()
{
	light->release();
}

cocos2d::Sprite* Illuminant::getLight()
{
	return light;
}

bool Illuminant::isExtinguish()
{
	return extinguish;
}

//////////////////////////////////////////////////////////////////////////




IlluminantForCharacter::IlluminantForCharacter(Character* c)
{
	character = c;
	size = c->getViewSize();

	light->setScale(size);
}


IlluminantForCharacter::~IlluminantForCharacter()
{
}

void IlluminantForCharacter::update()
{
	if (character->isDead())
	{
		light->setVisible(false);
	}
	if (character->getViewSize()!=size)
	{
		size = character->getViewSize();
		light->setScale(size);
	}
	light->setPosition(character->getPosition());
}

Character* IlluminantForCharacter::getCharacter()
{
	return character;
}


//////////////////////////////////////////////////////////////////////////




IlluminantFixed::IlluminantFixed(int lightSize,cocos2d::Point lightCoord,int dt)
{
	startTime = ToolFunction::getCurTime();

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	cocos2d::Point position = storey->getTilePosition(lightCoord);
	light->setPosition(position);
	light->setScale(lightSize);

	delayTime = dt;
}

IlluminantFixed::~IlluminantFixed()
{

}

void IlluminantFixed::update()
{
	int curTime = ToolFunction::getCurTime();

	if (curTime-startTime>delayTime)
	{
		extinguish = true;
	}
}
