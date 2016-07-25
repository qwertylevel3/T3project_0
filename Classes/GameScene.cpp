#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include"DungeonBuilder.h"
#include"RandomNumber.h"
#include"StoreyBuilder.h"
#include"CharacterManager.h"
#include"SkillManager.h"

USING_NS_CC;
using namespace Field;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
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
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	RandomNumber::getInstance()->setSeed(100);

	DungeonBuilder::getInstance()->init();
	CharacterManager::getInstance()->init();
	SkillManager::getInstance()->init();


	dungeon=DungeonBuilder::getInstance()->generate(4);
//	dungeon->writeToFile();
	Storey* floor0 = dungeon->getStorey();

//	dungeon->writeToFile();
//	std::string fileName = "1.tmx";
//	std::string filePath = FileUtils::getInstance()->getWritablePath();
//	filePath=filePath+fileName;
//	auto str = String::createWithContentsOfFile(filePath);

	tileMap = TMXTiledMap::createWithXML(floor0->getFileContent(), "");

	Layer::addChild(tileMap, -1);

	cocos2d::Point startPosition = floor0->getUpPosition();
	//cocos2d::Point startPosition(0, 0);

	//player = Character::create("test_character.plist");
	player = CharacterManager::getInstance()->getCharacter("Actor0");
	Character* testCharacter = CharacterManager::getInstance()->getCharacter("Actor0");

	this->addCharacter(testCharacter);
	this->addCharacter(player);

	player->setPosition(startPosition.x*32+16, (100-startPosition.y)*32-16);
	testCharacter->setPosition((startPosition.x + 1) * 32 + 16, (100 - startPosition.y) * 32 - 16);
	
	player->setMapCoord(floor0->getUpPosition());
//	player->setPosition(32, 32);

	setViewPointCenter(player->getPosition());

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		this->handleKey(keyCode);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	controlMode = MoveMode;

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

void GameScene::update(float dt)
{
	this->setViewPointCenter(player->getPosition());
}

void GameScene::handleKey(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (controlMode)
	{
	case AttackMode:
		playerAttack(keyCode);
		break;
	case MoveMode:
		playerMove(keyCode);
		break;
	}
}

void GameScene::playerAttack(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		player->runSkill("attack");
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		controlMode = MoveMode;
		break;
	}
}

void GameScene::playerMove(EventKeyboard::KeyCode keyCode)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
	{
		controlMode = AttackMode;
		return;
	}
	if (!isMoveAble(keyCode))
	{
		return;
	}
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		player->moveUp();
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		player->moveDown();
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		player->moveLeft();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		player->moveRight();
		break;

	}
}


bool GameScene::isMoveAble(EventKeyboard::KeyCode keyCode)
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

void GameScene::addCharacter(Character * character)
{
	Layer::addChild(character->getSprite());

	character->setScene(this);
	dungeon->addCharacter(character);
}
