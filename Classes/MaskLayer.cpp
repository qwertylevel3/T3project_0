#include "MaskLayer.h"
#include "Dungeon.h"
#include "Player.h"
#include "cocos2d.h"

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
	dark = Sprite::create("dark.png");
	dark->setScale(s.width / dark->getTexture()->getPixelsWide());
//	this->addChild(dark);

	lightClipe = Sprite::create("testlight.png");
	light = Sprite::create("testlight.png");
	this->addChild(light);

	

	CCClippingNode* clipeNode = CCClippingNode::create();
	clipeNode->setInverted(true);

	this->addChild(clipeNode);
	clipeNode->addChild(dark);
	clipeNode->setStencil(lightClipe);


//	CCClippingNode* light = CCClippingNode::create();
//	light->setInverted(true);
//	this->addChild(light);

	return true;
}

void MaskLayer::update()
{
	dark->setPosition(Player::getInstance()->getcharacterPtr()->getPosition());
	lightClipe->setPosition(Player::getInstance()->getcharacterPtr()->getPosition());
	light->setPosition(Player::getInstance()->getcharacterPtr()->getPosition());
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

