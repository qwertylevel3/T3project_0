#include "MaskLayer.h"
#include "Dungeon.h"
#include "Player.h"
#include "Dungeon.h"
#include "Marco.h"
#include "Illuminant.h"

USING_NS_CC;

//#define DEBUG_MASKLAYER

MaskLayer::MaskLayer()
{
}

MaskLayer::~MaskLayer()
{
	clear();
}

bool MaskLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	mask = nullptr;
	this->scheduleUpdate();

	return true;
}

void MaskLayer::update(float dt)
{
	for each (Illuminant* light in lightBox)
	{
		light->update();
	}
	if (!mask)
	{
		return;
	}

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	mask->clear(0, 0, 0, 0);
	//////////////////////////////////////////////////////////////////////////
	mask->begin();

	Sprite* bk = Sprite::create("mask/dark.png");
	bk->setScale(storey->getWidth() * 32 / bk->getContentSize().width);
	bk->setPosition(storey->getWidth() * 16, storey->getHeight() * 16);

	ccBlendFunc func0 = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA };
	ccBlendFunc func1 = { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };

	bk->setBlendFunc(func1);
	bk->visit();

	for each (Illuminant* light in lightBox)
	{
		Sprite* lightSprite = light->getLight();
		lightSprite->setBlendFunc(func0);
		lightSprite->visit();
	}

	mask->end();
	//mask->saveToFile("temp.png");
}

void MaskLayer::darkOn()
{
	this->setVisible(true);
}

void MaskLayer::darkOff()
{
	this->setVisible(false);
}

void MaskLayer::clear()
{
	if (mask)
	{
		mask->removeFromParent();
	}

	for each (Illuminant* light in lightBox)
	{
		delete light;
	}
	lightBox.clear();
}

void MaskLayer::loadStorey()
{
	clear();

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	//////////////////////////////////////////////////////////////////////////

//	Sprite* bk = Sprite::create("dark.png");
//	bk->setScale(storey->getWidth() * 32 / bk->getContentSize().width);
//	bk->setPosition(storey->getWidth() * 16 , storey->getHeight() * 16);
//	this->addChild(bk);

//////////////////////////////////////////////////////////////////////////

	mask = RenderTexture::create(storey->getWidth() * 32, storey->getHeight() * 32);
	mask->setPosition(storey->getWidth() * 16, storey->getHeight() * 16);

	this->addChild(mask, 10);

	std::list<Character* > allCharacter = storey->getAllCharacter();

	for each (Character* character in allCharacter)
	{
		if (character->getCharacterType() != Character::Bad)
		{
			Illuminant* light = new Illuminant(character);
			addLight(light);
		}
	}

	darkOff();
}

void MaskLayer::addLight(Illuminant* light)
{
	lightBox.push_back(light);
}