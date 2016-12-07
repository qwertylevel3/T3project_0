#include "MainLayer.h"
#include "platform/CCGLView.h"
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
#include "MyCamera.h"
#include "ZOrderManager.h"

USING_NS_CC;
using namespace Field;


//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// on "init" you need to initialize your instance
bool MainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

//	this->setVisible(false);
	/////////////////////////////


//	cocos2d::Sprite *sprite2 = cocos2d::Sprite::create("HelloWorld.png");
//	this->addChild(sprite2);



	//////////////////////////////////////////////////////////////////////////
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


void MainLayer::update(float dt)
{
	Character* player = Player::getInstance()->getcharacterPtr();
//	this->setViewPointCenter(player->getPosition());
	HudLayer::getInstance()->update();
}

void MainLayer::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	KeyController::getInstance()->handleKeyPressed(keyCode);
}

void MainLayer::handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode)
{
	KeyController::getInstance()->handleKeyReleased(keyCode);
}


cocos2d::Point MainLayer::getWorldPosition(cocos2d::Point position)
{
	return position + this->getPosition();
}

void MainLayer::clear()
{
	Layer::removeAllChildren();
}


void MainLayer::initMission()
{


	addChild(
		Field::Dungeon::getInstance()->getStorey()->getTileMap(),
		ZOrderManager::tileMapZ
	);
}

