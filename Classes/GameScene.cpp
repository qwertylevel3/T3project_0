#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include"DungeonBuilder.h"
#include"RandomNumber.h"
#include"StoreyBuilder.h"
#include"CharacterManager.h"
#include"SkillManager.h"
#include"Debug.h"
#include"HudLayer.h"
#include"RoundCounter.h"
#include"Player.h"
#include"InventoryMenu.h"

USING_NS_CC;
using namespace Field;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
	auto hudLayer = HudLayer::getInstance();

    // add layer as a child to scene
	scene->addChild(hudLayer,1);
    scene->addChild(layer);


    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	isControlPlayer = true;

	/////////////////////////////
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	RandomNumber::getInstance()->setSeed(100);

	DungeonBuilder::getInstance()->init();
	CharacterManager::getInstance()->init();
	SkillManager::getInstance()->init();
	Player::getInstance()->init();

//	Debug::getInstance()->init(HudLayer::getInstance());

//	std::stringstream ss;
//	std::string str;
//	ss << RoundCounter::getInstance()->getRoundCount();
//	ss >> str;
//	Debug::getInstance()->showMessage(str, cocos2d::Point(100, 100));
	HudLayer::getInstance()->addSender(RoundCounter::getInstance());

	dungeon=DungeonBuilder::getInstance()->generate(1);
//	dungeon->writeToFile();
	Storey* floor0 = dungeon->getStorey();

//	dungeon->writeToFile();
//	std::string fileName = "1.tmx";
//	std::string filePath = FileUtils::getInstance()->getWritablePath();
//	filePath=filePath+fileName;
//	auto str = String::createWithContentsOfFile(filePath);

	Layer::addChild(floor0->getTileMap(), -1);

	cocos2d::Point startPosition = floor0->getUpPosition();
	//cocos2d::Point startPosition(0, 0);

	//player = Character::create("test_character.plist");
	Character* testCharacter = CharacterManager::getInstance()->getCharacter("Actor0");

	Character* player = Player::getInstance()->getcharacterPtr();
	player->setPosition(startPosition.x*32+16, (100-startPosition.y)*32-16);
	testCharacter->setPosition((startPosition.x + 1) * 32 + 16, (100 - startPosition.y) * 32 - 16);

	player->setMapCoord(floor0->getUpPosition());
	Point testCharacterPosition=player->getMapCoord();
	testCharacterPosition.x = testCharacterPosition.x + 1;
	testCharacter->setMapCoord(testCharacterPosition);
//	player->setPosition(32, 32);
	
	this->addCharacter(testCharacter);
	this->addCharacter(player);

	setViewPointCenter(player->getPosition());

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

void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameScene::setViewPointCenter(Point position) {
	Storey* storey = dungeon->getStorey();
	TMXTiledMap* tileMap = storey->getTileMap();
	auto winSize = Director::getInstance()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (tileMap->getMapSize().width * tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}

void GameScene::update(float dt)
{
	Character* player = Player::getInstance()->getcharacterPtr();
	this->setViewPointCenter(player->getPosition());
	HudLayer::getInstance()->update();
}

void GameScene::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
	{
		switchControl();
	}
	if (isControlPlayer)
	{
		Player::getInstance()->handleKeyPressed(keyCode);
	}
	else
	{

	}
}

void GameScene::handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (isControlPlayer)
	{
		Player::getInstance()->handleKeyReleased(keyCode);
	}
	else
	{

	}
}

void GameScene::switchControl()
{
	if (isControlPlayer)
	{
		InventoryMenu::getInstance()->show();
	}
	else
	{
		InventoryMenu::getInstance()->hide();
	}
	isControlPlayer = !isControlPlayer;
}

void GameScene::addCharacter(Character * character)
{
	Layer::addChild(character->getSprite());

	character->setScene(this);
	dungeon->addCharacter(character);
}
