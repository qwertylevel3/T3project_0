#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"DungeonBuilder.h"
#include"RandomNumber.h"
#include"StoreyBuilder.h"

USING_NS_CC;
using namespace Field;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	RandomNumber::getInstance()->setSeed(100);

	DungeonBuilder::getInstance()->init();
	dungeon=DungeonBuilder::getInstance()->generate(4);
//	dungeon->writeToFile();
	Storey* floor0 = dungeon->getStorey();

//	dungeon->writeToFile();
//	std::string fileName = "1.tmx";
//	std::string filePath = FileUtils::getInstance()->getWritablePath();
//	filePath=filePath+fileName;
//	auto str = String::createWithContentsOfFile(filePath);

	tileMap = TMXTiledMap::createWithXML(floor0->getFileContent(), "");

	addChild(tileMap, -1);

	cocos2d::Point startPosition = floor0->getUpPosition();
	//cocos2d::Point startPosition(0, 0);

	player = Character::create("Player.png");

	player->setPosition(startPosition.x*32+16, (100-startPosition.y)*32-16);
	player->setMapCoord(floor0->getUpPosition());
//	player->setPosition(32, 32);
	addChild(player);

	setViewPointCenter(player->getPosition());

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		this->movePlayer(keyCode);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::setViewPointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (tileMap->getMapSize().width * this->tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}

void HelloWorld::movePlayer(EventKeyboard::KeyCode keyCode)
{
	if (!isMoveAble(keyCode))
	{
		return;
	}
	cocos2d::Point position;
	cocos2d::Point mapCoord = player->getMapCoord();
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		position.x = player->getPosition().x;
		position.y = player->getPosition().y + 32;
		movePlayer(position);
		player->setMapCoord(cocos2d::Point(mapCoord.x, mapCoord.y - 1));
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		position.x = player->getPosition().x;
		position.y = player->getPosition().y - 32;
		movePlayer(position);
		player->setMapCoord(cocos2d::Point(mapCoord.x, mapCoord.y + 1));
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		position.x = player->getPosition().x - 32;
		position.y = player->getPosition().y;
		movePlayer(position);
		player->setMapCoord(cocos2d::Point(mapCoord.x - 1, mapCoord.y));
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		position.x = player->getPosition().x + 32;
		position.y = player->getPosition().y;
		movePlayer(position);
		player->setMapCoord(cocos2d::Point(mapCoord.x + 1, mapCoord.y));
		break;
	}
}

void HelloWorld::movePlayer(cocos2d::Point position)
{
	player->setPosition(position);
	this->setViewPointCenter(player->getPosition());
}

bool HelloWorld::isMoveAble(EventKeyboard::KeyCode keyCode)
{
	Storey* storey = dungeon->getStorey();
	cocos2d::Point position = player->getMapCoord();
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		position.y -= 1;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		position.y += 1;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		position.x -= 1;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		position.x += 1;
		break;
	default:
		return false;
	}

	if (storey->getTile(position) == Field::Floor)
	{
		return true;
	}
	return false;
}
