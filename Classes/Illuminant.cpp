#include "Illuminant.h"
#include "cocos2d.h"
#include "MaskLayer.h"
#include "Character.h"
#include "2d/CCSprite.h"



Illuminant::Illuminant(Character* c)
{
	character = c;

	size = c->getViewSize();

	lightClipe = cocos2d::Sprite::create("testLight2.png");
	light = cocos2d::Sprite::create("light.png");
	cocos2d::ccBlendFunc cbl = { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA };
	light->setBlendFunc(cbl);

	light->setScale(size);
	lightClipe->setScale(size);

	light->retain();
	lightClipe->retain();
}


Illuminant::~Illuminant()
{
	light->release();
	lightClipe->release();
}

void Illuminant::update()
{
	if (character->getViewSize()!=size)
	{
		size = character->getViewSize();
		light->setScale(size);
		lightClipe->setScale(size);
	}
	light->setPosition(character->getPosition());
	lightClipe->setPosition(character->getPosition());
}

cocos2d::Sprite* Illuminant::getLightClipe()
{
	return lightClipe;
}

cocos2d::Sprite* Illuminant::getLight()
{
	return light;
}

Character* Illuminant::getCharacter()
{
	return character;
}
