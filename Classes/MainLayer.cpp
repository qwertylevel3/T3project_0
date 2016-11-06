#include "MainLayer.h"
#include "SimpleAudioEngine.h"
#include"RandomNumber.h"
#include"StoreyBuilder.h"
#include"CharacterFactory.h"
#include"Player.h"
#include"Dungeon.h"
#include"InventoryFactory.h"
#include"MonsterFactory.h"
#include "BattleSystem.h"
#include "RoundSystem.h"
#include "KeyController.h"
#include "MaskLayer.h"
#include "HudLayer.h"
#include "BuffFactory.h"
#include "SphereFactory.h"

USING_NS_CC;
using namespace Field;


// on "init" you need to initialize your instance
bool MainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	/////////////////////////////
    
	RandomNumber::getInstance()->setSeed(333);

	Buff::BuffFactory::getInstance()->init();
	Sphere::SphereFactory::getInstance()->init();
	InventoryFactory::getInstance()->init();
	CharacterFactory::getInstance()->init();
	Player::getInstance()->init();
	MonsterFactory::getInstance()->init();

	BattleSystem::getInstance()->init();

	KeyController::getInstance()->init();


//	Debug::getInstance()->init(HudLayer::getInstance());

	loadStorey();
	RoundSystem::getInstance()->init();
	RoundSystem::getInstance()->loadStorey();



	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		this->handleKeyPressed(keyCode);
		//Player::getInstance()->handleKeyPressed(keyCode);
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		this->handleKeyReleased(keyCode);
		//Player::getInstance()->handleKeyReleased(keyCode);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	this->scheduleUpdate();

	return true;
}

void MainLayer::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainLayer::setViewPointCenter(Point position) {
	Storey* storey = Dungeon::getInstance()->getStorey();
	TMXTiledMap* tileMap = storey->getTileMap();
	auto winSize = Director::getInstance()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (tileMap->getMapSize().width * tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	//移动整个层，将position移到屏幕中心
	this->setPosition(viewPoint);
	//顺带移动mask层
	MaskLayer::getInstance()->setPosition(viewPoint);
}

void MainLayer::update(float dt)
{
	Character* player = Player::getInstance()->getcharacterPtr();
	this->setViewPointCenter(player->getPosition());
	HudLayer::getInstance()->update();
	MaskLayer::getInstance()->update();
}

void MainLayer::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	KeyController::getInstance()->handleKeyPressed(keyCode);
}

void MainLayer::handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode)
{
	KeyController::getInstance()->handleKeyReleased(keyCode);
}



void MainLayer::loadStorey()
{
	Dungeon::getInstance()->generate(1);
	Dungeon::getInstance()->writeToFile();
	Storey* floor0 = Dungeon::getInstance()->getStorey();

//	dungeon->writeToFile();
//	std::string fileName = "1.tmx";
//	std::string filePath = FileUtils::getInstance()->getWritablePath();
//	filePath=filePath+fileName;
//	auto str = String::createWithContentsOfFile(filePath);

	Layer::addChild(floor0->getTileMap(), -1);

	cocos2d::Point startPosition = floor0->getUpCoord();
	//cocos2d::Point startPosition(0, 0);

	//player = Character::create("test_character.plist");

	std::list<Character* > chList = floor0->getAllCharacter();
	for each (Character*  character in chList)
	{
		Layer::addChild(character->getSprite());
	}

	Character* player = Player::getInstance()->getcharacterPtr();

	player->setMapCoord(floor0->getUpCoord());
	this->addCharacter(player);

	setViewPointCenter(player->getPosition());
}

void MainLayer::addCharacter(Character * character)
{
	Layer::addChild(character->getSprite(),10);

	Dungeon::getInstance()->addCharacter(character);
}

cocos2d::Point MainLayer::getWorldPosition(cocos2d::Point position)
{
	return position + this->getPosition();
}
