#include "Illuminant.h"
#include "cocos2d.h"
#include "MaskLayer.h"
#include "Character.h"
#include "2d/CCSprite.h"



Illuminant::Illuminant(Character* c)
{
	character = c;

	size = c->getViewSize();

	light = cocos2d::Sprite::create("mask/testLight2.png");
	cocos2d::BlendFunc func0 = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA };
	light->setBlendFunc(func0);

	light->setScale(size);
	light->retain();
}


Illuminant::~Illuminant()
{
	light->release();
}

void Illuminant::update()
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

cocos2d::Sprite* Illuminant::getLight()
{
	return light;
}

Character* Illuminant::getCharacter()
{
	return character;
}
