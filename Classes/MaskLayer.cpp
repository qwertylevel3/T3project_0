#include "MaskLayer.h"
#include "Dungeon.h"
#include "Player.h"
#include "cocos2d.h"
#include "Dungeon.h"
#include "Dungeon.h"

USING_NS_CC;


MaskLayer::MaskLayer()
{
}


MaskLayer::~MaskLayer()
{
}

bool MaskLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	scanWidth = 10;
	scanHeight = 10;

    auto s = Director::getInstance()->getWinSize();
    
    //auto draw = DrawNode::create();
    //addChild(draw, 10);
    
    // draw a line
	//cocos2d::Point startPoint = getTilePosition(Point(1,1));
    //draw->drawLine(startPoint, Vec2(s.width, s.height), Color4F(1.0, 0.0, 0.0, 0.5));
//	dark = Sprite::create("dark.png");

//	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
//	int width = storey->getWidth() * 32;
//	int height = storey->getHeight() * 32;

//	dark->setScale(width / dark->getTexture()->getPixelsWide());
//	dark->setPosition(width / 2,height/2);



//	lightClipe = Sprite::create("light.png");
//	light = Sprite::create("light.png");
//	lightClipe->setScale(1.5);
//	light->setScale(1.5);
//	this->addChild(light);

//	ClippingNode* clipeNode = ClippingNode::create();
//	clipeNode->setInverted(true);
//	this->addChild(clipeNode);

//	//先涂黑，再把有light的地方挖出来
//	clipeNode->addChild(dark);
//	clipeNode->setStencil(lightClipe);


////	CCClippingNode* light = CCClippingNode::create();
////	light->setInverted(true);
////	this->addChild(light);

//	darkOn();
	return true;
}

void MaskLayer::update()
{
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	std::list<Character*> allCharacter = storey->getAllCharacter();

	for each (Character* character in allCharacter)
	{
		if (character->getCharacterType()!=Character::Bad)
		{
		}
	}

//	dark->setPosition(Player::getInstance()->getcharacterPtr()->getPosition());
//	lightClipe->setPosition(Player::getInstance()->getcharacterPtr()->getPosition());
//	light->setPosition(Player::getInstance()->getcharacterPtr()->getPosition());
}

cocos2d::Point MaskLayer::getTilePosition(cocos2d::Point coord)
{
//	int x = MAX(position.x, winSize.width / 2);
//	int y = MAX(position.y, winSize.height / 2);
//	x = MIN(x, (tileMap->getMapSize().width * tileMap->getTileSize().width) - winSize.width / 2);
//	y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - winSize.height / 2);
//	auto actualPosition = Point(x, y);

	return Player::getInstance()->getcharacterPtr()->getPosition();
}

void MaskLayer::calculateEdge(cocos2d::Point position)
{

}

void MaskLayer::darkOn()
{
	darkSwitch = true;
	dark->setVisible(true);
	lightClipe->setVisible(true);
	light->setVisible(true);
}

void MaskLayer::darkOff()
{
	darkSwitch = false;
	dark->setVisible(false);
	lightClipe->setVisible(false);
	light->setVisible(false);
}

void MaskLayer::addIlluminant(Illuminant* light)
{

}

void MaskLayer::clear()
{
	removeAllChildren();
}

